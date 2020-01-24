#pragma once
#include <list>
#include <cstdint>
#include "CaptureListener.h"

class Capture
{
private:
	std::list<CaptureListener*> listeners;

protected:
	uint8_t* packetBuf;
	static constexpr size_t PACKETBUFSIZE = 0xffff;

protected:
	Capture();
	void notify(uint8_t* packet, size_t length);

public:
	void addListener(CaptureListener* listener);
	void removeListener(CaptureListener* listener);
	virtual void next() = 0;
	~Capture();
};
