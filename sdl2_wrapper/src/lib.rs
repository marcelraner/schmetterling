use std::ffi::{c_int, c_uchar, c_uint, c_void};

pub const SDL_INIT_VIDEO: c_uint = 0x00000020;
pub const SDL_WINDOW_SHOWN: c_uint = 0x00000004;

pub const SDL_WINDOW_FULLSCREEN: c_uint = 0x00000001;
pub const SDL_WINDOW_RESIZABLE: c_uint = 0x00000020;

pub const SDL_EVENT_QUIT: c_uint = 0x100;

#[link(name = "SDL2")]
extern "C" {
    pub fn SDL_Init(flags: c_int) -> c_int;
    pub fn SDL_CreateWindow(
        title: *const i8,
        x: c_int,
        y: c_int,
        w: c_int,
        h: c_int,
        flags: c_uint,
    ) -> *mut c_void;
    pub fn SDL_CreateRenderer(window: *mut c_void, index: c_int, flags: c_uint) -> *mut c_void;
    pub fn SDL_SetRenderDrawColor(
        renderer: *mut c_void,
        r: c_uchar,
        g: c_uchar,
        b: c_uchar,
        a: c_uchar,
    ) -> c_int;
    pub fn SDL_RenderClear(renderer: *mut c_void) -> c_int;
    pub fn SDL_RenderDrawRect(renderer: *mut c_void, rect: *const SDL_Rect) -> c_int;
    pub fn SDL_RenderPresent(renderer: *mut c_void);
    pub fn SDL_Delay(ms: u32);
    pub fn SDL_DestroyRenderer(renderer: *mut c_void);
    pub fn SDL_DestroyWindow(window: *mut c_void);
    pub fn SDL_Quit();
    pub fn SDL_PollEvent(event: *mut SDL_Event) -> c_int;
    pub fn SDL_WaitEvent(event: *mut SDL_Event) -> c_int;
    pub fn SDL_GetError() -> *const i8;
    pub fn SDL_RenderFillRect(renderer: *mut c_void, rect: *const SDL_Rect) -> i32;
    pub fn SDL_RegisterEvents(numevents: i32) -> u32;
    pub fn SDL_PushEvent(event: *mut SDL_Event) -> i32;
}

// SDL_Rect structure
#[repr(C)]
pub struct SDL_Rect {
    pub x: c_int,
    pub y: c_int,
    pub w: c_int,
    pub h: c_int,
}

#[repr(C)]
pub struct SDL_Event {
    pub _type: u32,
    padding: [u8; 52],
}

impl SDL_Event {
    pub fn new() -> Self {
        let event: Self = unsafe { std::mem::zeroed() };
        event
    }
}

pub fn init_sdl() {
    unsafe {
        if SDL_Init(0) != 0 {
            println!("SDL_Init failed: {}", get_error());
            std::process::exit(1);
        }
    }
}

pub fn destroy_sdl() {
    unsafe {
        SDL_Quit();
    }
}

pub fn create_window(title: &str, x: i32, y: i32, w: i32, h: i32, flags: u32) -> *mut c_void {
    let title_cstring = std::ffi::CString::new(title).expect("Failed to convert title to CString");
    unsafe { SDL_CreateWindow(title_cstring.as_ptr(), x, y, w, h, flags) }
}

pub fn destroy_window(window: *mut c_void) {
    unsafe {
        SDL_DestroyWindow(window);
    }
}

pub fn create_renderer(window: *mut c_void, index: i32, flags: u32) -> *mut c_void {
    unsafe { SDL_CreateRenderer(window, index, flags) }
}

pub fn destroy_renderer(renderer: *mut c_void) {
    unsafe {
        SDL_DestroyRenderer(renderer);
    }
}

pub fn set_render_draw_color(renderer: *mut c_void, r: u8, g: u8, b: u8, a: u8) {
    unsafe {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
}

pub fn render_clear(renderer: *mut c_void) {
    unsafe {
        SDL_RenderClear(renderer);
    }
}

pub fn render_fill_rect(renderer: *mut c_void, rect: &SDL_Rect) {
    unsafe {
        SDL_RenderFillRect(renderer, rect);
    }
}

pub fn render_present(renderer: *mut c_void) {
    unsafe {
        SDL_RenderPresent(renderer);
    }
}

pub fn wait_event(event: &mut SDL_Event) -> i32 {
    unsafe { SDL_WaitEvent(event) }
}

pub fn poll_event(event: &mut SDL_Event) -> i32 {
    unsafe { SDL_PollEvent(event) }
}

pub fn get_error() -> String {
    unsafe {
        let error_ptr = SDL_GetError();
        let c_str = std::ffi::CStr::from_ptr(error_ptr);
        c_str.to_string_lossy().into_owned()
    }
}

#[derive(Debug)]
pub struct SdlContext {
    window: Option<*mut c_void>,
    renderer: Option<*mut c_void>,
}

impl SdlContext {
    pub fn new() -> Self {
        init_sdl();
        let buffer_event = SDL_Event::new();
        Self{
            window: None,
            renderer: None,
        }
    }

    pub fn create_window(&mut self) {
        self.window = Some(create_window("Rust SDL FFI Example", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE));
        self.renderer = Some(create_renderer(self.window.unwrap(), -1, 0));
    }
}

impl Drop for SdlContext {
    fn drop(&mut self) {
        destroy_sdl();
    }
}
