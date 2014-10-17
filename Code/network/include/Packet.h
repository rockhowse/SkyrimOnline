#ifndef NETWORK_PACKET_H
#define NETWORK_PACKET_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "Buffer.h"

class Packet
{
public:

	uint16_t connectionId;

	Packet() {};
	virtual ~Packet() {}

	virtual void Deserialize(ReadBuffer* pBuffer) = 0;
	virtual void Serialize(WriteBuffer* pBuffer) = 0;

private:
};

#endif // NETWORK_PACKET_H