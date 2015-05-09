#pragma once

#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacket.h"

class OCVSPacketChallenge :
	public OCVSPacket
{
public:
	OCVSPacketChallenge();

	OCVSPacketChallenge(unsigned char FloorScale, unsigned char TopScale);

	~OCVSPacketChallenge();

	void Pack(std::vector<char> &buff) const override;

	size_t GetPackedSize() const override;

	bool VerifyReceived(const std::vector<char> &buff, size_t len) const;
	bool VerifyReceived(const std::vector<char> &buff, size_t len, unsigned char &FloorScale, unsigned char &TopScale) const;

private:
	static const size_t PackedSize = 3;
	const unsigned char FloorScale;
	const unsigned char TopScale;
};
