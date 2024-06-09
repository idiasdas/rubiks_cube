#include "opengl-context.h"

OpenGLContext::OpenGLContext(const std::string &window_name, const int window_width, const int window_height)
{
    m_window_name = window_name;
    m_window_width = window_width;
    m_window_height = window_height;

    // Initializing GLFW
    if (!glfwInit())
    {
        std::cout << "[ERROR] Failed to initialize GLFW" << std::endl;
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
        std::cout << "Failed to open GLFW window" << std::endl;
        std::cout << "If you have an Intel GPU, they are not 4.6 compatible." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_FALSE);         // Ensure we can capture the escape key being pressed
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Hide the mouse and enable unlimited movement
    glfwSetCursorPos(m_window, window_height / 2, window_width / 2);// Set the mouse at the center of the screen
    glfwSwapInterval(0);                                            // Disable VSync
    glfwPollEvents();

    // Initialize glad
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!status)
    {
        std::cout << "Failed to initialize glad." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL Info:" << std::endl;
    std::cout << " - Vendor:    " << (const char *)glGetString(GL_VENDOR) << std::endl;
    std::cout << " - Renderer:  " << (const char *)glGetString(GL_RENDERER) << std::endl;
    std::cout << " - Version:   " << (const char *)glGetString(GL_VERSION) << std::endl;

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it is closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Do not draw polygons if the camera is inside them
    glEnable(GL_CULL_FACE);
}
