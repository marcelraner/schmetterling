use std::thread;

use sdl2_ffi::{
    SDL_CreateWindow, SDL_Event, SDL_Init, SDL_PushEvent, SDL_Quit, SDL_RegisterEvents,
    SDL_WaitEvent, SDL_QUIT, SDL_INIT_VIDEO, SDL_WINDOW_RESIZABLE, SDL_WINDOW_SHOWN,
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

    // Register custom events
    let render_event_type = unsafe { SDL_RegisterEvents(2) };
    let update_event_type = render_event_type + 1;

    // Start the render trigger thread
    let (render_thread_sender, render_thread_receiver) = std::sync::mpsc::channel::<()>();
    let render_thread_join_handle = std::thread::spawn(move || {
        'thread_loop: loop {
            // check if thread should shut down
            if render_thread_receiver.try_recv().is_ok() {
                break 'thread_loop;
            }

            // Simulate some rendering work
            thread::sleep(std::time::Duration::from_millis(250));

            // Trigger a custom render event in the main thread
            let mut render_event: SDL_Event = unsafe { std::mem::zeroed() };
            render_event.event_type = render_event_type;

            // Send the custom render event to the main thread
            unsafe {
                SDL_PushEvent(&mut std::mem::transmute(render_event));
            }
        }
    });

    // Start the update trigger thread
    let (update_thread_sender, update_thread_receiver) = std::sync::mpsc::channel::<()>();
    let update_thread_join_handle = std::thread::spawn(move || {
        'thread_loop: loop {
            // check if thread should shut down
            if update_thread_receiver.try_recv().is_ok() {
                break 'thread_loop;
            }

            // Simulate some updateing work
            thread::sleep(std::time::Duration::from_millis(1000));

            // Trigger a custom update event in the main thread
            let mut update_event: SDL_Event = unsafe { std::mem::zeroed() };
            update_event.event_type = update_event_type;

            // Send the custom update event to the main thread
            unsafe {
                SDL_PushEvent(&mut std::mem::transmute(update_event));
            }
        }
    });

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
                println!("{:?}", event.event_type);
                if event.event_type == render_event_type {
                    println!("render_event_type");
                } else if event.event_type == update_event_type {
                    println!("update_event_type");
                }
            }
        }
    }

    update_thread_sender.send(()).unwrap();
    update_thread_join_handle.join().unwrap();
    render_thread_sender.send(()).unwrap();
    render_thread_join_handle.join().unwrap();

    // Cleanup and quit SDL
    unsafe {
        SDL_Quit();
    }
}
