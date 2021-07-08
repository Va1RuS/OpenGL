#pragma once

#include "Texture.h"
#include "stb_image/stb_image.h"
#include "set"
#include "imgui/imgui.h"
//#include "Colour.h"	





Texture::Texture(const std::string& path)
	: m_rendererID(0), m_filePath(path), m_localBuffer(nullptr),
	m_buffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
	
	m_buffer = (unsigned char*)malloc(m_width* m_height *4 * sizeof(char));
	ASSERT(m_buffer);
	memcpy(m_buffer, m_localBuffer, m_width * m_height * 4 * sizeof(char));

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_localBuffer)
	{
		free(m_localBuffer);
	}
}

void Texture::updateTexture(float h_inc, float s_inc, float v_inc) 
{
	unsigned char* new_buffer = (unsigned char*)malloc(m_width * m_height * 4 * sizeof(char));
	ASSERT(new_buffer);
	memcpy(new_buffer, m_buffer, m_width * m_height * 4 * sizeof(char));

	bool proportional_increase = false;

	unsigned char* ptr = m_buffer;
	for (int i = 0; i < m_width * m_height * 4; i+=4)
	{
		float rfs = (float)m_buffer[i]		/255.0f;
		float gfs = (float)m_buffer[i + 1]	/255.0f;
		float bfs = (float)m_buffer[i + 2]	/255.0f;

		float hf, sf, vf, rf, gf, bf;
		ImGui::ColorConvertRGBtoHSV(rfs, gfs, bfs, hf, sf, vf);

		if (proportional_increase)
		{
			float h_diff = h_inc > 0.0f ? 1.0f - hf : hf;
			float s_diff = s_inc > 0.0f ? 1.0f - sf : sf;
			float v_diff = v_inc > 0.0f ? 1.0f - vf : vf;
			hf += h_inc * h_diff;
			hf += s_inc * s_diff;
			hf += v_inc * v_diff;
		}
		else
		{
			hf += h_inc;
			sf += s_inc;
			vf += v_inc;
			
			hf = fmod(1.0f + fmod(hf, 1.0f), 1.0f);
			sf = (sf > 1.0f || sf < 0.0f) ? fmod(1.0f + fmod(sf, 1.0f), 1.0f) : sf;
			vf = (vf > 1.0f || vf < 0.0f) ? fmod(1.0f + fmod(vf, 1.0f), 1.0f) : vf;
		}
		ImGui::ColorConvertHSVtoRGB(hf, sf, vf, rf, gf, bf);
		unsigned char r = (unsigned char) (rf * 255.0f);
		unsigned char g = (unsigned char) (gf * 255.0f);
		unsigned char b = (unsigned char) (bf * 255.0f);
		new_buffer[i] = r;  
		new_buffer[i + 1] = g;
		new_buffer[i + 2] = b;
		new_buffer[i + 3] = m_buffer[i + 4]; // alpha
	}

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, new_buffer));

	if (new_buffer)
	{
		free(new_buffer);
	}

}


Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
	if (m_buffer)
	{
		free(m_buffer);
	}
}

void Texture::bind(unsigned int slot /*=0*/) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
