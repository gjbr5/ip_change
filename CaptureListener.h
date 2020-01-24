#pragma once
#include <cstdint>

class CaptureListener
{
public:
	virtual void onCaptured(uint8_t* packet, size_t length) = 0;
};
