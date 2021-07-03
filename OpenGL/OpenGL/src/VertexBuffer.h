#pragma once


class VertexBuffer 
{
private:
	unsigned int m_rendererID; // OpenGL ID   -- return of GenBuffers  // vertex buffer


public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};