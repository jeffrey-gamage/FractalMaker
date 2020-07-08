#pragma once
#include <string>
#include <memory>
#include "Zoom.h"
#include "ZoomList.h"
#include "Bitmap.h"

class FractalCreator
{
public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator();

	void calculateIteration();
	void drawFractal();
	void addZoom(const Zoom& zoom);
	void writeBitmap(std::string name);
private:
	Bitmap m_bitmap;
	ZoomList m_zoomlist; 
	std::unique_ptr<int[]> m_iterationHistogram;
	std::unique_ptr<int[]> m_iterationMap;
	int m_width;
	int m_height;
};

