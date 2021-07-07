// (c) Nucoda Limited 2002
#pragma once

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Renderer.h"






class Colour
{
private:
	float	m_red;
	float	m_green;
	float	m_blue;
	float	m_alpha;

public:

	Colour();
	Colour(float r, float g, float b, float a = 1.0f);
	Colour(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);
	
	
	/*void RGBtoHSV(float& r, float& g, float &b, float& h, float& s, float& v);
	void RGBtoHSV(int r, int g, int b, float& h, float& s, float& v);
	void HSVtoRGB(float& h, float& s, float& v, float& r, float& g, float& b);*/
	
	
	
	//void		set(float r, float g, float b, float a = 1.0f);
	//void		setDebugColour(int index);

	//void		getRGBBytes(uint8& r, uint8& g, uint8& b) const;
	//void		getRGB(uint8& r, uint8& g, uint8& b) const;
	//void		getRGB(float& r, float& g, float& b) const;

	//void		getRGBABytes(uint8& r, uint8& g, uint8& b, uint8& a) const;
	//void		getRGBA(uint8& r, uint8& g, uint8& b, uint8& a) const;
	//void		getRGBA(float& r, float& g, float& b, float& a) const;

	//Fl_Color	getFlColor() const;
	//void		setOpenGLColour(bool withAlpha = false) const;

	//Colour		operator+(const Colour& other) const;
	//Colour		operator-(const Colour& other) const;
	//Colour		operator*(float scalar) const;





};


