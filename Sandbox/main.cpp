#include "window.h"

#include <glad/glad.h>
#include <glfw3.h>

#include <GL/glew.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

const int windowWidth = 1920;
const int windowHeight = 1080;
const char* windowTitle = "Sandbox";

int exitWithError(const char* msg)
{
    printf(msg);
    glfwTerminate();
    return -1;
}

int main(void)
{
    glfwInit();

    if (!glfwInit())
    {
        return exitWithError("Failed to initialize glfw");
    }

    Window* window = Window::createWindow(windowWidth, windowHeight, windowTitle);

    if (window == nullptr)
    {
        return exitWithError("Failed to create glfw window");
    }

    window->installMainCallbacks();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return exitWithError("Failed to initialize glad");
    }   
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize glad.\n");
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);

    while (!glfwWindowShouldClose(window->nativeWindow))
    {
        glClearColor(186.0f / 255.0f, 87.0f / 255.0f, 111.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window->nativeWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}