#include "Shader.h"
#include <fstream>

Shader::Shader(std::string vertPath, std::string fragPath)
{
	std::string vertCode, fragCode;
	std::ifstream vertStream, fragStream;
	
	vertStream.exceptions(std::ifstream::failbit|std::ifstream::badbit);
	fragStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		vertStream.open(vertPath);
		fragStream.open(fragPath);
		
		vertStream << vertStream.rdbuf();
		fragStream << fragStream.rdbuf();

		vertStream.close();
		fragStream.close();

		vertCode = vertStream.str();
		fragCode = fragStream.str();
	}
	catch (std::ifstream::failure e) 
	{
		std::error << "ERRROR::SHADER: " <<  e.what();
	}
	
	//make the code from c++ style string to c style string
	const char* vertShaderSource = vertCode.c_str();
	const char* fragShaderSource = fragCode.c_str();

	unsigned int vertShader, fragShader;
	bool success;
	std::string logInfo;


	vertex = glCreateShader(GL_VERTEX_SHADER);
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
		std::count << "ERROR::SHADER::PROGRAM : " << logInfo << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

void Shader::UseShader()
{
	glUseProgram(m_ID);
}
