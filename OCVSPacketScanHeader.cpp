#ifdef IN_UE4
#include "GPProject.h"
#include "AssertionMacros.h"
#endif IN_UE4

#include "OCVSPacketScanHeader.h"

#ifndef IN_UE4
#include <cassert>
#endif


OCVSPacketScanHeader::OCVSPacketScanHeader(uint8_t result)
	: result(result)
	, length(0)
	, chunk_count(0)
{
}



OCVSPacketScanHeader::OCVSPacketScanHeader(uint32_t length, uint8_t chunk_count)
	: result(RESULT_SUCCESS)
	, length(length)
	, chunk_count(chunk_count)
{
}


OCVSPacketScanHeader::OCVSPacketScanHeader(const std::vector<OCVSPacket *> &scanChunks)
	: result(RESULT_SUCCESS)
	, chunk_count(scanChunks.size())
{
	length = 0;
	
	for (auto &pkt : scanChunks)
	{
		length += pkt->GetPackedSize();
	}
}


OCVSPacketScanHeader::OCVSPacketScanHeader(const std::vector<char> &packet)
{
	int i = 0;
	// First byte is the result.
	result = packet.at(i);
	// Next 4 bytes are the length.
	// TODO: Cheeky reinterpret maybe???
	/*length = 0;
	for (i = sizeof(uint32_t); i >= 1; i--) {
		length = length << 8;
		length = length | packet.at(i);
	}*/
	length = *reinterpret_cast<const uint32_t *>(&(packet[1]));
	// Next byte is the number of chunks
	const int start = sizeof(uint32_t) + sizeof(uint8_t);
	chunk_count = 0;
	for (i = start; i > sizeof(uint32_t); i--) {
		chunk_count = chunk_count << 8;
		chunk_count = chunk_count | packet.at(i);
	}
	// TODO: Check!
}


OCVSPacketScanHeader::~OCVSPacketScanHeader()
{
}


void OCVSPacketScanHeader::Pack(std::vector<char> &buff) const
{
	buff.clear();

	// Send the result code.
	buff.push_back(result);

	const char *asBytes = reinterpret_cast<const char *>(&length);

	// Send the total length
	buff.insert(buff.end(), asBytes, asBytes+sizeof(length));

	asBytes = reinterpret_cast<const char *>(&chunk_count);

	// Send the chunk count
	buff.insert(buff.end(), asBytes, asBytes + sizeof(chunk_count));

#ifdef IN_UE4
	check(buff.size() == GetPackedSize());
#else
	assert(buff.size() == GetPackedSize());
#endif
}


size_t OCVSPacketScanHeader::GetPackedSize() const
{
	// Fixed length of two 8 bit fields and one 32 bit fields
	return 6;
}


uint32_t OCVSPacketScanHeader::GetChunkCount() const
{
	// TODO: Type crying!
	return chunk_count;
}


uint32_t OCVSPacketScanHeader::GetLength() const
{
	// TODO: Type crying!
	return length;
}
