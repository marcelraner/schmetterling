use sdl2_ffi::{SDL_Quit, SDL_Init, SDL_INIT_VIDEO, SDL_CreateWindow, SDL_DestroyWindow, SDL_Window, SDL_WINDOW_SHOWN, SDL_WINDOW_RESIZABLE, SDL_CreateRenderer, SDL_DestroyRenderer, SDL_Renderer, SDL_RegisterEvents, SDL_PushEvent, SDL_Event};

pub enum Event {
    Quit {
        timestamp: u32,
    },
}

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

pub struct SdlInstance {}

impl SdlInstance {
    pub fn new() -> SdlInstance {
        unsafe {
            if SDL_Init(SDL_INIT_VIDEO) != 0 {
                panic!("Unable to initialize SDL: {}", sdl2_get_error());
            }
        }
        SdlInstance {}
    }

    pub fn register_events(&self, number_of_events: u32) -> Vec<u32> {
        let first_event_id = unsafe {
            SDL_RegisterEvents(number_of_events as i32)
        };
        let mut vec = Vec::new();
        for i in 0..number_of_events {
            vec.push(first_event_id + i);
        }
        vec
    }

    pub fn push_custom_event(&self, event: CustomEvent) {
        let mut sdl_event: SDL_Event = unsafe { std::mem::zeroed() };
        sdl_event.event_type = event.event_id;
        unsafe {    
            SDL_PushEvent(&sdl_event as *const SDL_Event);
        }
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
    _sdl_instance: std::sync::Arc<std::sync::Mutex<SdlInstance>>,
    window: SDL_Window,
}

impl SdlWindow {
    pub fn new(sdl_instance: std::sync::Arc<std::sync::Mutex<SdlInstance>>) -> SdlWindow {
        let window_title = std::ffi::CString::new("Window Application").expect("CString::new failed");
        let window = unsafe {
            SDL_CreateWindow(
                window_title.as_ptr(),
                0,
                0,
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
}

impl Drop for SdlRenderer {
    fn drop(&mut self) {
        unsafe {
            SDL_DestroyRenderer(self.renderer);
        }
    }
}
