mod interval_trigger;
mod event_dispatcher;

use std::{
    time::Duration, rc::Rc, cell::RefCell,
};

use sdl2_wrapper::{SdlInstance, SdlRenderer, SdlWindow};

use crate::interval_trigger::IntervalTrigger;
use crate::event_dispatcher::EventDispatcher;

struct Renderer {
    sdl_renderer: std::rc::Rc<SdlRenderer>,
}

impl Renderer {
    pub fn new(sdl_renderer: std::rc::Rc<SdlRenderer>) -> Self {
        Renderer {
            sdl_renderer,
        }
    }

    pub fn on_render(&self) {
        println!("on_render()");
        self.sdl_renderer.set_draw_color(111, 0, 0, 0);
        self.sdl_renderer.clear();
        self.sdl_renderer.present();
    }
}

fn on_update() {
    println!("on_update()");
}

fn main() {
    println!("Client v0.1.0");

    let sdl_instance = Rc::new(RefCell::new(SdlInstance::new()));
    let sdl_window = Rc::new(SdlWindow::new(Rc::clone(&sdl_instance)));
    let sdl_renderer = Rc::new(SdlRenderer::new(Rc::clone(&sdl_window)));

    let event_ids = sdl_instance.borrow_mut().register_events(2);
    let update_event_id = event_ids[0];
    let render_event_id = event_ids[1];

    let mut update_trigger = IntervalTrigger::new(
        Rc::clone(&sdl_instance),
        Duration::from_millis(1000),
        update_event_id,
    );

    let mut render_trigger = IntervalTrigger::new(
        Rc::clone(&sdl_instance),
        Duration::from_millis(250),
        render_event_id,
    );

    let mut event_dispatcher = EventDispatcher::new(
        Rc::clone(&sdl_instance),
    );

    let renderer = Renderer::new(Rc::clone(&sdl_renderer));

    let on_render_closure = move || {
        renderer.on_render();
    };

    event_dispatcher.register_event_callback(update_event_id, on_update);
    event_dispatcher.register_event_callback(render_event_id, on_render_closure);

    update_trigger.start();
    render_trigger.start();
    event_dispatcher.run();
    render_trigger.end();
    update_trigger.end();
}
