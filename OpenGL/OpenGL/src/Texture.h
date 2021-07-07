#pragma once
#include "Renderer.h"



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
			h = 60.0f * (fmod(((green - blue) / delta), 6.0f));
		}
		else if (Cmax == green)
		{
			h = 60.0f * (((blue - red) / delta) + 2.0f);
		}
		else if (Cmax == blue)
		{
			h = 60.0f * (((red - green) / delta) + 4.0f);
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
	h = std::max(0.0f, h);
	s = std::max(0.0f, s);
	v = std::max(0.0f, v);
	h = std::min(359.99f, h);
	s = std::min(1.0f, s);
	v = std::min(1.0f, v);


	float C = v * s;
	float X = C * (1.0f - fabs(fmod(h / 60.0f, 2) - 1.0f));
	float m = v - C;
	float r_prime, g_prime, b_prime;
	/*ASSERT(0 <= h < 360);*/

	if (0.0f <= h && h < 60)
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
	else if (180 <= h && h < 240)
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
	r = std::round((r_prime + m) * 255.0f);
	g = std::round((g_prime + m) * 255.0f);
	b = std::round((b_prime + m) * 255.0f);
}




class Texture
{
private:
	unsigned int	m_rendererID;
	std::string		m_filePath;
	unsigned char*	m_localBuffer;
	unsigned char*	m_buffer;
	int m_width, m_height, m_BPP;


public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	void updateTexture(float h, float s, float v);
	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
};