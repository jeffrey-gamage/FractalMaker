#pragma once
struct Zoom
{
public:
	Zoom(int x, int y, double scale);
	~Zoom();

	int m_x;
	int m_y;
	double m_scale;
};

