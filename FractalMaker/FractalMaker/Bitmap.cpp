#include "pch.h"
#include "Bitmap.h"
#include "bitmapHeader.h"
#include "bitmapInfoHeader.h"
#include <fstream>


Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height), m_pixels(new std::uint8_t[width*height * 3]{})
{

}


void Bitmap::setPixel(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	//TODO
}

bool Bitmap::write(std::string filename)
{
	BitmapHeader fileheader;
	BitmapInfoHeader bmpInfoHeader;

	fileheader.filesize = sizeof(fileheader) + sizeof(bmpInfoHeader) + m_width * m_height * 3;
	fileheader.data_offset = sizeof(fileheader) + sizeof(bmpInfoHeader);
	bmpInfoHeader.height = m_height;
	bmpInfoHeader.width = m_width;

	std::ofstream file;
	file.open(filename);
	if (file.is_open())
	{
		file.write((char*)&fileheader,sizeof(fileheader));
		file.write((char*)&bmpInfoHeader,sizeof(bmpInfoHeader));
		file.write((char*)m_pixels.get(), m_width*m_height * 3);
		file.close();
		return true;
	}
	return false;
}

Bitmap::~Bitmap()
{
	//TODO
}
