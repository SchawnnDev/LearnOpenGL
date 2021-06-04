#ifndef _MAIN_CPP
#define _MAIN_CPP
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#endif

#include <iostream>
#include "glad/glad.h"
#include <GLFW\glfw3.h>
#include <shader.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

int main() {

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader ourShader("../src/shaders/1.vertex.shader", "../src/shaders/1.fragment.shader");

    float vertices[] = {
            // first triangle
            -0.9f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0,  // right
            -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top
            // second triangle
            0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0,  // right
            0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    std::cout << "Starting with OpenGL with " << glGetString(GL_VENDOR) << " " << glad_glGetString(GL_RENDERER)
              << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Inputs */
        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render triangle
        ourShader.use();
        //  ourShader.setFloat("xOffset", 0.5f);

        // color value
        /*
        auto timeValue = (float) glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "vertexColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); */

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 6); // set the count to 6 since we're drawing 6 vertices now

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}