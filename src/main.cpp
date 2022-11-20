#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include "shaderClass.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

// called when the window is resized
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char *argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 800, "Triangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // load glad to configure OpenGL
    gladLoadGL();

    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shaderProgram("shaders/shader.vert", "shaders/shader.frag");

    GLfloat vertices[] = {
        -1,
        -1,
        0,
        1,
        -1,
        0,
        0,
        1,
        0,
        0,
        -1,
        0,
        -0.5,
        0,
        0,
        0.5,
        0,
        0,
    };

    GLuint indices[] = {
        0, 3, 4,
        1, 3, 5,
        2, 4, 5};

    VAO VAO1;
    VAO1.bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.linkVBO(VBO1, 0);
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();

    // // vbo stores vertex data
    // // vao stores pointers to one or more vbos
    // // ebo stores vertex indices
    // GLuint VAO, VBO, EBO;

    // // always create vao before vbo
    // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // prevent vao and vbo from being modified
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // // set and apply the window clear colour
    // glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    // // swap the front and back buffers to display updated content
    // glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.activate();

        // bind the VAO so OpenGL uses it
        VAO1.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
        processInput(window);
    }

    // delete all objects we've created
    VAO1.remove();
    VBO1.remove();
    EBO1.remove();
    shaderProgram.remove();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}