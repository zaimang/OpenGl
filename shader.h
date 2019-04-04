#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

using namespace std;

class Shader 
{
public:
	GLuint Program;
	//构造器读取着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use();

	void setFloat(const GLchar* name, const float offest);
};

#endif
