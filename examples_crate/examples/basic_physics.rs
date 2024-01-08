use std::thread;

use sdl2_ffi::{
    SDL_CreateRenderer, SDL_CreateWindow,
    SDL_DestroyRenderer, SDL_DestroyWindow, SDL_Event,
    SDL_Init, SDL_Quit, SDL_RenderClear, SDL_RenderPresent, SDL_SetRenderDrawColor,
    SDL_WaitEvent, SDL_INIT_VIDEO, SDL_QUIT, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN, SDL_WINDOW_RESIZABLE, SDL_RenderDrawLine, SDL_RenderDrawRect, SDL_Rect, SDL_PollEvent,
};

struct RigidBody {
    position_x: f32,
    position_y: f32,
    velocity_x: f32,
    velocity_y: f32,
    mass: f32,
}

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

        let dt = 0.250;
        let mut object_a = RigidBody {position_x: 100.0, position_y: -100.0, velocity_x: 0.0, velocity_y: 0.0, mass: 1.0};

        'event_loop: loop {
            while SDL_PollEvent(&mut event) == 1 {
                match event.event_type {
                    SDL_QUIT => {
                        println!("SDL_QUIT event received, exiting...");
                        break 'event_loop;
                    }
                    _ => {}
                }
            }

            '_updating: {
                // Apply gravity to objects
                let force = object_a.mass * -9.81;
                let acceleration = force / object_a.mass;
                object_a.velocity_y += acceleration * dt as f32;

                object_a.position_x += object_a.velocity_x;
                object_a.position_y += object_a.velocity_y;
            }

            '_rendering: {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, 50, 50, 200, 200);
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                let rect = SDL_Rect { x: object_a.position_x as i32 -10, y: -object_a.position_y as i32 - 10, w: 20, h: 20 };
                SDL_RenderDrawRect(renderer, &rect);
                //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

                SDL_RenderPresent(renderer);
            }

            thread::sleep(std::time::Duration::from_millis((dt * 1000.0) as u64));
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
