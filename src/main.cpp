#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

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

    Shader shaderProgram("res/shaders/shader.vert", "res/shaders/shader.frag");

    GLfloat vertices[] = {
        // layout:
        // first three are coords
        // second three are rgb values
        -1, 1, 0, 0, 1, 0,
        1, 1, 0, 1, 0, 0,
        -1, -1, 0, 0, 0, 1,
        1, -1, 0, 1, 1, 1};

    GLuint indices[] = {
        0,
        1,
        2,
        1,
        2,
        3,
    };

    /* Creating a VAO object and then binding it. */
    VAO VAO1;
    VAO1.bind();

    /* Creating a VBO and EBO object and passing the data to the constructor. */
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    /* Linking the VBO to the VAO. */
    // 0 for coords layout
    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    // 1 for rgb layout, 3 values offset from the start of the vertex
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();

    // get scale uniform attribute from vertex shader
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    int widthImg, heightImg, numColCh;
    unsigned char *bytes = stbi_load("res/textures/cancer.png", &widthImg, &heightImg, &numColCh, 0);
    std::cout << "image width: " << widthImg << " image height: " << heightImg << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.activate();
        // set the uniform scale attribute for the vertex shader
        glUniform1f(uniID, -0.5f);

        // bind the VAO so OpenGL uses it
        VAO1.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

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