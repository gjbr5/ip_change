#pragma once
#include "Capture.h"
#ifdef __WIN32
#include <string>
#include <Windows.h>
#include "windivert.h"

class WinDivertCapture : public Capture
{
private:
	HANDLE handle;

public:
	WinDivertCapture(std::string filter);
	~WinDivertCapture();
	virtual void next() final;
};
#endif
