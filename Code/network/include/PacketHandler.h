#ifndef NETWORK_PACKET_HANDLER_H
#define NETWORK_PACKET_HANDLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "Buffer.h"

class PacketHandler
{
public:

	PacketHandler() {};
	virtual ~PacketHandler() {};

	virtual void HandleBuffer(ReadBuffer* pBuffer, uint16_t aOpcode, uint16_t aConnectionId) = 0;

private:
};

#endif // NETWORK_PACKET_HANDLER_H