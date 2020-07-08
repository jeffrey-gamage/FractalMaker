#include "pch.h"
#include "Mandelbrot.h"
#include <complex>


Mandelbrot::Mandelbrot()
{
}


Mandelbrot::~Mandelbrot()
{
}

int Mandelbrot::GetIterations(double x, double y)
{
	int iterations = 0;

	std::complex<double> a = 0;
	std::complex<double> b(x,y);

	while (iterations < MAX_ITERATIONS)
	{
		a = a * a + b;
		if (abs(a) > 2)
		{
			break;
		}
		iterations++;
	}
	return iterations;
}
