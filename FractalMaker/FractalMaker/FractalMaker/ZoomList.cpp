#include "pch.h"
#include "ZoomList.h"


ZoomList::ZoomList(int width, int height): m_width(width), m_height(height),m_xcenter(0),m_ycenter(0)
{
}


ZoomList::~ZoomList()
{
}

std::pair<double, double> ZoomList::doZoom(int x, int y)
{
	double xFractal = (x - m_width / 2)*m_scale + m_xcenter;
	double yFractal = (y - m_height / 2)*m_scale + m_ycenter;

	return std::pair<double, double>(xFractal, yFractal);
}

void ZoomList::add(const Zoom& zoom)
{
	zooms.push_back(zoom);

	m_xcenter += (zoom.m_x - m_width / 2)*m_scale;
	m_ycenter += (zoom.m_y - m_height / 2)*m_scale;

	m_scale *= zoom.m_scale;
}
