#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"

#include "Colour.h"


int main(void)
{
	
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 957, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);


	// glew init
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew init ERROR!" << std::endl;
	}

	std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

	// Modern way, buffer holds the integer of the specific shader
	{
		float positions[] = {
			-0.5f, -0.5f, /* 0   3-----2*/ 0.0f, 0.0f,
			 0.5f, -0.5f, /* 1	 |   / |*/ 1.0f, 0.0f,
			 0.5f, 0.5f,  /* 2	 | /   |*/ 1.0f, 1.0f,
			-0.5f, 0.5f,  /* 3	 0-----1*/ 0.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, //first triangle
			2, 3, 0  //second triangle
		};


		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		VertexArray va;
		
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));  //binds by default

		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		va.addBuffer(vb, layout);

		IndexBuffer ib(indices, 6);  //binds by default

		glm::mat4 proj	= glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.f); // should be -2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.f if we want to scale image on 4x3 window
		glm::mat4 view	= glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.0f));

		glm::mat4 mvp = proj * view * model; //because of memory layout opengl except matrices are multipolied from right to left
		
		Shader shader("res/shaders/Basic.shader");
		shader.bind();
		shader.setUniformMatrix4f("u_MVP", mvp);
		
		Texture texture("res/textures/naruto.png");
		texture.bind();
		shader.setUniform1i("u_texture", 0); /*we have to match the slot in texture.bind() method*/

		va.unbind();
		vb.unbind();
		ib.unbind();
		shader.unbind();

		Renderer renderer;

		float r, g, b, a, increment;
		r = 1.0f, g = 0.8f, b = 0.8f, a = 1.0f, increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.clear();

			/*If we are drawing different kinds of stuff, VertexAttrib might be different as well as buffer and ibo
			we end upo actually calling  it everytime
			1.bind shader
			2.bind vertex array
			3.bind index buffer
			4.draw call

			*/
			shader.bind();

			/*u_color is address of */
			//shader.setUniform4f("u_color", r, g, b, a);
			
			renderer.draw(va, ib, shader);


			/*if (r > 1.00f || r < 0.00f)
			{
				increment = (-1) * increment;
			}

			r += increment;*/


			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));

			/* Poll for and process events */
			GLCall(glfwPollEvents());
		}
	}
	glfwTerminate();
	return 0;
}