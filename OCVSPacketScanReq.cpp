#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacketScanReq.h"

OCVSPacketScanReq::OCVSPacketScanReq(bool debug)
	: content(debug ? SCAN_DEBUG : SCAN)
{
}

// TODO: This should actually verify the packet.
OCVSPacketScanReq::OCVSPacketScanReq(std::vector<char> &begin, int offset)
	: content(begin.at(offset)) // Single byte indicating the command.
{
}


OCVSPacketScanReq::~OCVSPacketScanReq()
{
}


void OCVSPacketScanReq::Pack(std::vector<char> &buff) const
{
	// Simply a single byte, 0x53
	buff.clear();
	buff.push_back(content);
}


size_t OCVSPacketScanReq::GetPackedSize() const
{
	// Fixed length of a single byte
	return 1;
}


bool OCVSPacketScanReq::DebugRequested() const
{
	switch (content)
	{
	case SCAN:
		return true;
	case SCAN_DEBUG:
		return false;
	default:
		// TODO: Should throw an exception
		return false;
	}
}
