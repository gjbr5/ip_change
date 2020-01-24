#include "Capture.h"

Capture::Capture() : packetBuf(new uint8_t[PACKETBUFSIZE]) {}

Capture::~Capture() {
	for (CaptureListener*& listener : listeners)
		delete listener;
	delete[] packetBuf;
}

void Capture::notify(uint8_t* packet, size_t length) {
	for (CaptureListener*& listener : listeners)
		listener->onCaptured(packet, length);
}

void Capture::addListener(CaptureListener* listener) {
	listeners.emplace_back(listener);
}

void Capture::removeListener(CaptureListener* listener) {
	listeners.remove(listener);
	delete listener;
}