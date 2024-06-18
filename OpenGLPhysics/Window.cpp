#include "Window.h"
#include <iostream>
#include "Rendering/Shader.h"

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};


OpenGLWindow::OpenGLWindow()
{
}

void OpenGLWindow::run()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Physics rocks", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	if (window == nullptr) 
	{
		std::cout << "Could not create window";
		glfwTerminate();
	}
	else
	{
		WindowLoop(window);
	}
}

void OpenGLWindow::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window,true);
	}
}

void OpenGLWindow::WindowLoop(GLFWwindow* window)
{
	std::unique_ptr<Shader> shader = std::make_unique<Shader>();//std::make_unique<Shader>("Shaders/shader.vert","Shaders/shader.frag");

	unsigned int VAO, VBO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Element Buffer object

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	
;
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);
		shader->UseShader();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void OpenGLWindow::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


