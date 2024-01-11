pub const SDL_QUIT: std::ffi::c_uint = 0x100;

pub const SDL_INIT_VIDEO: std::ffi::c_uint = 0x00000020;

pub const SDL_WINDOW_SHOWN: std::ffi::c_uint = 0x00000004;
pub const SDL_WINDOW_FULLSCREEN: std::ffi::c_uint = 0x00000001;
pub const SDL_WINDOW_RESIZABLE: std::ffi::c_uint = 0x00000020;

pub const SDL_WINDOWPOS_UNDEFINED_MASK: std::ffi::c_uint = 0x1FFF0000;
macro_rules! SDL_WINDOWPOS_UNDEFINED_DISPLAY {
    ($display:literal) => {
        SDL_WINDOWPOS_UNDEFINED_MASK | $display
    };
}
pub const SDL_WINDOWPOS_UNDEFINED: std::ffi::c_uint = SDL_WINDOWPOS_UNDEFINED_DISPLAY!(0);

pub const SDL_WINDOWPOS_CENTERED_MASK: std::ffi::c_uint = 0x2FFF0000;
macro_rules! SDL_WINDOWPOS_CENTERED_DISPLAY {
    ($display:literal) => {
        SDL_WINDOWPOS_CENTERED_MASK | $display
    };
}
pub const SDL_WINDOWPOS_CENTERED: std::ffi::c_uint = SDL_WINDOWPOS_CENTERED_DISPLAY!(0);

pub type SDL_Window = *const std::ffi::c_void;
pub type SDL_Renderer = *const std::ffi::c_void;
pub type SDL_Texture = *const std::ffi::c_void;
pub type SDL_Surface = *const std::ffi::c_void;

#[repr(C)]
pub struct SDL_Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}

#[repr(C)]
pub struct SDL_Event {
    pub event_type: u32,
    pub padding: [u8; 52],
}

#[repr(C)]
pub struct SDL_Rect {
    pub x: i32,
    pub y: i32,
    pub w: i32,
    pub h: i32,
}

#[link(name = "SDL2")]
extern "C" {
    pub fn SDL_Init(flags: u32) -> i32;
    pub fn SDL_Quit();
    pub fn SDL_GetError() -> *const std::ffi::c_char;
    pub fn SDL_CreateWindow(
        title: *const std::ffi::c_char,
        x: i32,
        y: i32,
        w: i32,
        h: i32,
        flags: u32,
    ) -> SDL_Window;
    pub fn SDL_DestroyWindow(window: SDL_Window);
    pub fn SDL_CreateRenderer(window: SDL_Window, index: i32, flags: u32) -> SDL_Renderer;
    pub fn SDL_DestroyRenderer(renderer: SDL_Renderer);
    pub fn SDL_SetRenderDrawColor(renderer: SDL_Renderer, r: u8, g: u8, b: u8, a: u8) -> i32;
    pub fn SDL_RenderClear(renderer: SDL_Renderer) -> std::ffi::c_int;
    pub fn SDL_RenderPresent(renderer: SDL_Renderer);
    pub fn SDL_WaitEvent(event: *mut SDL_Event) -> std::ffi::c_int;
    pub fn SDL_PollEvent(event: *mut SDL_Event) -> std::ffi::c_int;
    pub fn SDL_RenderCopy(
        renderer: SDL_Renderer,
        texture: SDL_Texture,
        srcrect: *const std::ffi::c_void,
        dstrect: *const std::ffi::c_void,
    ) -> i32;
    pub fn SDL_CreateTextureFromSurface(
        renderer: SDL_Renderer,
        surface: SDL_Surface,
    ) -> SDL_Texture;
    pub fn SDL_FreeSurface(surface: SDL_Surface);
    pub fn SDL_QueryTexture(
        texture: SDL_Texture,
        format: *mut u32,
        access: *mut i32,
        w: *mut i32,
        h: *mut i32,
    ) -> i32;
    pub fn SDL_DestroyTexture(texture: SDL_Texture);
    pub fn SDL_RegisterEvents(numevents: i32) -> u32;
    pub fn SDL_PushEvent(event: *const SDL_Event) -> i32;
    pub fn SDL_RenderDrawLine(
        renderer: SDL_Renderer,
        x1: i32,
        y1: i32,
        x2: i32,
        y2: i32,
    ) -> i32;
    pub fn SDL_RenderDrawRect(
        renderer: SDL_Renderer,
        rect: *const SDL_Rect,
    ) -> i32;
    pub fn SDL_GetRendererOutputSize(
        renderer: SDL_Renderer,
        w: *mut i32,
        h: *mut i32,
    ) -> i32;
}
