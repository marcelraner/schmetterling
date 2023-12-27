pub enum ConnectionState {
    Disconnected,
    Connecting,
    Connected,
}

pub enum PayloadType {
    EntityPositionPayload = 0,
}

#[derive(Copy, Clone)]
pub struct EntityPosition {
    pub id: u32,
    pub x: u64,
    pub y: u64,
}

pub union Payload
{
    pub entity_position: EntityPosition,
}

pub struct Packet
{
    pub packet_id: u8,
    pub crc32: u32,
    pub payload_type: PayloadType,
    pub payload: Payload,
}

impl Packet {
    pub fn as_bytes(&self) -> &[u8] {
        &[self.packet_id]
    }
}

pub fn serialize_packet(data: &[u8]) -> Packet {

    let window: &[u8; 4] = &data[1..5].try_into().unwrap();
    let num = u32::from_be_bytes(*window);

    let packet = Packet {
        packet_id: 123,
        crc32: 123,
        payload_type: PayloadType::EntityPositionPayload,
        payload: Payload{
            entity_position: EntityPosition {
                id: 123,
                x: 123,
                y: 123,
            }
        }
    };
    packet
}

pub fn deserialize_packet(packet: &Packet) -> Vec<u8> {
    let mut data: Vec<u8> = Vec::new();
    data.extend(packet.packet_id.to_be_bytes());
    data.extend(packet.crc32.to_be_bytes());
    if packet.payload_type == PayloadType::EntityPositionPayload {
        data.extend(0_u8.to_be_bytes());
        data.extend(packet.payload.entity_position.id.to_be_bytes());
        data.extend(packet.payload.entity_position.x.to_be_bytes());
        data.extend(packet.payload.entity_position.y.to_be_bytes());
    }
    data
}

pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
