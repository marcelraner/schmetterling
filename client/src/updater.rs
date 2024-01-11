use crate::game_state::GameState;

pub struct Updater {
    game_state: std::rc::Rc<std::cell::RefCell<GameState>>,
}

impl Updater {
    pub fn new(game_state: std::rc::Rc<std::cell::RefCell<GameState>>) -> Self {
        Updater {
            game_state,
        }
    }

    pub fn update(&self) {
        //println!("update()");
        self.game_state.borrow_mut().dummy.0 += 1;
        self.game_state.borrow_mut().dummy.1 += 1;
    }
}
