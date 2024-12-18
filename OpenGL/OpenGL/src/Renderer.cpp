#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << std::hex << error << std::dec << "): " << function << " " << file << ":" << line << "\n";
		return false;
	}
	return true;
}



void Renderer::clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.bind();
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}


