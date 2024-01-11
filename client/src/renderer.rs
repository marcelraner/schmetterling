use sdl2_wrapper::SdlRenderer;

use crate::game_state::GameState;

pub struct Renderer {
    sdl_renderer: std::rc::Rc<SdlRenderer>,
    game_state: std::rc::Rc<std::cell::RefCell<GameState>>,
}

impl Renderer {
    pub fn new(sdl_renderer: std::rc::Rc<SdlRenderer>, game_state: std::rc::Rc<std::cell::RefCell<GameState>>) -> Self {
        Renderer {
            sdl_renderer,
            game_state,
        }
    }

    pub fn render(&self) {
        //println!("render()");
        self.sdl_renderer.set_draw_color(111, 0, 0, 0);
        self.sdl_renderer.clear();
        self.sdl_renderer.set_draw_color(0, 111, 0, 0);
        self.sdl_renderer.draw_rectangle(self.game_state.borrow().dummy.0 - 10, self.game_state.borrow().dummy.1 - 10, 20, 20);
        self.sdl_renderer.present();
    }
}