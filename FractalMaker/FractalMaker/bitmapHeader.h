#pragma once
#include <cstdint>

#pragma pack(push,2)
struct BitmapHeader
{
	char header[2] = { 'B','M' };
	int32_t filesize;
	int32_t reserved{ 0 };
	int32_t data_offset;
};
#pragma pack(pop)

