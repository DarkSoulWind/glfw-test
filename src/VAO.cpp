#include "VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO VBO, GLuint layout)
{
    VBO.bind();

    // param 1: position of the vertex attribute (0)
    // param 2: number of inputs per vertex (3)
    // param 4: size of inputs
    // param 5: offset from beginning of vertex array (0)
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(layout);

    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::remove()
{
    glDeleteVertexArrays(1, &ID);
}