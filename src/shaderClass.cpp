#include <string>
#include <fstream>
#include <iostream>
#include "glad/glad.h"

#include "shaderClass.hpp"

std::string readTextFromFile(const char *filename)
{
    std::string line;
    std::string res;
    std::ifstream file(filename);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            res += line + '\n';
        }
        file.close();
    }
    return res;
};

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode = readTextFromFile(vertexFile);
    std::string fragmentCode = readTextFromFile(fragmentFile);

    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

    std::cout << "Vertex shader:\n"
              << vertexSource;
    std::cout << "Fragment shader:\n"
              << fragmentSource;

    // create and compile vertex and fragment shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexSource, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSource, NULL);
    glCompileShader(fs);

    // combine both the vertex and fragment shaders
    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);

    // delete vertex and fragment shaders now that they are no
    // longer used
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::activate()
{
    glUseProgram(ID);
}

void Shader::remove()
{
    glDeleteProgram(ID);
}