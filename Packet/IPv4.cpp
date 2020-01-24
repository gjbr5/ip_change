#include "IPv4.h"

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif

IPv4Address::IPv4Address() : address(0) {}
IPv4Address::IPv4Address(uint32_t address) : address(address) {}
IPv4Address::IPv4Address(const char* address) : address(0) {
	inet_pton(AF_INET, address, &this->address);
}
bool IPv4Address::operator<(const IPv4Address& o) const {
	return address < o.address;
}
bool IPv4Address::operator==(const IPv4Address& o) const {
	return address == o.address;
}
IPv4Address::operator std::string() const {
	char buffer[16];
	inet_ntop(AF_INET, &address, buffer, 16);
	return buffer;
}
std::ostream& operator<<(std::ostream& os, const IPv4Address& ip) {
	return os << std::string(ip);
}
void IPHeader::calcChecksum() {
	checksum = 0;
	uint16_t* data = reinterpret_cast<uint16_t*>(this);
	size_t len = hdr_len << 2;
	int i = len / 2;

	uint16_t result = 0;
	if (len & 1)
		result = ntohs(data[i] & 0x00ff);

	while (i--) {
		if (0xffff - ntohs(data[i]) < result)
			result++;
		result += ntohs(data[i]);
	}
	checksum = htons(~result);
}