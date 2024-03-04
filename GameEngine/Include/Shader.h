#pragma once

#include <iostream>
#include <glm/ext/matrix_float4x4.hpp>

class Shader
{
public:

	Shader(const std::string& vertexPath, const std::string &fragmentPath);
	~Shader();

	std::string readFile(const std::string& filename);

	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	unsigned int ID;

	unsigned int use();


private:



};

