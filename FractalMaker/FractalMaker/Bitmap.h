#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include "bitmapHeader.h"
#include "bitmapInfoHeader.h"
class Bitmap
{
public:
	Bitmap(int width, int height);
	void setPixel(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
	bool write(std::string filename);
	virtual~Bitmap();
private:
	int m_width{ 0 };
	int m_height{ 0 };
	std::unique_ptr<std::uint8_t> m_pixels{ nullptr };
};

