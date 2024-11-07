#pragma once

#include <glad/glad.h>
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "renderer/opengl-context.h"

#define IMGUI_DEMO_MARKER(section)                                                                   \
    do {                                                                                             \
        if (GImGuiDemoMarkerCallback != NULL)                                                        \
            GImGuiDemoMarkerCallback(__FILE__, __LINE__, section, GImGuiDemoMarkerCallbackUserData); \
    } while (0)

void ShowExampleAppLog(bool* p_open);
void set_imgui_window(ImGuiIO& io, OpenGLContext& context);

class ImguiWindow {
private:
    void clear();
    void add_log(const char* fmt, ...);
    void imgui_draw(const char* title, bool* p_open = NULL);

public:
    ImguiWindow();
    void set_window(ImGuiIO& io, OpenGLContext& context);
    void draw(bool* p_open);

private:
    ImGuiTextBuffer m_buf;
    ImGuiTextFilter m_filter;
    ImVector<int> m_line_offsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool m_auto_scroll; // Keep scrolling if already at the bottom.
};
