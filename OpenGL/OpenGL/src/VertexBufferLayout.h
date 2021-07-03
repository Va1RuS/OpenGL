#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normilized;
	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(0);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector< VertexBufferLayoutElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout()
		: m_stride(0) {}

	~VertexBufferLayout();

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}
	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * VertexBufferLayoutElement::getSizeOfType(GL_FLOAT); // size of GLfloat
	}
	
	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_INT); // size of GLfloat
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_BYTE); // size of GLfloat
	}

	inline const std::vector<VertexBufferLayoutElement> getElements() const { return m_elements; }

	inline unsigned int getStride() const { return m_stride; }
};