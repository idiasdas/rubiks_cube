#pragma  once
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

#ifndef EXECUTABLE_UTILS_PATH
#define EXECUTABLE_UTILS_PATH ""
#endif

class Shader
{
public:
    Shader(const std::string& vertex_file_path, const std::string& fragment_file_path);
    void bind() const;
    void unbind() const;

private:
    uint32_t m_renderer_ID;
};
