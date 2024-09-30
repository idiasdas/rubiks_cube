#pragma once

#include <glad/glad.h>
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "renderer/opengl-context.h"

void ShowExampleAppLog(bool* p_open);
void set_imgui_window(ImGuiIO& io, OpenGLContext& context);
