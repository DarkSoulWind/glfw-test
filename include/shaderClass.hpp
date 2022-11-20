#pragma once

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string readTextFromFile(const char *filename);

class Shader
{
public:
    GLuint ID;
    Shader(const char *vertexFile, const char *fragmentFile);

    void activate();
    void remove();
};