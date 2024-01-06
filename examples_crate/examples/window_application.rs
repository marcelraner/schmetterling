use sdl2_ffi::{
    SDL_CreateWindow, SDL_Event, SDL_Init, SDL_Quit, SDL_WaitEvent, SDL_QUIT,
    SDL_INIT_VIDEO, SDL_WINDOW_RESIZABLE, SDL_WINDOW_SHOWN,
};
use sdl2_wrapper::sdl2_get_error;

fn main() {
    // Initialize SDL
    unsafe {
        if SDL_Init(SDL_INIT_VIDEO) != 0 {
            panic!("Unable to initialize SDL: {}", sdl2_get_error());
        }
    }

    // Create a window
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

    // Check if the window was created successfully
    if window.is_null() {
        unsafe {
            println!("Unable to create SDL window: {}", sdl2_get_error());
            SDL_Quit();
        }
        return;
    }

    // Main event loop
    'event_loop: loop {
        let mut event: SDL_Event = unsafe { std::mem::zeroed() };

        // Wait for an event
        unsafe {
            SDL_WaitEvent(&mut event);
        }

        // Handle the event
        match event.event_type {
            SDL_QUIT => {
                println!("SDL_QUIT event received, exiting...");
                break 'event_loop;
            }
            _ => {
                // Handle other events as needed
                //println!("{:?}", event._type);
            }
        }
    }

    // Cleanup and quit SDL
    unsafe {
        SDL_Quit();
    }
}
