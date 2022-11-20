#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
}

std::string vertexShaderSource = readTextFromFile("src/shader.vert");
const char *vertexShaderText = vertexShaderSource.c_str();
std::string fragmentShaderSource = readTextFromFile("src/shader.frag");
const char *fragmentShaderText = fragmentShaderSource.c_str();

int main(int argc, char *argv[])
{
    glfwInit();

    std::cout << "Vertex shader: " << vertexShaderText << std::endl;
    std::cout << "Fragment shader: " << fragmentShaderText << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -1, -1, 0,
        1, -1, 0,
        0, 1, 0};

    GLFWwindow *window = glfwCreateWindow(800, 800, "Triangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // create and compile vertex and fragment shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderText, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderText, NULL);
    glCompileShader(fs);

    // combine both the vertex and fragment shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);

    // delete vertex and fragment shaders now that they are no
    // longer used
    glDeleteShader(vs);
    glDeleteShader(fs);

    // vbo stores vertex data
    // vao stores pointers to one or more vbos
    GLuint VAO, VBO;

    // always create vao before vbo
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // static draw as the vertices won't be modified often
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // param 1: position of the vertex attribute (0)
    // param 2: number of inputs per vertex (3)
    // param 4: size of inputs
    // param 5: offset from beginning of vertex array (0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // prevent vao and vbo from being modified
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // set and apply the window clear colour
    glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // swap the front and back buffers to display updated content
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
        processInput(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}