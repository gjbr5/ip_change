#include "Transport.h"

#ifdef _WIN32
#include <WinSock2.h>
#elif __linux
#include <arpa/inet.h>
#endif

PortAddress::PortAddress() : address(0) {}
PortAddress::PortAddress(const uint16_t address) : address(htons(address)) {}
bool PortAddress::operator<(const PortAddress& o) const {
	return address < o.address;
}
bool PortAddress::operator==(const PortAddress& o) const {
	return address == o.address;
}
PortAddress::operator std::string() const {
	return std::to_string(ntohs(address));
}
std::ostream& operator<<(std::ostream& os, const PortAddress& port) {
	return os << std::string(port);
}

SocketAddress::SocketAddress() : ip(), port() {}
SocketAddress::SocketAddress(IPAddress ip, PortAddress port) : ip(ip), port(port) {}
bool SocketAddress::operator<(const SocketAddress& o) const {
	if (!(ip == o.ip))
		return ip < o.ip;
	return port < o.port;
}
bool SocketAddress::operator==(const SocketAddress& o) const {
	return ip == o.ip && port == o.port;
}

void TCPHeader::calcChecksum(IPAddress src_ip, IPAddress dst_ip, uint16_t tcp_len) {
	checksum = 0;

	// Pseudo Header
	struct
	{
		IPAddress src_ip;
		IPAddress dst_ip;
		uint8_t reserved = 0;
		IPProtocol protocol = IPProtocol::TCP;
		uint16_t tcp_len = 0;
	} ps_hdr;

	ps_hdr.src_ip = src_ip;
	ps_hdr.dst_ip = dst_ip;
	ps_hdr.tcp_len = htons(tcp_len);

	uint16_t result = 0;

	// Pseudo Checksum
	uint16_t* data = reinterpret_cast<uint16_t*>(&ps_hdr);
	size_t len = sizeof(ps_hdr);
	int i = len / 2;
	if (len & 1)
		result += ntohs(data[i] & 0x00ff);
	while (i--) {
		if (0xffff - ntohs(data[i]) < result)
			result++;
		result += ntohs(data[i]);
	}

	// TCP Segement Checksum
	data = reinterpret_cast<uint16_t*>(this);
	len = tcp_len;
	i = len / 2;
	if (len & 1) {
		if (0xffff - ntohs(data[i] & 0x00ff) < result)
			result++;
		result += ntohs(data[i] & 0x00ff);
	}
	while (i--) {
		if (0xffff - ntohs(data[i]) < result)
			result++;
		result += ntohs(data[i]);
	}
	checksum = htons(~result);
}

void UDPHeader::calcChecksum(IPAddress src_ip, IPAddress dst_ip, uint16_t udp_len) {
	checksum = 0;

	// Pseudo Header
	struct
	{
		IPAddress src_ip;
		IPAddress dst_ip;
		uint8_t reserved = 0;
		IPProtocol protocol = IPProtocol::UDP;
		uint16_t udp_len = 0;
	} ps_hdr;

	ps_hdr.src_ip = src_ip;
	ps_hdr.dst_ip = dst_ip;
	ps_hdr.udp_len = htons(udp_len);

	uint16_t result = 0;

	// Pseudo Checksum
	uint16_t* data = reinterpret_cast<uint16_t*>(&ps_hdr);
	size_t len = sizeof(ps_hdr);
	int i = len / 2;
	if (len & 1)
		result += ntohs(data[i] & 0x00ff);
	while (i--) {
		if (0xffff - ntohs(data[i]) < result)
			result++;
		result += ntohs(data[i]);
	}

	// UDP Segement Checksum
	data = reinterpret_cast<uint16_t*>(this);
	len = udp_len;
	i = len / 2;
	if (len & 1) {
		if (0xffff - ntohs(data[i] & 0x00ff) < result)
			result++;
		result += ntohs(data[i] & 0x00ff);
	}
	while (i--) {
		if (0xffff - ntohs(data[i]) < result)
			result++;
		result += ntohs(data[i]);
	}
	checksum = htons(~result);
}

Flow::Flow(SocketAddress src, SocketAddress dst, IPProtocol protocol)
	: src(src), dst(dst), protocol(protocol) {}
Flow::Flow(IPAddress src_ip, PortAddress src_port, IPAddress dst_ip, PortAddress dst_port, IPProtocol protocol)
	: src(src_ip, src_port), dst(dst_ip, dst_port), protocol(protocol) {}
Flow Flow::reverse() const { return Flow(dst, src, protocol); }
bool Flow::operator<(const Flow& o) const {
	if (!(src == o.src))
		return src < o.src;
	if (!(dst == o.dst))
		return dst < o.dst;
	return protocol < o.protocol;
}
bool Flow::operator==(const Flow& o) const {
	return src == o.src && dst == o.dst && protocol == o.protocol;
}
