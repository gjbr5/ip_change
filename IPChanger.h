#pragma once
#include "CaptureListener.h"
#include <unordered_map>
#include "Packet.h"

class IPChanger : public CaptureListener
{
private:
	PortAddress trigger;
	IPAddress to_ip;
	std::unordered_map<SocketAddress, IPAddress> sessions;
	
public:
	virtual void onCaptured(uint8_t* packet, size_t length) final;
	IPChanger(PortAddress trigger, IPAddress to_ip);
};

