#include <string>
#include <fstream>
#include <iostream>
#include "glad/glad.h"

#include "shaderClass.hpp"

/**
 * It reads a text file and returns the contents as a string
 *
 * @param filename The name of the file to read from.
 *
 * @return A string
 */
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

/**
 * It reads the vertex and fragment shader source code from the files specified by the arguments,
 * compiles them, and links them into a shader program
 *
 * @param vertexFile the path to the vertex shader file
 * @param fragmentFile The name of the fragment shader file.
 */
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
    compileErrors(vs, "VERTEX");

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSource, NULL);
    glCompileShader(fs);
    compileErrors(fs, "FRAGMENT");

    // combine both the vertex and fragment shaders
    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");

    // delete vertex and fragment shaders now that they are no
    // longer used
    glDeleteShader(vs);
    glDeleteShader(fs);
}

/**
 * It tells OpenGL to use the shader program with the ID stored in the ID variable.
 */
void Shader::activate()
{
    glUseProgram(ID);
}

/**
 * It deletes the shader program from the GPU
 */
void Shader::remove()
{
    glDeleteProgram(ID);
}

/**
 * If the shader compilation or linking fails, print the error message to the console
 *
 * @param shader The shader object that we want to check for errors.
 * @param type This is the type of shader that we are compiling. It can be either GL_VERTEX_SHADER or
 * GL_FRAGMENT_SHADER.
 */
void Shader::compileErrors(unsigned int shader, const char *type)
{
    GLint hasCompiled;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n"
                      << infoLog << "\n";
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for: " << type << "\n"
                      << infoLog << "\n";
        }
    }
}