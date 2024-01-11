pub struct Position<T> {
    pub x: T,
    pub y: T,
}

impl<T> Position<T> {
    pub fn new(x: T, y: T) -> Self {
        Position { x, y }
    }
}

pub struct Size<T> {
    w: T,
    h: T,
}

pub struct Player {
    pub camera_position: Position<i32>,
}

pub struct SomeObject {
    pub position: Position<i32>,
}

pub struct GameState {
    pub player: Player,
    pub some_objects: Vec<SomeObject>,
}

impl GameState {
    pub fn new() -> Self {
        let mut some_objects = Vec::new();
        some_objects.push(SomeObject { position: Position::new(100, 100)});
        some_objects.push(SomeObject { position: Position::new(200, 100)});
        some_objects.push(SomeObject { position: Position::new(-100, 100)});
        some_objects.push(SomeObject { position: Position::new(-50, -100)});
        GameState {
            player: Player {
                camera_position: Position::new(0, 0),
            },
            some_objects,
        }
    }
}
