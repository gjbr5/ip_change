#pragma once
#include <cstdint>

#ifdef __linux
#include <sys/types.h>
#endif

class CaptureListener
{
public:
	virtual void onCaptured(uint8_t* packet, size_t length) = 0;
};
