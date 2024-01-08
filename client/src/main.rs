mod interval_trigger;

use std::{
    sync::{Arc, Mutex},
    thread::{self},
    time::Duration, rc::Rc, ops::Deref, cell::RefCell,
};

use sdl2_wrapper::{SdlInstance, SdlRenderer, SdlWindow, Event};

use crate::interval_trigger::IntervalTrigger;

struct EventDispatcher {
    sdl_instance: std::rc::Rc<std::cell::RefCell<SdlInstance>>,
}

impl EventDispatcher {
    fn new(sdl_instance: std::rc::Rc<std::cell::RefCell<SdlInstance>>) -> EventDispatcher {
        EventDispatcher {
            sdl_instance
        }
    }

    fn run(&self) {
        'event_loop: loop {
            // TODO: this call locks the sdl_instance and then no trigger thread can spawn an event
            let event = self.sdl_instance.borrow().wait_for_event();
            println!("event: {:?}", event);
            match event {
                Event::Quit => {
                    break 'event_loop;
                },
                _ => {}
            }
        }
    }
}

fn main() {
    println!("Client v0.1.0");

    let sdl_instance = Rc::new(RefCell::new(SdlInstance::new()));
    let sdl_window = Rc::new(SdlWindow::new(Rc::clone(&sdl_instance)));
    let sdl_renderer = SdlRenderer::new(Rc::clone(&sdl_window));

    let event_ids = sdl_instance.borrow_mut().register_events(2);
    println!("event_id: {}", event_ids[0]);
    println!("event_id: {}", event_ids[1]);

    let mut update_trigger = IntervalTrigger::new(
        Rc::clone(&sdl_instance),
        Duration::from_millis(1000),
        event_ids[0],
    );

    let mut render_trigger = IntervalTrigger::new(
        Rc::clone(&sdl_instance),
        Duration::from_millis(250),
        event_ids[1],
    );

    let event_dispatcher = EventDispatcher::new(
        Rc::clone(&sdl_instance),
    );

    update_trigger.start();
    render_trigger.start();
    event_dispatcher.run();
    render_trigger.end();
    update_trigger.end();
}
