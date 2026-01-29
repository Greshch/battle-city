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

    //////////////////////       vertexes      ////////////////////////////
    // position
    GLfloat my_vertex_GLfloat_position[] = {
        // red top
        0.0f, 0.5f, 0.0f,
        // green right
        0.5f, -0.5f, 0.0f,
        // blue left
        -0.5f, -0.5f, 0.0f
    };
    // colors
    GLfloat my_vertex_GLfloat_colors[] = {
        // red top
        1.0f, 0.0f, 0.0f,
        // green right
        0.0f, 1.0f, 0.0f,
        // blue left
        0.0f, 0.0f, 1.0f
    };
    ///////////////////////////////////////////////////////////////////////

    //////////////////////     shaders code    ////////////////////////////
    // vertex
    const char* my_shader_vertex_code_str = 
    "#version 460\n"
    "layout(location = 0) in vec3 vertex_position;\n"
    "layout(location = 1) in vec3 vertex_colors;\n"
    "out vec3 colors;\n"
    "void main(){\n"
    "    colors = vertex_colors;\n"
    "    gl_Position = vec4(vertex_position, 1.0);\n"
    "}\n";
    // fragment
    const char* my_shader_fragment_code_str =
    "#version 460\n"
    "in vec3 colors;\n"
    "out vec4 fragment_colors;\n"
    "void main(){\n"
    "    fragment_colors = vec4(colors, 1.0);\n"
    "}\n"
    ;
    ///////////////////////////////////////////////////////////////////////

    //////////////////////   shaders compile   ////////////////////////////
    // vertex
    GLuint my_shader_vertex_GLuint = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(my_shader_vertex_GLuint, 1, &my_shader_vertex_code_str, nullptr);
    glCompileShader(my_shader_vertex_GLuint);
    // fragment
    GLuint my_shader_fragment_GLuint = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(my_shader_fragment_GLuint, 1, &my_shader_fragment_code_str, nullptr);
    glCompileShader(my_shader_fragment_GLuint);
    ///////////////////////////////////////////////////////////////////////

    //////////////////////     link program    ////////////////////////////
    GLuint my_shader_program_GLuint = glCreateProgram();
    glAttachShader(my_shader_program_GLuint, my_shader_vertex_GLuint);
    glAttachShader(my_shader_program_GLuint, my_shader_fragment_GLuint);
    glLinkProgram(my_shader_program_GLuint);
    ///////////////////////////////////////////////////////////////////////

    //////////////////////   delete shaders    ////////////////////////////
    glDeleteShader(my_shader_vertex_GLuint);
    glDeleteShader(my_shader_fragment_GLuint);
    ///////////////////////////////////////////////////////////////////////

    ///////////////////// vertex buffer objects  //////////////////////////
    // position
    GLuint my_shader_position_vbo_GLuint {};
    glGenBuffers(1, &my_shader_position_vbo_GLuint);
    glBindBuffer(GL_ARRAY_BUFFER, my_shader_position_vbo_GLuint);
    glBufferData(GL_ARRAY_BUFFER, sizeof(my_vertex_GLfloat_position), my_vertex_GLfloat_position, GL_STATIC_DRAW);
    // colors
    GLuint my_shader_colors_vbo_GLuint {};
    glGenBuffers(1, &my_shader_colors_vbo_GLuint);
    glBindBuffer(GL_ARRAY_BUFFER, my_shader_colors_vbo_GLuint);
    glBufferData(GL_ARRAY_BUFFER, sizeof(my_vertex_GLfloat_colors), my_vertex_GLfloat_colors, GL_STATIC_DRAW);
    ///////////////////////////////////////////////////////////////////////
    
    /////////////////////  vertex array objects  //////////////////////////
    GLuint my_vao_GLuint {};
    glGenVertexArrays(1, &my_vao_GLuint);
    glBindVertexArray(my_vao_GLuint);
    // position
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, my_shader_position_vbo_GLuint);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    // colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, my_shader_colors_vbo_GLuint);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    ///////////////////////////////////////////////////////////////////////

    //////////////////////     Main Loop      /////////////////////////////
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(my_g_window_GLFWwindow_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //////////////////////   draw triangle    /////////////////////////////
        glUseProgram(my_shader_program_GLuint);
        glBindVertexArray(my_vao_GLuint);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        ///////////////////////////////////////////////////////////////////////
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
