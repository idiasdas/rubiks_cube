#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

#include "log.h"

#ifndef EXECUTABLE_UTILS_PATH
#define EXECUTABLE_UTILS_PATH ""
#endif

class Shader
{
public:
    Shader(const std::string &vertex_file_path, const std::string &fragment_file_path);
    void bind() const;
    void unbind() const;
    uint32_t get_uniform_location(const char *uniform_name) const { return glGetUniformLocation(m_renderer_ID, uniform_name); }

private:
    uint32_t m_renderer_ID;
};
