#include <iostream>
#include "FractalCreator.h"
#include "Mandelbrot.h"

FractalCreator::FractalCreator(int width, int height): m_width(width),
	m_height(height), 
	m_iterationHistogram(new int[Mandelbrot::MAX_ITERATIONS]{}), 
	m_iterationMap(new int[width * height]{}),
	m_zoomlist(width,height),
	m_bitmap(width,height)
{
	
}

FractalCreator::~FractalCreator()
{
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
				m_bitmap.setPixel(x, y, (uint8_t)std::pow(255, hue), (uint8_t)std::pow(100, hue), (uint8_t)std::pow(255, hue));
			}
		}
	}
}

void FractalCreator::addZoom(const Zoom& zoom)
{
	m_zoomlist.add(zoom);
}

void FractalCreator::writeBitmap(std::string name)
{
	m_bitmap.write(name);
}
