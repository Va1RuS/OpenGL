#pragma once

#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: m_rendererID(0), m_filePath(path), m_localBuffer(nullptr),
	m_buffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
	
	unsigned char* m_buffer = (unsigned char*)malloc(m_width* m_height *4 * sizeof(char));
	ASSERT(m_buffer);
	memcpy(m_buffer, m_localBuffer, m_width * m_height * 4 * sizeof(char));
	//unsigned char* temp = m_buffer;
	//unsigned char x = 165;
	//for (int i = 0; i < 5000*4; i++)
	//{
	//	if (i % 4 == 3)
	//	{
	//		//temp += 1;
	//		*temp = x;
	//		//std::cout <<  (int)*temp << " ";
	//	}

	//		temp += 1;
	//}

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_localBuffer)
	{
		free(m_localBuffer);
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
