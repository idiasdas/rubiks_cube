#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "log.h"
#include "events.h"

class OpenGLContext {
public:
    OpenGLContext(const std::string &window_name, const int window_width, const int window_height, void (*func_event_manager)(Event &event));

    inline std::string get_window_name() const { return m_window_name; }
    inline int get_window_width() const { return m_window_width; }
    inline int get_window_height() const { return m_window_height; }
    inline void set_window_width(int window_width) { m_window_width = window_width; }
    inline void set_window_height(int window_height) { m_window_height = window_height; }
    inline GLFWwindow *get_window_handle() const { return m_window; }

private:
    void set_events_callbacks();
    void run_event_manager(Event &event) const { m_func_event_manager(event); }

private:
    GLFWwindow *m_window;
    std::string m_window_name;
    int m_window_width;
    int m_window_height;
    void (*m_func_event_manager)(Event &event);
};
