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
	enum class ScanType { SCAN, SCAN_DEBUG, SCAN_INTERACTIVE };

	OCVSPacketScanReq(ScanType mode = ScanType::SCAN);

	OCVSPacketScanReq(std::vector<char> &begin, int offset);

	~OCVSPacketScanReq();

	void Pack(std::vector<char> &buff) const override;

	size_t GetPackedSize() const override;

	// TODO: Replace with enum get, verify on input.
	ScanType GetRequestType() const;

private:
	const unsigned char content;

	static unsigned char ScanTypeToContent(ScanType st);

	static const unsigned char CONTENT_SCAN = 0x53;
	static const unsigned char CONTENT_SCAN_DEBUG = 0x54;
	static const unsigned char CONTENT_SCAN_INTERACTIVE = 0x55;
};

