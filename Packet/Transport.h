#pragma once
#include "IPv4.h"
#include <cstdint>
#include <iostream>
#include <functional>

typedef struct PortAddress {
	uint16_t address;
	PortAddress();
	PortAddress(uint16_t address);
	bool operator<(const PortAddress& o) const;
	bool operator==(const PortAddress& o) const;
	operator std::string() const;
	friend std::ostream& operator<<(std::ostream& os, const PortAddress& port);
} PortAddress;


typedef struct SocketAddress
{
	IPv4Address ip;
	PortAddress port;
	SocketAddress(IPAddress ip, PortAddress port);
	SocketAddress();
	bool operator<(const SocketAddress& o) const;
	bool operator==(const SocketAddress& o) const;
} SocketAddress;


typedef struct TCPHeader
{
	PortAddress src_port;
	PortAddress dst_port;
	uint32_t seq_num;
	uint32_t ack_num;
	uint16_t reserved1 : 4;
	uint16_t offset : 4;
	uint16_t flg_fin : 1;
	uint16_t flg_syn : 1;
	uint16_t flg_rst : 1;
	uint16_t flg_psh : 1;
	uint16_t flg_ack : 1;
	uint16_t flg_urg : 1;
	uint16_t reserved2 : 2;
	uint16_t window;
	uint16_t checksum;
	uint16_t urg_ptr;
	void calcChecksum(IPAddress src_ip, IPAddress dst_ip, uint16_t tcp_len);
} TCPHeader;

typedef struct UDPHeader
{
	PortAddress src_port;
	PortAddress dst_port;
	uint16_t length;
	uint16_t checksum;
	void calcChecksum(IPAddress src_ip, IPAddress dst_ip, uint16_t udp_len);
} UDPHeader;

class Flow
{
private:
	SocketAddress src;
	SocketAddress dst;
	IPProtocol protocol;

public:
	Flow(IPAddress src_ip, PortAddress src_port, IPAddress dst_ip, PortAddress dst_port, IPProtocol protocol);
	Flow(SocketAddress src, SocketAddress dst, IPProtocol protocol);
	Flow reverse() const;
	bool operator<(const Flow& o) const;
	bool operator==(const Flow& o) const;

	friend std::hash<Flow>;
};