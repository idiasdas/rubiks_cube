#pragma once

#include <vector>

#include <glad/glad.h>

#include "shader.h"

class Model
{
public:
    Model();
    void bind_array() const;
    void unbind_array() const;
    void bind_buffer() const;
    void unbind_buffer() const;

    void buffer_data(std::vector<float> buffer);
    void draw(Shader& shader);
private:
    uint32_t m_vertex_array_ID;
    uint32_t m_vertex_buffer_ID;
    std::vector<float> m_buffer;
};
