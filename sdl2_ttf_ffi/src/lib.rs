use std::ffi::c_char;

pub type TTF_Font = *const std::ffi::c_void;
pub type SDL_Surface = *const std::ffi::c_void;

#[link(name = "SDL2_ttf")]
extern "C" {
    pub fn TTF_Init() -> i32;
    pub fn TTF_Quit();
    pub fn TTF_OpenFont(file: *const c_char, size: i32) -> TTF_Font;
    pub fn TTF_CloseFont(font: TTF_Font);
    pub fn TTF_RenderText_Solid(
        font: TTF_Font,
        text: *const std::ffi::c_char,
        color: *const std::ffi::c_void,
    ) -> SDL_Surface;
}
