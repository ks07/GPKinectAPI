#pragma once

#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacket.h"

#include <vector>

class OCVSPacketScanReq :
	public OCVSPacket
{
public:
	OCVSPacketScanReq(bool debug = false);

	OCVSPacketScanReq(std::vector<char> &begin, int offset);

	~OCVSPacketScanReq();

	void Pack(std::vector<char> &buff) const override;

	size_t GetPackedSize() const override;

	// TODO: Replace with enum get, verify on input.
	bool DebugRequested() const;

private:
	const unsigned char content;

	static const unsigned char SCAN = 0x53;
	static const unsigned char SCAN_DEBUG = 0x54;
};

