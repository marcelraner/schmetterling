pub fn sdl2_get_error() -> String {
    unsafe {
        let error_ptr = sdl2_ffi::SDL_GetError();
        let c_str = std::ffi::CStr::from_ptr(error_ptr);
        c_str.to_string_lossy().into_owned()
    }
}
