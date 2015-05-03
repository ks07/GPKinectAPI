#pragma once

#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacket.h"

#include <cstdint>
#include <vector>

class OCVSPacketMarker :
	public OCVSPacket
{
public:
	OCVSPacketMarker(uint8_t id, float centre_x, float centre_y);

    OCVSPacketMarker(std::vector<char> &begin);

	~OCVSPacketMarker();

	void Pack(std::vector<char> &buff) const override;

	size_t GetPackedSize() const override;

    // TODO: Getters
	uint8_t id;
	float centre_x;
	float centre_y;
};
