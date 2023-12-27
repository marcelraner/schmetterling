//use std::io::{self, Read, Write, BufRead};
use std::net::{UdpSocket, SocketAddr};
//use std::env;
use std::str;

use shared::ConnectionState;

struct Client
{
    connection_state: ConnectionState,
    address: SocketAddr,
}

struct ServerState
{
    clients: Vec<Client>,
}

fn main() -> std::io::Result<()> {
    //let socket = UdpSocket::bind("0.0.0.0:2000")?; // for UDP4
    let socket = UdpSocket::bind("[::]:2000")?;  // for UDP4/6
    let mut buf = [0; 2048];

    loop {
        // Receives a single datagram message on the socket.
	// If `buf` is too small to hold
        // the message, it will be cut off.
        let (amt, src) = socket.recv_from(&mut buf)?;

        // Print received data
        let echo = str::from_utf8(&buf[..amt]).unwrap();
	    println!("Echo {} from {}", echo, src);

        // Redeclare `buf` as slice of the received data
	// and send data back to origin.
        let buf = &mut buf[..amt];
        socket.send_to(buf, &src)?;
    }
}