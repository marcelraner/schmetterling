mod update_trigger;

/*struct EventDispatcher{}

impl EventDispatcher {
    fn new() -> EventDispatcher {
        EventDispatcher {}
    }

    fn run(&self) {
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
    }
}

struct SdlInstance{}

impl SdlInstance {
    fn new(nr_custom_event_slots: u32) -> SdlInstance {
        SdlInstance {}
    }

    fn aquire_event_type() ->
}*/

use std::{
    sync::{mpsc::Sender, Arc, Mutex},
    thread::{self, JoinHandle},
    time::Duration,
};

use sdl2_wrapper::{SdlInstance, SdlRenderer, SdlWindow, CustomEvent};

use crate::update_trigger::UpdateTrigger;



fn main() {
    println!("Hello, world!");

    let sdl_instance = Arc::new(Mutex::new(SdlInstance::new()));
    //let sdl_instance = std::rc::Rc::new(SdlInstance::new());
    let sdl_window = std::rc::Rc::new(SdlWindow::new(Arc::clone(&sdl_instance)));
    let sdl_renderer = SdlRenderer::new(std::rc::Rc::clone(&sdl_window));

    let event_ids = sdl_instance.lock().unwrap().register_events(2);
    println!("event_id: {}", event_ids[0]);
    println!("event_id: {}", event_ids[1]);
    // todo: return array[2]

    let mut update_trigger = UpdateTrigger::new(
        Arc::clone(&sdl_instance),
        Duration::from_millis(1000),
        event_ids[0],
    );

    update_trigger.start();
    thread::sleep(Duration::from_millis(4000));
    update_trigger.end();

    /*let render_event_type = unsafe { SDL_RegisterEvents(2) };
    let update_event_type = render_event_type + 1;

    let sdl_instance = SdlInstance::new(2);

    let update_trigger = UpdateTrigger::new();
    let event_dispatcher = EventDispatcher::new();

    event_dispatcher.run();*/
}
