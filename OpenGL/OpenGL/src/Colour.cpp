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

