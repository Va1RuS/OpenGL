#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"	

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}
VertexArray:: ~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const std::vector<VertexBufferLayoutElement>& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const VertexBufferLayoutElement element = elements[i];

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normilized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferLayoutElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_rendererID));

}
void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}