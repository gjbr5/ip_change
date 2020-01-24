#pragma once
#include <cstdint>

#ifdef __linux
#include <sys/types.h>
#endif

typedef struct MacAddress
{
	static constexpr size_t ADDRLEN = 6;
	uint8_t address[ADDRLEN];
	bool operator<(const MacAddress& o) const;
	bool operator==(const MacAddress& o) const;
} MacAddress;

typedef enum class EtherType : uint16_t
{
	PUP = 0x0200,		/* Xerox PUP */
	SPRITE = 0x0500,	/* Sprite */
	IP = 0x0800,		/* IP */
	ARP = 0x0806,		/* Address resolution */
	REVARP = 0x8035,	/* Reverse ARP */
	AT = 0x809B,		/* AppleTalk protocol */
	AARP = 0x80F3,	/* AppleTalk ARP */
	VLAN = 0x8100,	/* IEEE 802.1Q VLAN tagging */
	IPX = 0x8137,		/* IPX */
	IPV6 = 0x86dd,	/* IP protocol version 6 */
	LOOPBACK = 0x9000	/* used to test interfaces */
} EtherType;

typedef struct EthernetHeader
{
	MacAddress dhost;
	MacAddress shost;
	EtherType type;
} EthernetHeader;
