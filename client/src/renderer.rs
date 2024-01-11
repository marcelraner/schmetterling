use sdl2_wrapper::SdlRenderer;

use crate::game_state::GameState;

pub struct Renderer {
    sdl_renderer: std::rc::Rc<SdlRenderer>,
    game_state: std::rc::Rc<std::cell::RefCell<GameState>>,
}

impl Renderer {
    pub fn new(
        sdl_renderer: std::rc::Rc<SdlRenderer>,
        game_state: std::rc::Rc<std::cell::RefCell<GameState>>,
    ) -> Self {
        Renderer {
            sdl_renderer,
            game_state,
        }
    }

    pub fn render(&self) {
        //println!("render()");
        let renderer_size = self.sdl_renderer.get_renderer_size();

        let offset_x = (renderer_size.0 / 2) - self.game_state.borrow().player.camera_position.x;
        let offset_y = (renderer_size.1 / 2) - self.game_state.borrow().player.camera_position.y;

        self.sdl_renderer.set_draw_color(0, 0, 0, 0);
        self.sdl_renderer.clear();

        // draw 0 position
        self.sdl_renderer.set_draw_color(255, 0, 0, 0);
        self.sdl_renderer.draw_rectangle(
            offset_x - 10,
            offset_y - 10,
            20,
            20,
        );

        // draw some objects positions
        self.sdl_renderer.set_draw_color(0, 0, 255, 0);
        for some_object in &self.game_state.borrow().some_objects {
            self.sdl_renderer.draw_rectangle(
                offset_x + some_object.position.x - 10,
                offset_y + some_object.position.y - 10,
                20,
                20,
            );
        }

        // draw camera position
        self.sdl_renderer.set_draw_color(0, 255, 0, 0);
        self.sdl_renderer.draw_rectangle(
            (renderer_size.0 / 2) - 10,
            (renderer_size.1 / 2) - 10,
            20,
            20,
        );
        self.sdl_renderer.present();
    }
}
