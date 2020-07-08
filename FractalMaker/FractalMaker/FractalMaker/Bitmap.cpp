#include "pch.h"
#include "Bitmap.h"
#include "bitmapHeader.h"
#include "bitmapInfoHeader.h"
#include <fstream>

using namespace std;

Bitmap::Bitmap(int width, int height) :
	m_width(width), m_height(height), m_pixels(
		new uint8_t[width * height * 3]{ }) {

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
	file.open(filename,ios::binary);
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

void Bitmap::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t* pixel = m_pixels.get();
	pixel += (m_width*y * 3) + x * 3;
	pixel[0] = b;
	pixel[1] = g;
	pixel[2] = r;
}


Bitmap::~Bitmap()
{
	//TODO
}
