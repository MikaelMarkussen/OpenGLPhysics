#include "Shader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Shader::Shader(std::string vertPath, std::string fragPath)
{
	std::string vertCode, fragCode;
	std::fstream vertStream, fragStream;
	
	vertStream.exceptions(std::ifstream::failbit|std::ifstream::badbit);
	fragStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream vertStringStream, fragStringStream;
	try 
	{
		vertStream.open(vertPath);
		fragStream.open(fragPath);
		
		vertStringStream << vertStream.rdbuf();
		fragStringStream << fragStream.rdbuf();

		vertStream.close();
		fragStream.close();

		vertCode = vertStringStream.str();
		fragCode = fragStringStream.str();
	}
	catch (std::ifstream::failure e) 
	{
		std::cout << "ERRROR::SHADER: " <<  e.what();
	}
	
	//make the code from c++ style string to c style string
	const char* vertShaderSource = vertCode.c_str();
	const char* fragShaderSource = fragCode.c_str();

	unsigned int vertShader, fragShader;
	int success;
	char* logInfo;


	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader,1,&vertShaderSource,NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader,512,NULL,logInfo);
		std::cout <<"ERROR::SHADER::COMPILE : " << logInfo << std::endl;
	}
	

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, logInfo);
		std::cout << "ERROR::SHADER::COMPILE : " << logInfo << std::endl;
	}


	m_ID = glCreateProgram();	
	glAttachShader(m_ID,vertShader);
	glAttachShader(m_ID, fragShader);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID,GL_LINK_STATUS,&success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID,512,NULL,logInfo);
		std::cout << "ERROR::SHADER::PROGRAM : " << logInfo << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

Shader::Shader()
{
	std::string vertPath, fragPath;
	
	// default constrructor for the sake of haveing a some default shaders
	fragPath = "C:/Prosjekter/Vulkan/OpenGLPhysics/OpenGLPhysics/Shaders/shader.frag";
	vertPath = "C:/Prosjekter/Vulkan/OpenGLPhysics/OpenGLPhysics/Shaders/shader.vert";

	std::string vertCode, fragCode;
	std::fstream vertStream, fragStream;

	vertStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream vertStringStream, fragStringStream;
	try
	{
		vertStream.open(vertPath);
		fragStream.open(fragPath);

		vertStringStream << vertStream.rdbuf();
		fragStringStream << fragStream.rdbuf();

		vertStream.close();
		fragStream.close();

		vertCode = vertStringStream.str();
		fragCode = fragStringStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERRROR::SHADER: " << e.what();
	}

	//make the code from c++ style string to c style string
	const char* vertShaderSource = vertCode.c_str();
	const char* fragShaderSource = fragCode.c_str();

	unsigned int vertShader, fragShader;
	int success;
	char* logInfo;


	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShaderSource, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, logInfo);
		std::cout << "ERROR::SHADER::COMPILE : " << logInfo << std::endl;
	}


	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, logInfo);
		std::cout << "ERROR::SHADER::COMPILE : " << logInfo << std::endl;
	}


	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertShader);
	glAttachShader(m_ID, fragShader);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, logInfo);
		std::cout << "ERROR::SHADER::PROGRAM : " << logInfo << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

void Shader::UseShader()
{
	glUseProgram(m_ID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
