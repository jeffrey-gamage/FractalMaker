#include <iostream>
#include "FractalCreator.h"
#include "Mandelbrot.h"
#include "RGBColor.h"

FractalCreator::FractalCreator(int width, int height): m_width(width),
	m_height(height), 
	m_iterationHistogram(new int[Mandelbrot::MAX_ITERATIONS]{}), 
	m_iterationMap(new int[width * height]{}),
	m_zoomlist(width,height),
	m_bitmap(width,height)
{
	addZoom(m_width / 2, m_height / 2, 4.0 / m_width);
	m_colors.push_back(RGBColor(0, 0, 0));
}

FractalCreator::~FractalCreator()
{
}

void FractalCreator::run(std::string filename)
{
	sanitizeColorInputs();
	calculateIteration();
	calculateColorRangePixelCounts();
	drawFractal();
	writeBitmap(filename);
	std::cout << "Finished!\n";
}

void FractalCreator::calculateIteration()
{
	for (int y = 0; y < m_height; y++)
	{
		std::cout << "calculating row " << y << std::endl;
		for (int x = 0; x < m_width; x++)
		{
			std::pair<double, double> fractalCoords = m_zoomlist.doZoom(x, y);
			int iterations = Mandelbrot::GetIterations(fractalCoords.first, fractalCoords.second);
			m_iterationMap[y * m_width+x] = iterations;
			if (iterations < Mandelbrot::MAX_ITERATIONS)
			{
				m_iterationHistogram[iterations]++;
			}
		}
	}
}

void FractalCreator::drawFractal()
{
	for (int y = 0; y < m_height; y++)
	{
		std::cout << "drawing row " << y << std::endl;
		for (int x = 0; x < m_width; x++)
		{
			int iterations = m_iterationMap[y * m_width+ x];
			int color_range_index = getRangeIndex(iterations);
			int range_pixel_count = m_colorRangePixelCounts[color_range_index];
			int range_start = getRangeMinimumIterations(color_range_index);

			RGBColor startColor = m_colors[color_range_index];
			RGBColor endColor = m_colors[color_range_index + 1];
			RGBColor colorDiff = endColor - startColor;
			if (iterations < Mandelbrot::MAX_ITERATIONS)
			{
				int totalPixels = 0;
				for (int i =range_start; i < iterations; i++)
				{
					totalPixels += m_iterationHistogram[i];
				}
				uint8_t r = startColor.r + colorDiff.r * (double)totalPixels / range_pixel_count;
				uint8_t g = startColor.g + colorDiff.g * (double)totalPixels / range_pixel_count;
				uint8_t b = startColor.b + colorDiff.b * (double)totalPixels / range_pixel_count;
				m_bitmap.setPixel(x, y, r, g, b);
			}
		}
	}
}

void FractalCreator::addZoom(int x, int y, double scale)
{
	//y cooordinate inverted to match ms paint coordinates
	m_zoomlist.add(Zoom(x,m_height-y,scale));
}

/*before running, range intervals will be normalized to sum to one. if no range intervals are added, the plot will be rendered in greyscale*/
void FractalCreator::addColorRange(double rangeInterval, RGBColor endColor)
{
	m_colorRangeIntervals.push_back(rangeInterval);
	m_colors.push_back(endColor);
	m_colorRangePixelCounts.push_back(0);
}

void FractalCreator::writeBitmap(std::string name)
{
	m_bitmap.write(name);
}

void FractalCreator::calculateColorRangePixelCounts()
{
	int range_index = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
	{
		int num_pixels = m_iterationHistogram[i];
		if (i > getRangeMaximumIterations(range_index))
		{
			range_index++;
		}
		m_colorRangePixelCounts[range_index] += num_pixels;
	}
}


//ensures range intervals are safe to run by making sure the range sums to one and there are a least two colors to derive a gradient
void FractalCreator::sanitizeColorInputs()
{
	enforceColorGradient();
	normalizeColorIntervals();
}

void FractalCreator::normalizeColorIntervals()
{
	double intervalSum = 0.0;
	for (double colorInterval : m_colorRangeIntervals)
	{
		intervalSum += colorInterval;
	}	
	for (int i=0;i<m_colorRangeIntervals.size();i++)
	{
		 m_colorRangeIntervals[i] /= intervalSum;
	}
}

void FractalCreator::enforceColorGradient()
{
	if (m_colors.size() <= 1)
	{
		addColorRange(1.0, RGBColor(255, 255, 255));
	}
}

//returns the hightest pixel count included in the indexed range
int FractalCreator::getRangeMaximumIterations(int rangeIndex) const
{
	float rangeMaximumFraction = 0.0;
	for (int i = 0; i <= rangeIndex; i++)
	{
		rangeMaximumFraction += m_colorRangeIntervals[i];
	}
	return rangeMaximumFraction * Mandelbrot::MAX_ITERATIONS;
}
int FractalCreator::getRangeMinimumIterations(int rangeIndex) const
{
	if (rangeIndex == 0)
	{
		return 0;
	}
	else
	{
		return getRangeMaximumIterations(rangeIndex - 1) + 1;
	}
}
//returns the color range into which the passed number of iterations falls
int FractalCreator::getRangeIndex(int iterations) const
{
	for (int i = 0; i < m_colorRangeIntervals.size(); i++)
	{
		if (getRangeMaximumIterations(i) >= iterations)
		{
			return i;
		}
	}
	return m_colorRangeIntervals.size() - 1;
}
