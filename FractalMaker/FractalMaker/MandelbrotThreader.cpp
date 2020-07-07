#include "pch.h"
#include <cstdint>
#include "MandelbrotThreader.h"
#include "Mandelbrot.h"

MandelbrotThreader::MandelbrotThreader()
{
}


MandelbrotThreader::~MandelbrotThreader()
{
}

void MandelbrotThreader::colourStripes(const int &HEIGHT, const int &WIDTH, int offset, int num_threads)
{
	for (int y = 0; y < HEIGHT; y += num_threads)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			double xfractal = (x - WIDTH * 2 / 3) *2.0 / HEIGHT;
			double yfractal = (y - HEIGHT / 2)*2.0 / HEIGHT;

			int iterations = Mandelbrot::GetIterations(xfractal, yfractal);
			double heat = (double)iterations / Mandelbrot::MAX_ITERATIONS;
			heat *= heat;
			heat *= heat;
			uint8_t violet = (uint8_t)(256 * heat);
			bitmap.setPixel(x, y, (uint8_t)violet, (uint8_t)violet / 3, (uint8_t)violet);
		}
	}
}