#pragma once

#include "glitter.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

class Shader
{
	const std::string& mVertexShaderSource;
	const std::string& mFragmentShaderSource;
	int mProgramId;
public:
	Shader(const std::string& vertexSource, const std::string& fragmentSource)
		: mVertexShaderSource(vertexSource)
		, mFragmentShaderSource(fragmentSource)
	{
		int vertexShader = Compile(GL_VERTEX_SHADER, mVertexShaderSource);
		int fragmentShader = Compile(GL_FRAGMENT_SHADER, mFragmentShaderSource);
		mProgramId = Link(vertexShader, fragmentShader);
	}

	void Use() const
	{
		glUseProgram(mProgramId);
	}

    void SetBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(mProgramId, name.c_str()), (int)value); 
    }
    void SetInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(mProgramId, name.c_str()), value); 
    }
    void SetFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(mProgramId, name.c_str()), value); 
    } 
private:
    int Compile(GLenum shaderType, const std::string& shaderSource)
    {
        int shaderId = glCreateShader(shaderType);

        const char* cSource = shaderSource.c_str();
        std::cout << "DEBUG::SHADER::COMPILE::SHADER_SOURCE" << std::endl;
        std::cout << cSource << std::endl;

        glShaderSource(shaderId, 1, &cSource, NULL);
        glCompileShader(shaderId);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return shaderId;
    }

    int Link(int shader1, int shader2)
    {
        int success;
        char infoLog[512];

        int shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, shader1);
        glAttachShader(shaderProgram, shader2);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(shader1);
        glDeleteShader(shader2);

        return shaderProgram;
    }
};
