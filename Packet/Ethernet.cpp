#include "Ethernet.h"
#include <cstring>

bool MacAddress::operator<(const MacAddress& o) const {
	return memcmp(address, o.address, MacAddress::ADDRLEN) < 0;
}
bool MacAddress::operator==(const MacAddress& o) const {
	return memcmp(address, o.address, MacAddress::ADDRLEN) == 0;
}
