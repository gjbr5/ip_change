#pragma once
#include "Packet.h"
#include <functional>

template <class T>
static void hash_combine(size_t& seed, const T& v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

size_t std::hash<MacAddress>::operator()(const MacAddress& mac) const {
	size_t hash = std::hash<uint8_t>()(mac.address[0]);
	for (size_t i = 1; i < MacAddress::ADDRLEN; i++)
		hash_combine(hash, mac.address[i]);
	return hash;
}

size_t std::hash<IPAddress>::operator()(const IPAddress& ip) const {
	return std::hash<uint32_t>()(ip.address);
}

size_t std::hash<PortAddress>::operator()(const PortAddress& port) const {
	return std::hash<uint16_t>()(port.address);
}

size_t std::hash<SocketAddress>::operator()(const SocketAddress& socket) const {
	size_t hash = std::hash<IPAddress>()(socket.ip);
	hash_combine(hash, socket.port);
	return hash;
}

size_t std::hash<Flow>::operator()(const Flow& flow) const {
	size_t hash = std::hash<SocketAddress>()(flow.src);
	hash_combine(hash, flow.dst);
	hash_combine(hash, flow.protocol);
	return hash;
}
