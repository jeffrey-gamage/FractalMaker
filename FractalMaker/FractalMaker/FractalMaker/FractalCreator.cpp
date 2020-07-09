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
	int histogramSum = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
	{
		histogramSum += m_iterationHistogram[i];
	}
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			double hue = 0.0;
			int iterations = m_iterationMap[y * m_width+ x];
			if (iterations < Mandelbrot::MAX_ITERATIONS)
			{
				for (int i = 0; i < iterations; i++)
				{
					hue += ((double)m_iterationHistogram[i]) / histogramSum;
				}
				int colourIndex = 0;
				double rangeSum = m_colorRangeIntervals[colourIndex];
				while (rangeSum < hue)
				{
					colourIndex++;
					rangeSum += m_colorRangeIntervals[colourIndex];
				}
				m_colorRangePixelCounts[colourIndex]++;
				RGBColor startColor = m_colors[colourIndex];
				RGBColor endColor = m_colors[colourIndex + 1];
				RGBColor colorDiff = endColor - startColor;
				hue -= rangeSum - m_colorRangeIntervals[colourIndex];
				m_bitmap.setPixel(x, y, startColor.r+colorDiff.r*hue, startColor.g+colorDiff.g*hue, startColor.b+colorDiff.b*hue);
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

void FractalCreator::printColorRangePixelCounts()
{
	for (int pixelCount : m_colorRangePixelCounts)
	{
		std::cout << pixelCount << std::endl;
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
