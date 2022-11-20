#include "VBO.hpp"

/**
 * It creates a buffer object, binds it to the GL_ARRAY_BUFFER target, and then provides the vertex
 * data to the buffer object
 *
 * @param vertices the array of vertices
 * @param size the size of the data in bytes
 */
VBO::VBO(GLfloat *vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // provide vertex data to the vao
    // static draw as the vertices won't be modified often
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

/**
 * Binds the VBO to the current context.
 */
void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

/**
 * It unbinds the VBO
 */
void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 * It deletes the VBO from the GPU
 */
void VBO::remove()
{
    glDeleteBuffers(1, &ID);
}