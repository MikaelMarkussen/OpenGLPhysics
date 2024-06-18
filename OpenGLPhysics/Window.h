#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class OpenGLWindow
{
public:
	OpenGLWindow();
	void run();
	void ProcessInput(GLFWwindow* window);
private:
	//functions
	void WindowLoop(GLFWwindow* window);
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	
	//objects
	
};
