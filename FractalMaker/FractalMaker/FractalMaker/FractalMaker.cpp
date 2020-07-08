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



int main()
{

	const int WIDTH = 800;
	const int HEIGHT = 600;

	FractalCreator fractalCreator(WIDTH,HEIGHT);
	fractalCreator.addZoom(Zoom(WIDTH / 2, HEIGHT / 2, 4.0 / WIDTH));
	fractalCreator.addZoom(Zoom(292, HEIGHT - 175, 0.1));
	fractalCreator.addZoom(Zoom(514, HEIGHT - 299, 0.1));
	fractalCreator.calculateIteration();
	fractalCreator.drawFractal();
	fractalCreator.writeBitmap("mandelbrot2.bmp");
    std::cout << "Finished!\n"; 
	return 0;
}

