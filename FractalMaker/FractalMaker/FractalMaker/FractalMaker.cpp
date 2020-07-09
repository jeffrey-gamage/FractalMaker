// FractalMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	fractalCreator.addZoom(292, 175, 0.1);
	fractalCreator.addZoom(514, 299, 0.1);
	fractalCreator.addColorRange(0.35, RGBColor(255, 100, 255));
	fractalCreator.run("mandelbrot.bmp");
	return 0;
}

