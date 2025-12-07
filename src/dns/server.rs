use std::net::SocketAddr;
use tokio::net::UdpSocket;
use trust_dns_proto::op::{Message, MessageType, OpCode, Query};
use trust_dns_proto::rr::{Name, RData, Record, RecordType};
use trust_dns_proto::serialize::binary::{BinDecodable, BinEncodable, BinEncoder};

pub async fn start(addr: &str) -> tokio::io::Result<()> {
    let socket = UdpSocket::bind(addr).await?;
    
}