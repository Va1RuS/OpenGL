#include "Colour.h"

Colour::Colour(float r, float g, float b, float a)
{
	m_red = r;
	m_green = g;
	m_blue = b;
	m_alpha = a;

}
Colour::Colour()
{
	//m_red = 1;
	//m_green = 1;
	//m_blue = 1;
	//m_alpha = 1;

}

Colour::Colour(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	m_red = (float)(r % 0x100) / 0xff;
	m_green = (float)(g % 0x100) / 0xff;
	m_blue = (float)(b % 0x100) / 0xff;
	m_alpha = (float)(a % 0x100) / 0xff;

}

void RGBtoHSV(unsigned char& r, unsigned char& g, unsigned char& b, float& h, float& s, float& v)
{
	float red = (float)(r % 0x100) / 0xff;
	float green = (float)(g % 0x100) / 0xff;
	float blue = (float)(b % 0x100) / 0xff;

	float Cmax = std::max(std::max(red, green), blue);
	float Cmin = std::min(std::min(red, green), blue);
	float delta = Cmax - Cmin;
	h = 0;
	s = 0;
	v = Cmax;
	if (delta > 0)
	{
		if (Cmax == red)
		{
			h = 60 * (fmod(((green - blue) / delta), 6));
		}
		else if (Cmax == green)
		{
			h = 60 * (((blue - red) / delta) + 2);
		}
		else if (Cmax == blue)
		{
			h = 60 * (((red - green) / delta) + 4);
		}

		if (Cmax != 0)
		{
			s = delta / Cmax;
		}
		else {
			s = 0;
		}
	}
	if (h < 0) {
		h = 360 + h;
	}
}



void HSVtoRGB(float& h, float& s, float& v, unsigned char& r, unsigned char& g, unsigned char& b)
{
	float C = v * s;
	float X = C * (1 - fabs(fmod(h / 60.0f, 2) - 1));
	float m = v - C;
	float r_prime, g_prime, b_prime;
	/*ASSERT(0 <= h < 360);*/

	if (0 <= h && h < 60)
	{
		r_prime = C;
		g_prime = X;
		b_prime = 0;
	}
	else if (60 <= h && h < 120)
	{
		r_prime = X;
		g_prime = C;
		b_prime = 0;
	}
	else if (120 <= h && h < 180)
	{
		r_prime = 0;
		g_prime = C;
		b_prime = X;
	}
	else if (180 <= h < 240)
	{
		r_prime = 0;
		g_prime = X;
		b_prime = C;
	}
	else if (240 <= h && h < 300)
	{
		r_prime = X;
		g_prime = 0;
		b_prime = C;
	}
	else if (300 <= h && h < 360)
	{
		r_prime = C;
		g_prime = 0;
		b_prime = X;
	}
	r = (r_prime + m) * 255;
	g = (g_prime + m) * 255;
	b = (b_prime + m) * 255;

}