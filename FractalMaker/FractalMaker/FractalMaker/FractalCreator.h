#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Zoom.h"
#include "ZoomList.h"
#include "Bitmap.h"
#include "RGBColor.h"

class FractalCreator
{
public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator();

	void run(std::string filename);
	void calculateIteration();
	void drawFractal();
	void addZoom(int x, int y, double scale);
	void addColorRange(double rangeInterval, RGBColor endColor);
	void writeBitmap(std::string name);
	void calculateColorRangePixelCounts();
private:
	void sanitizeColorInputs();
	void normalizeColorIntervals();
	void enforceColorGradient();
	int getRangeMaximumIterations(int rangeIndex) const;
	int getRangeMinimumIterations(int rangeIndex) const;
	int getRangeIndex(int iterations) const;
	Bitmap m_bitmap;
	ZoomList m_zoomlist; 
	std::unique_ptr<int[]> m_iterationHistogram;
	std::unique_ptr<int[]> m_iterationMap;
	int m_width;
	int m_height;
	std::vector<double> m_colorRangeIntervals;
	std::vector<RGBColor> m_colors;
	std::vector<int> m_colorRangePixelCounts;
};

