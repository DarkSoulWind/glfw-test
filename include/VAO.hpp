#pragma once

#include <glad/glad.h>
#include "VBO.hpp"

class VAO
{
public:
    GLuint ID;
    VAO();

    void linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
    void bind();
    void unbind();
    void remove();
};