// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <thread>
#include <string>
#include <memory>
#include <utility>
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "Zoom.h"
#include "Bitmap.h"
#include "FractalCreator.h"
#include "RGBColor.h"



int main()
{

	const int WIDTH = 800;
	const int HEIGHT = 600;
	FractalCreator fractalCreator(WIDTH, HEIGHT);
	fractalCreator.addColorRange(0.05, RGBColor(255, 99, 71));
	fractalCreator.addColorRange(0.03, RGBColor(255, 215, 0));
	fractalCreator.addColorRange(0.92, RGBColor(255, 255, 255));

	fractalCreator.addZoom(295, 202, 0.1);
	fractalCreator.addZoom(312, 304, 0.1);
	fractalCreator.run("mandelbrot.bmp");
	return 0;
}

