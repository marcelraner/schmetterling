mod event_dispatcher;
mod interval_trigger;
mod renderer;
mod updater;
mod game_state;

use crate::{event_dispatcher::EventDispatcher, game_state::GameState};
use crate::interval_trigger::IntervalTrigger;
use crate::renderer::Renderer;
use crate::updater::Updater;
use sdl2_wrapper::{SdlInstance, SdlRenderer, SdlWindow};
use std::{cell::RefCell, rc::Rc, time::Duration};

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

    let mut event_dispatcher = EventDispatcher::new(Rc::clone(&sdl_instance));

    let game_state = Rc::new(RefCell::new(GameState::new()));

    let renderer = Renderer::new(Rc::clone(&sdl_renderer), Rc::clone(&game_state));

    let on_render_closure = move || {
        renderer.render();
    };

    let updater = Updater::new(Rc::clone(&game_state));

    let on_update_closure = move || {
        updater.update();
    };

    event_dispatcher.register_event_callback(update_event_id, on_update_closure);
    event_dispatcher.register_event_callback(render_event_id, on_render_closure);

    update_trigger.start();
    render_trigger.start();
    event_dispatcher.run();
    render_trigger.end();
    update_trigger.end();
}
