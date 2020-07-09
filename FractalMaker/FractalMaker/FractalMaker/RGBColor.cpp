#include "RGBColor.h"

RGBColor::RGBColor(): r(0),g(0),b(0)
{
}

RGBColor::RGBColor(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue)
{
}

RGBColor RGBColor::operator-(RGBColor other)
{
	return RGBColor(r-other.r,g-other.g,b-other.b);
}
