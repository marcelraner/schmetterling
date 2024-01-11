pub struct GameState {
    pub dummy: (i32, i32),
}

impl GameState {
    pub fn new() -> Self {
        GameState {
            dummy: (0,0),
        }
    }
}