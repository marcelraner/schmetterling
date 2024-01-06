#[link(name = "SDL2_image")]
extern "C" {
    pub fn IMG_Init(flags: i32) -> i32;
    pub fn IMG_LoadTexture(renderer: *const std::ffi::c_void, file: *const std::ffi::c_char) -> *const std::ffi::c_void;
    pub fn IMG_SavePNG(texture: *const std::ffi::c_void, file: *const std::ffi::c_char) -> i32;
    pub fn IMG_Quit();
}
