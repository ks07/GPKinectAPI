#ifdef IN_UE4
#include "GPProject.h"
#endif

#include "OCVSPacketMarker.h"

#ifndef IN_UE4
#include <cassert>
#endif

OCVSPacketMarker::OCVSPacketMarker(uint8_t id, float centre_x, float centre_y)
	: id(id)
	, centre_x(centre_x)
	, centre_y(centre_y)
{
}

// This is not the way to pass an iterator. TODO: NOPE NOPE NOPE
OCVSPacketMarker::OCVSPacketMarker(std::vector<char> &begin)
{
	// ID, 2 floats.
	std::vector<char>::iterator it = begin.begin();

	// Get id
	id = *it;
	it++;

	// Get pointer and interpret as float.
	float *thefloat;
	thefloat = reinterpret_cast<float *>(&(*it));
	centre_x = *thefloat;

	it += sizeof(float);

	thefloat = reinterpret_cast<float *>(&(*it));
	centre_y = *thefloat;
}

OCVSPacketMarker::~OCVSPacketMarker()
{
}


void OCVSPacketMarker::Pack(std::vector<char> &buff) const
{
	buff.clear();

	// Send the id
    buff.push_back(id);

	// Send the centre
	asBytes = reinterpret_cast<const char *>(&centre_x);
	buff.insert(buff.end(), asBytes, asBytes + sizeof(centre_x));
	asBytes = reinterpret_cast<const char *>(&centre_y);
	buff.insert(buff.end(), asBytes, asBytes + sizeof(centre_y));

	//assert(buff.size() == GetPackedSize());
}


size_t OCVSPacketMarker::GetPackedSize() const
{
	// Fixed length of one 8 bit field, 2 32 bit floats
	return 9;
}
