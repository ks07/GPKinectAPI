#pragma once

#ifdef IN_UE4
#include "GPProject.h"
#endif

#define OCVS_PROTOCOL_VERSION (unsigned char)0x02;

#include <vector>

class OCVSPacket
{
public:
	//OCVSPacket();
	virtual ~OCVSPacket();

	virtual void Pack(std::vector<char> &buff) const = 0; // Set to null to be pure virtual

	virtual size_t GetPackedSize() const = 0;

	static const unsigned char ProtocolVersion = OCVS_PROTOCOL_VERSION;
};

