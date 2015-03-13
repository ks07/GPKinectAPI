#pragma once

#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacket.h"

class OCVSPacketAck :
	public OCVSPacket
{
public:
	OCVSPacketAck();
	~OCVSPacketAck();

	void Pack(std::vector<char> &buff) const override;

	size_t GetPackedSize() const override;

	static const OCVSPacketAck *getInstance();

private:
	const char content = -1;

	static const OCVSPacketAck *static_instance;
};

