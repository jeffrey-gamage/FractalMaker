#pragma once
#include <vector>
#include <utility>
#include "Zoom.h"

class ZoomList
{
public:
	ZoomList(int width, int height);
	~ZoomList();
	std::pair<double, double> doZoom(int x, int y);
	void add(const Zoom& zoom);

private:
	int m_width{ 0 };
	int m_height{ 0 };
	int m_xcenter;
	int m_ycenter;
	double m_scale{ 1.0 };
	std::vector<Zoom> zooms;

};

