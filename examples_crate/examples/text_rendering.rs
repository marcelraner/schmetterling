use sdl2_ffi::{
    SDL_CreateRenderer, SDL_CreateTextureFromSurface, SDL_CreateWindow,
    SDL_DestroyRenderer, SDL_DestroyTexture, SDL_DestroyWindow, SDL_Event, SDL_FreeSurface,
    SDL_Init, SDL_Quit, SDL_RenderClear, SDL_RenderCopy, SDL_RenderPresent, SDL_SetRenderDrawColor,
    SDL_WaitEvent, SDL_INIT_VIDEO, SDL_QUIT, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN, SDL_WINDOW_RESIZABLE,
};
use sdl2_ttf_ffi::{
    TTF_CloseFont, TTF_Init, TTF_OpenFont, TTF_Quit, TTF_RenderText_Solid,
};

fn main() {
    unsafe {
        let mut event: SDL_Event = std::mem::zeroed();

        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();

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

        let font_filename = std::ffi::CString::new("font.ttf").unwrap();
        let font = TTF_OpenFont(font_filename.as_ptr(), 24);

        let text = std::ffi::CString::new("Birds Aren't Real").unwrap();
        //let color = Box::<SDL_Color>::new(SDL_Color { r: 0, g: 0, b: 0, a: 0});
        let surface = TTF_RenderText_Solid(font, text.as_ptr(), std::ptr::null());
        let texture = SDL_CreateTextureFromSurface(renderer, surface);

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
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderCopy(renderer, texture, std::ptr::null(), std::ptr::null());

                SDL_RenderPresent(renderer);
            }
        }

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
}
