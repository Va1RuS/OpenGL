#pragma once


class IndexBuffer 
{
private:
	unsigned int m_rendererID; // OpenGL ID  -- return of GenBuffers  // index buffer object
	unsigned int m_count; // number of indeces


public:
	IndexBuffer(const unsigned int* data, unsigned int count); // count number of indeces 
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const { return m_count; }
};