use sdl2_ffi::{
    SDL_CreateRenderer, SDL_CreateWindow, SDL_DestroyRenderer, SDL_DestroyWindow, SDL_Event,
    SDL_Init, SDL_PollEvent, SDL_PushEvent, SDL_Quit, SDL_RegisterEvents, SDL_RenderClear,
    SDL_RenderPresent, SDL_Renderer, SDL_SetRenderDrawColor, SDL_WaitEvent, SDL_Window,
    SDL_INIT_VIDEO, SDL_QUIT, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOW_RESIZABLE, SDL_WINDOW_SHOWN, SDL_Rect, SDL_RenderDrawRect, SDL_GetRendererOutputSize,
};

#[derive(Debug)]
pub enum Event {
    Quit,
    CustomEvent(CustomEvent),
    Unknown,
}

#[derive(Debug)]
pub struct CustomEvent {
    pub event_id: u32,
}

pub fn sdl2_get_error() -> String {
    unsafe {
        let error_ptr = sdl2_ffi::SDL_GetError();
        let c_str = std::ffi::CStr::from_ptr(error_ptr);
        c_str.to_string_lossy().into_owned()
    }
}

pub struct SdlInstance {
    registered_events: Vec<u32>,
}

impl SdlInstance {
    pub fn new() -> SdlInstance {
        unsafe {
            if SDL_Init(SDL_INIT_VIDEO) != 0 {
                panic!("Unable to initialize SDL: {}", sdl2_get_error());
            }
        }
        SdlInstance {
            registered_events: Vec::new(),
        }
    }

    pub fn register_events(&mut self, number_of_events: u32) -> Vec<u32> {
        let first_event_id = unsafe { SDL_RegisterEvents(number_of_events as i32) };
        for i in 0..number_of_events {
            self.registered_events.push(first_event_id + i);
        }
        self.registered_events.clone()
    }

    // its a static method because it is called from threads
    pub fn push_custom_event(event: CustomEvent) {
        let mut sdl_event: SDL_Event = unsafe { std::mem::zeroed() };
        sdl_event.event_type = event.event_id;
        unsafe {
            SDL_PushEvent(&sdl_event as *const SDL_Event);
        }
    }

    pub fn wait_for_event(&self) -> Event {
        let mut event = Event::Unknown;
        unsafe {
            let mut sdl_event: SDL_Event = std::mem::zeroed();
            SDL_WaitEvent(&mut sdl_event);
            match sdl_event.event_type {
                SDL_QUIT => event = Event::Quit,
                _ => {
                    for registered_event in &self.registered_events {
                        if sdl_event.event_type == *registered_event {
                            event = Event::CustomEvent(CustomEvent {
                                event_id: sdl_event.event_type,
                            });
                        }
                    }
                }
            }
        }
        event
    }
}

impl Drop for SdlInstance {
    fn drop(&mut self) {
        unsafe {
            SDL_Quit();
        }
    }
}

pub struct SdlWindow {
    _sdl_instance: std::rc::Rc<std::cell::RefCell<SdlInstance>>,
    window: SDL_Window,
}

impl SdlWindow {
    pub fn new(sdl_instance: std::rc::Rc<std::cell::RefCell<SdlInstance>>) -> SdlWindow {
        let window_title =
            std::ffi::CString::new("Window Application").expect("CString::new failed");
        let window = unsafe {
            SDL_CreateWindow(
                window_title.as_ptr(),
                SDL_WINDOWPOS_CENTERED as i32,
                SDL_WINDOWPOS_CENTERED as i32,
                640,
                480,
                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
            )
        };
        if window.is_null() {
            panic!("Unable to create SDL window: {}", sdl2_get_error());
        }
        SdlWindow {
            _sdl_instance: sdl_instance,
            window,
        }
    }
}

impl Drop for SdlWindow {
    fn drop(&mut self) {
        unsafe {
            SDL_DestroyWindow(self.window);
        }
    }
}

pub struct SdlRenderer {
    _sdl_window: std::rc::Rc<SdlWindow>,
    renderer: SDL_Renderer,
}

impl SdlRenderer {
    pub fn new(sdl_window: std::rc::Rc<SdlWindow>) -> SdlRenderer {
        let renderer = unsafe { SDL_CreateRenderer(sdl_window.window, -1, 0) };
        if renderer.is_null() {
            panic!("Unable to create SDL renderer: {}", sdl2_get_error());
        }
        SdlRenderer {
            _sdl_window: sdl_window,
            renderer,
        }
    }

    pub fn get_renderer_size(&self) -> (i32, i32) {
        let mut w: i32 = 0;
        let mut h: i32 = 0;
        unsafe {
            SDL_GetRendererOutputSize(self.renderer, &mut w, &mut h);
        }
        (w, h)
    }

    pub fn set_draw_color(&self, r: u8, g: u8, b: u8, a: u8) {
        unsafe {
            SDL_SetRenderDrawColor(self.renderer, r, g, b, a);
        }
    }

    pub fn clear(&self) {
        unsafe {
            SDL_RenderClear(self.renderer);
        }
    }

    pub fn present(&self) {
        unsafe {
            SDL_RenderPresent(self.renderer);
        }
    }

    pub fn draw_rectangle(&self, x: i32, y: i32, w: i32, h: i32) {
        let rect = SDL_Rect { x, y, w, h };
        unsafe { SDL_RenderDrawRect(self.renderer, &rect); }
    }
}

impl Drop for SdlRenderer {
    fn drop(&mut self) {
        unsafe {
            SDL_DestroyRenderer(self.renderer);
        }
    }
}
