#include "shader.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	//��·���л�ȡ��ɫ��
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	//��֤ifstream��������׳��쳣
	vShaderFile.exceptions(ifstream::badbit);
	fShaderFile.exceptions(ifstream::badbit);
	try
	{
		//���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		//
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "��ȡshader�ļ�ʧ��" << endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	//������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//��ӡ�������
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "���붥����ɫ������" << infoLog << endl;
	}
	//Ƭ����ɫ��
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//��ӡ�������
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "����Ƭ����ɫ������" << infoLog << endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	glGetProgramiv(this->Program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		cout << "��ɫ���������" << infoLog << endl;
	}
	//ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(this->Program);
}

void Shader::setFloat(const GLchar* name, const float offest)
{
	GLint vertexColorLocation = glGetUniformLocation(this->Program, name);
	glUniform4f(vertexColorLocation, 0.0f, offest, 0.0f, 1.0f);
}
