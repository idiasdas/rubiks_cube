#include "opengl-context.h"

OpenGLContext::OpenGLContext(const std::string &window_name, const int window_width, const int window_height, void (*func_event_manager)(Event& event))
{
    m_window_name = window_name;
    m_window_width = window_width;
    m_window_height = window_height;
    m_func_event_manager = func_event_manager;

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


    glfwSetWindowUserPointer(m_window, this);
    set_events_callbacks();
}

void OpenGLContext::set_events_callbacks()
{
    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods){
        (void) scancode;
        (void) mods;
        OpenGLContext* context = (OpenGLContext *) glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS)
        {
            KeyPressEvent event(key);
            context->run_event_manager(event);
        }
        else if (action == GLFW_RELEASE)
        {
            KeyReleaseEvent event(key);
            context->run_event_manager(event);
        }
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xpos, double ypos){
        OpenGLContext* context = (OpenGLContext *) glfwGetWindowUserPointer(window);
        MouseMoveEvent event(xpos, ypos);
        context->run_event_manager(event);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods){
        (void) mods;
        OpenGLContext* context = (OpenGLContext *) glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MouseButtonPressEvent event(button, xpos, ypos);
            context->run_event_manager(event);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseButtonReleaseEvent event(button);
            context->run_event_manager(event);
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xoffset, double yoffset){
        (void) xoffset;
        OpenGLContext* context = (OpenGLContext *) glfwGetWindowUserPointer(window);
        MouseScrollEvent event(yoffset);
        context->run_event_manager(event);
    });
    });
}
