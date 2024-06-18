#pragma once
#include <string>
#include <glad/glad.h>


class Shader 
{
public:
	Shader(std::string vertPath, std::string fragString);
	Shader();


	void UseShader();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	unsigned int GetID() const { return m_ID; }
private:
	unsigned int m_ID;
};