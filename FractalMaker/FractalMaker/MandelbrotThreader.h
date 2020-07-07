#pragma once

class MandelbrotThreader
{
public:
	MandelbrotThreader();
	~MandelbrotThreader();
	static void colourStripes(const int &HEIGHT, const int &WIDTH, int offset, int num_threads);
};

