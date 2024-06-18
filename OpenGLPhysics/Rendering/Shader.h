#pragma once
#include <string>
#include <glad/glad.h>


class Shader 
{
public:
	Shader(std::string vertPath, std::string fragString);
	void UseShader();
private:
	unsigned int m_ID;
};