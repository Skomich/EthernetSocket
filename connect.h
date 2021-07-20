#pragma once

#indlude "stdafx.h"
#include "resize_buffer.h"

class Connector {
public:
    virtual void Send(ResizeBuffer rBuffer);
    virtual DWORD Receive(rBuffer);
}

class Server : public Connector {
}
