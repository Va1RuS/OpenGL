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

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"




int main(void)
{
	/*float rr, gg, bb, hh, ss, vv;
	unsigned char rr_int, gg_int, bb_int;
	rr_int = 255;
	gg_int = 20;
	bb_int = 30;
	rr = rr_int / 255.0f;
	gg = gg_int / 255.0f;
	bb = bb_int / 255.0f;
	std::cout << (int)rr_int << " " << (int)gg_int << " " << (int)bb_int << " " << std::endl;;
	
	RGBtoHSV(rr_int, gg_int, bb_int, hh, ss, vv);

	std::cout << hh << " " << ss * 100 << " " << vv * 100 << " " << std::endl;

	HSVtoRGB(hh, ss, vv, rr_int, gg_int, bb_int);*/
	/*ImGui::ColorConvertRGBtoHSV(rr, gg, bb, hh, ss, vv);
	ImGui::ColorConvertHSVtoRGB(hh, ss, vv, rr, gg, bb);*/
	
	/*rr_int = rr * 255;
	gg_int = gg * 255;
	bb_int = bb * 255;*/
	//std::cout  << (int)rr_int << " " << (int)gg_int << " " << (int)bb_int << " "<<std::endl;
	
	
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
		
		Texture texture("res/textures/test.png");
		texture.bind();
		shader.setUniform1i("u_texture", 0); /*we have to match the slot in texture.bind() method*/

		va.unbind();
		vb.unbind();
		ib.unbind();
		shader.unbind();

		Renderer renderer;

		// IMGUI 
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));


		float h, s, v, h_prev, s_prev, v_prev;
		h = s = v = h_prev = s_prev = v_prev = 0.0f;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


		float r, g, b, a, increment;
		r = 1.0f, g = 0.8f, b = 0.8f, a = 1.0f, increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.clear();

			// IMGUI before actual code
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			shader.bind();

			/*u_color is address of */
			//shader.setUniform4f("u_color", r, g, b, a);
			
			renderer.draw(va, ib, shader);


			/*if (r > 1.00f || r < 0.00f)
			{
				increment = (-1) * increment;
			}

			r += increment;*/

			//IMGUI
			{

				static int counter = 0;

				ImGui::Begin("HSV options");							// Create a window called "Hello, world!" and append into it.

				ImGui::Text("Addust these values as desired");			// Display some text (you can use a format strings too)

				ImGui::SliderFloat("h", &h, -1.0f, 1.0f);				// Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::SliderFloat("s", &s, -1.0f, 1.0f);				// Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::SliderFloat("v", &v, -1.0f, 1.0f);				// Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))								// Buttons return true when clicked (most widgets return true when edited/activated)
				{
					if (h != h_prev || s != s_prev || v != v_prev)
					{
						h_prev = h;
						s_prev = s;
						v_prev = v;
						texture.updateTexture(h, s, v);
						texture.bind();
					}
					counter++;
				}
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
				
				
			}

			//IMGUI END
			//IMGUI Render
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));

			/* Poll for and process events */
			GLCall(glfwPollEvents());
		}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}