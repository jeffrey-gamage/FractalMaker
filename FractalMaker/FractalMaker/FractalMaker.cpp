// FractalMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <thread>
#include <memory>
#include <utility>
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "Zoom.h"
#include "Bitmap.h"
#include "FractalMaker.h"



int main()
{

	const int WIDTH = 800;
	const int HEIGHT = 600;

	ZoomList zoomlist(WIDTH, HEIGHT);
	zoomlist.add(Zoom(WIDTH / 2, HEIGHT / 2, 4.0 / WIDTH));
	zoomlist.add(Zoom(369, HEIGHT - 93, 0.1));

	Bitmap bitmap(WIDTH, HEIGHT);
	std::unique_ptr<int[]> iterationHistogram(new int[Mandelbrot::MAX_ITERATIONS]{});
	std::unique_ptr<int[]> iterationMap(new int[WIDTH*HEIGHT]{});

	for (int y = 0; y < HEIGHT; y ++)
	{
		std::cout << "calculating row " << y << std::endl;
		for (int x = 0; x < WIDTH; x++)
		{
			std::pair<double,double> fractalCoords = zoomlist.doZoom(x, y);
			int iterations = Mandelbrot::GetIterations(fractalCoords.first, fractalCoords.second);
			iterationMap[y*WIDTH + x] = iterations;
			if (iterations < Mandelbrot::MAX_ITERATIONS)
			{
				iterationHistogram[iterations]++;
			}
		}
	}

	int histogramSum = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
	{
		histogramSum += iterationHistogram[i];
	}
	for (int y = 0; y < HEIGHT; y++)
	{
		std::cout << "painting row "<< y << std::endl;
		for (int x = 0; x < WIDTH; x++)
		{
			double hue = 0.0;
			int iterations = iterationMap[y*WIDTH + x];
			if (iterations < Mandelbrot::MAX_ITERATIONS)
			{
				for (int i = 0; i < iterations; i++)
				{
					hue += ((double)iterationHistogram[i]) / histogramSum;
				}
				bitmap.setPixel(x, y, (uint8_t) std::pow(255,hue), (uint8_t) std::pow(100,hue), (uint8_t) std::pow(255,hue));
			}
		}
	}

	bitmap.write("mandelbrot.bmp");
    std::cout << "Finished!\n"; 
	return 0;
}

