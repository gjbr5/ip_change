#include "IPChanger.h"
#include <iostream>

IPChanger::IPChanger(PortAddress trigger, IPAddress to_ip) : trigger(trigger), to_ip(to_ip) {}

void IPChanger::onCaptured(uint8_t* packet, size_t length) {
	// Get IP and Port
	IPHeader *iphdr = reinterpret_cast<IPHeader*>(packet);
	
	PortAddress src_port, dst_port;
	if (iphdr->protocol == IPProtocol::TCP) {
		TCPHeader* tcphdr = reinterpret_cast<TCPHeader*>(packet + (iphdr->hdr_len << 2));
		src_port = tcphdr->src_port;
		dst_port = tcphdr->dst_port;
	}
	else if (iphdr->protocol == IPProtocol::UDP) {
		UDPHeader* udphdr = reinterpret_cast<UDPHeader*>(packet + (iphdr->hdr_len << 2));
		src_port = udphdr->src_port;
		dst_port = udphdr->dst_port;
	}
	else
		return;

	// Modify IP
	if (dst_port == trigger && !(iphdr->src_addr == to_ip)) {
		// --->
		sessions.insert(std::make_pair(SocketAddress(iphdr->src_addr, src_port), iphdr->dst_addr));
		std::cout << iphdr->src_addr << ":" << src_port << " -> " << iphdr->dst_addr << ":" << dst_port
			<< " to " << iphdr->src_addr << ":" << src_port << " -> " << to_ip << ":" << dst_port << '\n';
		iphdr->dst_addr = to_ip;
	}
	else if (iphdr->src_addr == to_ip && src_port == trigger) {
		// <---
		auto server = sessions.find(SocketAddress(iphdr->dst_addr, dst_port));
		if (server == sessions.end())
			return;
		std::cout << iphdr->dst_addr << ":" << dst_port << " <- " << iphdr->src_addr << ":" << src_port
			<< " to " << iphdr->dst_addr << ":" << dst_port << " <- " << server->second << ":" << src_port << '\n';
		iphdr->src_addr = server->second;
	}
	else
		return;
	
	// Recalculate Checksum
	if (iphdr->protocol == IPProtocol::TCP) {
		TCPHeader* tcphdr = reinterpret_cast<TCPHeader*>(packet + (iphdr->hdr_len << 2));
		uint16_t tcp_len = static_cast<uint16_t>(length - (iphdr->hdr_len << 2));
		tcphdr->calcChecksum(iphdr->src_addr, iphdr->dst_addr, tcp_len);
	}
	else if (iphdr->protocol == IPProtocol::UDP) {
		UDPHeader* udphdr = reinterpret_cast<UDPHeader*>(packet + (iphdr->hdr_len << 2));
		uint16_t udp_len = static_cast<uint16_t>(length - (iphdr->hdr_len << 2));
		udphdr->calcChecksum(iphdr->src_addr, iphdr->dst_addr, udp_len);
	}
	iphdr->calcChecksum();
}