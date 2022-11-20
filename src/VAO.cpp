#include "VAO.hpp"

/**
 * It creates a vertex array object and stores its ID in the variable ID
 */
VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

/**
 * This function links a VBO to a VAO.
 *
 * The first parameter is the VBO to link. The second parameter is the layout of the vertex attribute.
 * The third parameter is the number of components per vertex. The fourth parameter is the type of the
 * components. The fifth parameter is the stride of the vertex. The sixth parameter is the offset of
 * the vertex
 *
 * @param VBO the VBO to link to the VAO
 * @param layout The layout of the vertex attribute. This is the number you pass to
 * glBindAttribLocation.
 * @param numComponents The number of components per vertex attribute. Must be 1, 2, 3, or 4.
 * @param type GL_FLOAT, GL_INT, GL_UNSIGNED_INT, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,
 * GL_UNSIGNED_SHORT, GL_DOUBLE
 * @param stride The stride is the number of bytes between each vertex.
 * @param offset offset from beginning of vertex array
 */
void VAO::linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
    VBO.bind();

    // param 1: position of the vertex attribute (0)
    // param 2: number of inputs per vertex (3)
    // param 4: number of bytes between each vertex
    // param 5: offset from beginning of vertex array (0)
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);

    VBO.unbind();
}

/**
 * It binds the VAO
 */
void VAO::bind()
{
    glBindVertexArray(ID);
}

/**
 * This function binds the VAO to the OpenGL context.
 */
void VAO::unbind()
{
    glBindVertexArray(0);
}

/**
 * It deletes the VAO
 */
void VAO::remove()
{
    glDeleteVertexArrays(1, &ID);
}