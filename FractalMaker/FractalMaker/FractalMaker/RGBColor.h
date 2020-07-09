#pragma once
#include<cstdint>

struct RGBColor
{
	RGBColor();
	RGBColor(uint8_t red, uint8_t green, uint8_t blue);
	RGBColor operator-(RGBColor other);

	uint8_t r;
	uint8_t g;
	uint8_t b;
};

