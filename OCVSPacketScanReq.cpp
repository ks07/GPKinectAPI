#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacketScanReq.h"

#include <stdexcept>

OCVSPacketScanReq::OCVSPacketScanReq(ScanType mode)
	: content(OCVSPacketScanReq::ScanTypeToContent(mode))
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


unsigned char OCVSPacketScanReq::ScanTypeToContent(OCVSPacketScanReq::ScanType st)
{
	switch (st)
	{
	case ScanType::SCAN:
		return CONTENT_SCAN;
	case ScanType::SCAN_DEBUG:
		return CONTENT_SCAN_DEBUG;
	case ScanType::SCAN_INTERACTIVE:
		return CONTENT_SCAN_INTERACTIVE;
	default:
		// The Unreal compiler complains without this!
		throw std::invalid_argument("Unsupport ScanType");
	}
}

OCVSPacketScanReq::ScanType OCVSPacketScanReq::GetRequestType() const
{
	switch (content)
	{
	case CONTENT_SCAN:
		return ScanType::SCAN;
	case CONTENT_SCAN_DEBUG:
		return ScanType::SCAN_DEBUG;
	case CONTENT_SCAN_INTERACTIVE:
		return ScanType::SCAN_INTERACTIVE;
	default:
		throw std::invalid_argument("Invalid Scan Request Packet");
	}
}
