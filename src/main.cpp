#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//////////////////////  main window vars  /////////////////////////////
GLFWwindow* my_g_window_GLFWwindow_window = nullptr;
int my_g_window_int_width = 640;
int my_g_window_int_height = 480;
const char* my_g_window_str_title = "Game";
///////////////////////////////////////////////////////////////////////

////////////////////  callbacks functions  ////////////////////////////
void my_fun_callback_window_size(GLFWwindow* window, int width, int height);
void my_fun_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
///////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    //////////////////////     Init glfw      /////////////////////////////
    if (!glfwInit())
    {
        std::cerr << "glfw Init error..\n";
        return -1;
    }
    ///////////////////////////////////////////////////////////////////////

    /////////////////////  Create Main Window  ////////////////////////////
    my_g_window_GLFWwindow_window = 
    glfwCreateWindow(my_g_window_int_width, my_g_window_int_height, my_g_window_str_title, nullptr, nullptr);
    if (!my_g_window_GLFWwindow_window)
    {
        std::cerr << "glfw Create window error..\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(my_g_window_GLFWwindow_window);
    ///////////////////////////////////////////////////////////////////////

    //////////////////////     Set OpenGL     /////////////////////////////
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    ///////////////////////////////////////////////////////////////////////

    //////////////////////      load glad     /////////////////////////////
    if (!gladLoadGL())
    {
        std::cerr << "glad Load GL error..\n";
        glfwTerminate();
        return -1;
    }
    ///////////////////////////////////////////////////////////////////////

    //////////////////////    Set callbacks    ////////////////////////////
    glfwSetWindowSizeCallback(my_g_window_GLFWwindow_window, my_fun_callback_window_size);
    glfwSetKeyCallback(my_g_window_GLFWwindow_window, my_fun_callback_key);
    ///////////////////////////////////////////////////////////////////////

    //////////////////////     Main Loop      /////////////////////////////
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(my_g_window_GLFWwindow_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(my_g_window_GLFWwindow_window);
        glfwPollEvents();
    }
    ///////////////////////////////////////////////////////////////////////

    //////////////////////    Print Version   /////////////////////////////
    std::cout << "renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "version: " << glGetString(GL_VERSION) << std::endl;
    ///////////////////////////////////////////////////////////////////////

    //////////////////////    END programm    /////////////////////////////
    glfwTerminate();
    return 0;
    ///////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////
void my_fun_callback_window_size(GLFWwindow *window, int width, int height)
{
    my_g_window_int_width = width;
    my_g_window_int_height = height;
    glViewport(0, 0, my_g_window_int_width, my_g_window_int_height);
}

void my_fun_callback_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        if (action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}
///////////////////////////////////////////////////////////////////////
