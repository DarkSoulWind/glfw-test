#include "EBO.hpp"

/**
 * It creates a new EBO and binds it to the GL_ELEMENT_ARRAY_BUFFER.
 *
 * @param indices the array of indices
 * @param size the size of the data in bytes
 */
EBO::EBO(GLuint *indices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // provide vertex data to the vao
    // static draw as the vertices won't be modified often
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

/**
 * Binds the EBO to the current VAO.
 */
void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

/**
 * Unbinds the EBO from the current context.
 */
void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 * It deletes the EBO
 */
void EBO::remove()
{
    glDeleteBuffers(1, &ID);
}