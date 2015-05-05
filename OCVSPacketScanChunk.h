#pragma once

#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacket.h"

#ifndef IN_UE4
#include <opencv2/opencv.hpp>
#endif

#include <cstdint>
#include <vector>

class OCVSPacketScanChunk :
	public OCVSPacket
{
public:
#ifndef IN_UE4
	OCVSPacketScanChunk(uint32_t index, cv::RotatedRect rect, uint8_t scale);
#endif

    OCVSPacketScanChunk(std::vector<char> &begin, int offset);

	~OCVSPacketScanChunk();

	void Pack(std::vector<char> &buff) const override;

	size_t GetPackedSize() const override;

    // TODO: Getters
	float centre_x;
	float centre_y;
	float rotation;
	float scale_x;
	float scale_y;
	uint8_t scale;

private:
	uint32_t index;
};
