#include <GLFW/glfw3.h>
#include <iostream>

//////////////////////  main window vars  /////////////////////////////
GLFWwindow* my_g_window_GLFWwindow_window = nullptr;
int my_g_window_int_width = 640;
int my_g_window_int_height = 480;
const char* my_g_window_str_title = "Game";
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

    //////////////////////     Main Loop      /////////////////////////////
    while (!glfwWindowShouldClose(my_g_window_GLFWwindow_window))
    {
        // glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(my_g_window_GLFWwindow_window);
        glfwPollEvents();
    }
    ///////////////////////////////////////////////////////////////////////

    //////////////////////    Print Version   /////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    //////////////////////    END programm    /////////////////////////////
    glfwTerminate();
    return 0;
    ///////////////////////////////////////////////////////////////////////
}