#pragma once
#include <cstdint>

#pragma pack(push,2)
struct BitmapInfoHeader
{
	std::int32_t header_size{ 40 };
	std::int32_t width;
	std::int32_t height;
	std::int16_t planes{ 1 };
	std::int16_t bits_per_pixel{ 24 };
	std::int32_t compression{ 0 };
	std::int32_t data_size;
	std::int32_t horizontal_resolution{ 2400 };
	std::int32_t vertical_resolution{ 2400 };
	std::int32_t colors{ 0 };
	std::int32_t important_colors{ 0 };
};
#pragma pack(pop)

