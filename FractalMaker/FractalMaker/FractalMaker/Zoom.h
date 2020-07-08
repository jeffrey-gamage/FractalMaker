#pragma once
struct Zoom
{
public:
	Zoom(int x, int y, double scale);
	~Zoom();

	int m_x{ 0 };
	int m_y{ 0 };
	double m_scale{ 0 };
};

