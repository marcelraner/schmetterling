use sdl2_ffi::{
    SDL_CreateRenderer, SDL_CreateWindow,
    SDL_DestroyRenderer, SDL_DestroyWindow, SDL_Event,
    SDL_Init, SDL_Quit, SDL_RenderClear, SDL_RenderPresent, SDL_SetRenderDrawColor,
    SDL_WaitEvent, SDL_INIT_VIDEO, SDL_QUIT, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN, SDL_WINDOW_RESIZABLE, SDL_RenderDrawLine, SDL_RenderDrawRect, SDL_Rect, SDL_RenderCopy,
};
use sdl2_image_ffi::IMG_LoadTexture;

fn main() {
    unsafe {
        let mut event: SDL_Event = std::mem::zeroed();

        SDL_Init(SDL_INIT_VIDEO);

        let window_title = std::ffi::CString::new("Window Application").unwrap();
        let window = SDL_CreateWindow(
            window_title.as_ptr(),
            SDL_WINDOWPOS_CENTERED as i32,
            SDL_WINDOWPOS_CENTERED as i32,
            640,
            480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
        );
        let renderer = SDL_CreateRenderer(window, -1, 0);

        let texture_filename = std::ffi::CString::new("resources/spaceship.png").unwrap();
        let texture = IMG_LoadTexture(renderer, texture_filename.as_ptr());

        'event_loop: loop {
            SDL_WaitEvent(&mut event);

            match event.event_type {
                SDL_QUIT => {
                    println!("SDL_QUIT event received, exiting...");
                    break 'event_loop;
                }
                _ => {}
            }
            '_rendering: {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer, texture, std::ptr::null(), std::ptr::null());

                SDL_RenderPresent(renderer);
            }
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
