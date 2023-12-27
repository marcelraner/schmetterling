use std::io::{self, BufRead};
use std::net::UdpSocket;
use std::env;
use std::str;
use std::{thread, time};

struct ClientState
{
}

fn main() -> std::io::Result<()> {

    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Usage {} hostname", args[0]);
        std::process::exit(1);
    }
    let hostname = &args[1];

    let socket = UdpSocket::bind("[::]:0")?;  // for UDP4/6
    //socket.connect(hostname.to_string() + &":2000").expect("couldn't connect to address");

    // from https://stackoverflow.com/questions/30186037/how-can-i-read-a-single-line-from-stdin
    /*let stdin = io::stdin();
    for line in stdin.lock().lines() {
	let line = line.unwrap();
	println!("Line read from stdin '{}'", line);
	if &line == "BYE" {
	    break;
	}

	socket.send_to(line.as_bytes(), hostname.to_string() + &":2000")
	    .expect("Error on send");*/

	/*let mut buf = [0; 2048];
	let (amt, _src) = socket.recv_from(&mut buf)?;

	let echo = str::from_utf8(&buf[..amt]).unwrap();
	println!("Echo {}", echo);
    }*/

    loop {
        // send
        let packet = shared::Packet {
            packet_id: 123,
            crc32: 123,
            payload_type: shared::PayloadType::EntityPositionPayload,
            payload: shared::Payload{
                entity_position: shared::EntityPosition {
                    id: 123,
                    x: 123,
                    y: 123,
                }
            }
        };
        let raw = &packet as *const u8;
        let packet_as_bytes: &[u8] = unsafe { std::slice::from_raw_parts(raw , 2) };

        socket.send_to(packet_as_bytes, hostname.to_string() + &":2000")
	        .expect("Error on send");

        // receive
        let mut buf = [0; 2048];
        let (amt, _src) = socket.recv_from(&mut buf)?;
        thread::sleep(time::Duration::from_millis(1000));

        // print

    }

    Ok(())
}