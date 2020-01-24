TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lnetfilter_queue

SOURCES += \
    Main.cpp \
    IPChanger.cpp \
    Capture.cpp \
    NetfilterCapture.cpp \
    Packet.cpp \
    Packet/Ethernet.cpp \
    Packet/IPv4.cpp \
    Packet/Transport.cpp
    WinDivertCapture.cpp \

HEADERS += \
    IPChanger.h \
    Capture.h \
    CaptureListener.h \
    IPChanger.h \
    NetfilterCapture.h \
    Packet.h \
    Packet/Ethernet.h \
    Packet/IPv4.h \
    Packet/Transport.h \
    WinDivertCapture.h \
    windivert.h
