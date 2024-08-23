#pragma once

#include "rubiks_cube.h"

#include <sstream>
#include <string>

#include "glm/glm.hpp"

enum class EventType
{
    none = 0,
    window_close,
    window_resize,
    key_press,
    key_release,
    mouse_button_press,
    mouse_button_release,
    mouse_move,
    mouse_scroll,
    ray
};

#define EVENT_CLASS_TYPE(type)                                     \
    static EventType get_static_type() { return EventType::type; } \
    virtual EventType get_event_type() const override { return get_static_type(); }

class Event
{
public:
    virtual EventType get_event_type() const = 0;
    virtual std::string to_string() const = 0;
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "WindowCloseEvent";
        return ss.str();
    }

    EVENT_CLASS_TYPE(window_close)
};

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(int width, int heigth)
        : m_width(width), m_height(heigth) {}

    inline int get_width() const { return m_width; }
    inline int get_height() const { return m_height; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent (" << m_width << ", " << m_height << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(window_resize)

private:
    int m_width, m_height;
};

class KeyPressEvent : public Event
{
public:
    KeyPressEvent(int key)
        : m_key(key) {}

    inline int get_key() const { return m_key; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyPressEvent (" << m_key << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(key_press)

private:
    int m_key;
};

class KeyReleaseEvent : public Event
{
public:
    KeyReleaseEvent(int key)
        : m_key(key) {}

    inline int get_key() const { return m_key; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyReleaseEvent (" << m_key << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(key_release)

private:
    int m_key;
};

class MouseButtonPressEvent : public Event
{
public:
    MouseButtonPressEvent(int button, float xpos, float ypos)
        : m_button(button), m_xpos(xpos), m_ypos(ypos) {}

    inline int get_button() const { return m_button; }
    inline double get_xpos() const { return m_xpos; }
    inline double get_ypos() const { return m_ypos; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressEvent (" << m_button << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(mouse_button_press)

private:
    int m_button;
    double m_xpos, m_ypos;
};

class MouseButtonReleaseEvent : public Event
{
public:
    MouseButtonReleaseEvent(int button)
        : m_button(button) {}

    inline int get_button() const { return m_button; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleaseEvent (" << m_button << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(mouse_button_release)

private:
    int m_button;
};

class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(int xpos, int ypos)
        : m_xpos(xpos), m_ypos(ypos) {}

    inline int get_x() const { return m_xpos; }
    inline int get_y() const { return m_ypos; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseMoveEvent (" << m_xpos << ", " << m_ypos << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(mouse_move)

private:
    int m_xpos, m_ypos;
};

class MouseScrollEvent : public Event
{
public:
    MouseScrollEvent(int yoffset)
        : m_yoffset(yoffset) {}

    inline int get_yoffset() const { return m_yoffset; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseScrollEvent (" << m_yoffset << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(mouse_scroll)

private:
    int m_yoffset;
};

class RayEvent : public Event
{
public:
    RayEvent(glm::vec3 origin, glm::vec3 direction)
        : m_origin(origin), m_direction(direction) {}

    glm::vec3 get_origin() { return m_origin; }
    glm::vec3 get_direction() { return m_direction; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "RayEvent (" << m_origin.x << ", " << m_origin.y << ", " << m_origin.z << ") (" << m_direction.x << ", " << m_direction.y << ", " << m_direction.z << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ray)

private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};
