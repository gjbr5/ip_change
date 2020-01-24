#pragma once
#include "Packet/Ethernet.h"
#include "Packet/IPv4.h"
#include "Packet/Transport.h"

template<>
struct std::hash<MacAddress> { size_t operator()(const MacAddress& mac) const; };

template<>
struct std::hash<IPAddress> { size_t operator()(const IPAddress& ip) const; };

template<>
struct std::hash<PortAddress> { size_t operator()(const PortAddress& port) const; };

template<>
struct std::hash<SocketAddress> { size_t operator()(const SocketAddress& socket) const; };

template<>
struct std::hash<Flow> { size_t operator()(const Flow& flow) const; };
