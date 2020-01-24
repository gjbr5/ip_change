#ifdef _WIN32
#include "WinDivertCapture.h"
#include <iostream>
#include <string>

WinDivertCapture::WinDivertCapture(std::string filter) : Capture(), handle(WinDivertOpen(filter.c_str(), WINDIVERT_LAYER_NETWORK, 0, 0)) {
	// Check Device Open
	if (handle == INVALID_HANDLE_VALUE)
		throw ("error: failed to open the WinDivert device ("
			+ std::to_string(GetLastError()) + ")");

	// Set Parameters
	if (!WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_LENGTH, WINDIVERT_PARAM_QUEUE_LENGTH_MAX)
		|| !WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_TIME, WINDIVERT_PARAM_QUEUE_TIME_MAX)
		|| !WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_SIZE, WINDIVERT_PARAM_QUEUE_SIZE_MAX))
		throw ("error: failed to set params ("
			+ std::to_string(GetLastError()) + ")");
}

WinDivertCapture::~WinDivertCapture() {
	// Close Handler
	WinDivertClose(handle);
}

void WinDivertCapture::next() {
	size_t packetLen;
	WINDIVERT_ADDRESS addr;
	if (!WinDivertRecv(handle, packetBuf, PACKETBUFSIZE, &packetLen, &addr)) {
		std::cerr << "warning: failed to read packet (" << GetLastError() << ")\n";
		return;
	}
	notify(packetBuf, packetLen);
	if (!WinDivertSend(handle, packetBuf, packetLen, nullptr, &addr)) {
		std::cerr << "WinDivertSend Failed\n";
	}
}

#endif