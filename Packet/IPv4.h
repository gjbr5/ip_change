#pragma once
#include <cstdint>
#include <string>
#include <iostream>

typedef struct IPv4Address
{
	uint32_t address;
	IPv4Address();
	IPv4Address(uint32_t address);
	IPv4Address(const char* address);
	bool operator<(const IPv4Address& o) const;
	bool operator==(const IPv4Address& o) const;
	operator std::string() const;
	friend std::ostream& operator<<(std::ostream& os, const IPv4Address& ip);
} IPAddress;

typedef enum class IPProtocol : uint8_t
{
	IP = 0,	   /* Dummy protocol for TCP.  */
	ICMP = 1,	   /* Internet Control Message Protocol.  */
	IGMP = 2,	   /* Internet Group Management Protocol. */
	IPIP = 4,	   /* IPIP tunnels (older KA9Q tunnels use 94).  */
	TCP = 6,	   /* Transmission Control Protocol.  */
	EGP = 8,	   /* Exterior Gateway Protocol.  */
	PUP = 12,	   /* PUP protocol.  */
	UDP = 17,	   /* User Datagram Protocol.  */
	IDP = 22,	   /* XNS IDP protocol.  */
	TP = 29,	   /* SO Transport Protocol Class 4.  */
	DCCP = 33,	   /* Datagram Congestion Control Protocol.  */
	IPV6 = 41,     /* IPv6 header.  */
	RSVP = 46,	   /* Reservation Protocol.  */
	GRE = 47,	   /* General Routing Encapsulation.  */
	ESP = 50,      /* encapsulating security payload.  */
	AH = 51,       /* authentication header.  */
	MTP = 92,	   /* Multicast Transport Protocol.  */
	BEETPH = 94,   /* IP option pseudo header for BEET.  */
	ENCAP = 98,	   /* Encapsulation Header.  */
	PIM = 103,	   /* Protocol Independent Multicast.  */
	COMP = 108,	   /* Compression Header Protocol.  */
	SCTP = 132,	   /* Stream Control Transmission Protocol.  */
	UDPLITE = 136, /* UDP-Lite protocol.  */
	MPLS = 137,    /* MPLS in IP.  */
	RAW = 255,	   /* Raw IP packets.  */
} IPProtocol;

typedef struct IPHeader
{
	uint8_t hdr_len : 4;
	uint8_t version : 4;
	uint8_t tos;
	uint16_t tot_len;
	uint16_t id;
	uint16_t frag_off;
	uint8_t ttl;
	IPProtocol protocol;
	uint16_t checksum;
	IPAddress src_addr;
	IPAddress dst_addr;
	void calcChecksum();
} IPHeader;