#include "opengl-context.h"

OpenGLContext::OpenGLContext(const std::string &window_name, const int window_width, const int window_height)
{
    m_window_name = window_name;
    m_window_width = window_width;
    m_window_height = window_height;

    // Initializing GLFW
    if (!glfwInit())
    {
        LOG_ERROR("Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
    }

    // Create OpenGL window and context
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_name.c_str(), NULL, NULL);

    if (m_window == nullptr)
    {
        LOG_ERROR("Failed to open GLFW window.");
        LOG_ERROR(" - If you have an Intel GPU, they are not 4.6 compatible.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_FALSE);          // Ensure we can capture the escape key being pressed
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);     // Hide the mouse and enable unlimited movement
    glfwSetCursorPos(m_window, window_height / 2, window_width / 2); // Set the mouse at the center of the screen
    glfwSwapInterval(1);                                             // Vsync (0 == off, 1 == on)
    glfwPollEvents();

    // Initialize glad
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!status)
    {
        std::cout << "Failed to initialize glad." << std::endl;
        exit(EXIT_FAILURE);
    }

    LOG_INFO("OpenGL Info:");
    LOG_INFO(" - Vendor:    {0}", (const char *)glGetString(GL_VENDOR));
    LOG_INFO(" - Renderer:  {0}", (const char *)glGetString(GL_RENDERER));
    LOG_INFO(" - Version:   {0}", (const char *)glGetString(GL_VERSION));

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it is closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Do not draw polygons if the camera is inside them
    glEnable(GL_CULL_FACE);
}
