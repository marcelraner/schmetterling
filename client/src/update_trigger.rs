use std::{sync::{Arc, Mutex}, time::Duration, thread::{JoinHandle, self}};

use sdl2_wrapper::{SdlInstance, CustomEvent};

pub struct UpdateTrigger {
    sdl_instance: Arc<Mutex<SdlInstance>>,
    update_interval: Duration,
    sdl_event_id: u32,
    join_handle: Option<JoinHandle<()>>,
    stop_flag: Arc<Mutex<bool>>,
}

impl UpdateTrigger {
    pub fn new(sdl_instance: Arc<Mutex<SdlInstance>>, update_interval: Duration, sdl_event_id: u32) -> UpdateTrigger {
        UpdateTrigger {
            sdl_instance,
            update_interval,
            sdl_event_id,
            join_handle: None,
            stop_flag: Arc::new(Mutex::new(false)),
        }
    }

    pub fn start(&mut self) {
        *self.stop_flag.lock().unwrap() = false;
        let stop_flag = Arc::clone(&self.stop_flag);
        let update_interval = self.update_interval;
        let event_id = self.sdl_event_id;
        let sdl_instance = std::sync::Arc::clone(&self.sdl_instance);
        let join_handle = std::thread::spawn(move || {
            'thread_loop: loop {
                // check for shutdown
                if *stop_flag.lock().unwrap() {
                    break 'thread_loop;
                }

                // sleep for time that has been configured for update interval
                thread::sleep(update_interval);

                // Trigger a custom update event in the main thread
                let event = CustomEvent { event_id };
                sdl_instance.lock().unwrap().push_custom_event(event);
            }
        });
        self.join_handle = Some(join_handle);
    }

    pub fn end(&mut self) {
        if let Some(join_handle) = self.join_handle.take() {
            *self.stop_flag.lock().unwrap() = true;
            join_handle.join().unwrap();
        }
    }
}
