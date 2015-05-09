#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacketChallenge.h"

OCVSPacketChallenge::OCVSPacketChallenge()
	: FloorScale(180),
	TopScale(10)
{
}


OCVSPacketChallenge::OCVSPacketChallenge(unsigned char FloorScale, unsigned char TopScale)
	: FloorScale(FloorScale),
	TopScale(TopScale)
{
}


OCVSPacketChallenge::~OCVSPacketChallenge()
{
}


void OCVSPacketChallenge::Pack(std::vector<char> &buff) const
{
	buff.clear();
	// Send the protcol version
	buff.push_back(ProtocolVersion);
	// Send scale values
	buff.push_back(FloorScale);
	buff.push_back(TopScale);
}


size_t OCVSPacketChallenge::GetPackedSize() const
{
	// Fixed length of a single byte followed by a 32 bit int
	return PackedSize;
}


bool OCVSPacketChallenge::VerifyReceived(const std::vector<char> &buff, size_t len) const
{
	if (len != PackedSize) {
		return false;
	}

	return buff.at(0) == ProtocolVersion;
}

bool OCVSPacketChallenge::VerifyReceived(const std::vector<char> &buff, size_t len, unsigned char &FloorScale, unsigned char &TopScale) const
{
	if (VerifyReceived(buff, len)) {
		FloorScale = buff.at(1);
		TopScale = buff.at(2);
		return true;
	}
	else {
		return false;
	}
}
