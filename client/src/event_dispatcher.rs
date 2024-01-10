use std::collections::HashMap;

use sdl2_wrapper::{SdlInstance, Event};

pub(crate) struct EventDispatcher {
    sdl_instance: std::rc::Rc<std::cell::RefCell<SdlInstance>>,
    event_callbacks: HashMap<u32, Box<dyn Fn()>>,
}

impl EventDispatcher {
    pub fn new(sdl_instance: std::rc::Rc<std::cell::RefCell<SdlInstance>>) -> EventDispatcher {
        EventDispatcher {
            sdl_instance,
            event_callbacks: HashMap::new(),
        }
    }

    /*pub fn register_event_callback(&mut self, event_id: u32, callback: fn()) {
        self.event_callbacks.insert(event_id, callback);
    }*/

    pub fn register_event_callback(&mut self, event_id: u32, callback: impl Fn() + 'static) {
        self.event_callbacks.insert(event_id, Box::new(callback));
    }

    pub fn run(&self) {
        'event_loop: loop {
            let event = self.sdl_instance.borrow().wait_for_event();
            println!("event: {:?}", event);
            match event {
                Event::Quit => {
                    break 'event_loop;
                },
                Event::CustomEvent(custom_event) => {
                    if let Some(callback) = self.event_callbacks.get(&custom_event.event_id) {
                        callback();
                    }
                }
                _ => {}
            }
        }
    }
}
