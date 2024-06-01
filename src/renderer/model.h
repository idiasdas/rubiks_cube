#pragma once

#include <vector>

#include <glad/glad.h>

#include "shader.h"

class Model
{
public:
    Model();

    void buffer_vertices(std::vector<float> buffer);
    void buffer_indices(std::vector<uint32_t> buffer);
    void draw(Shader& shader);
private:
    uint32_t m_vertex_array_ID;
    uint32_t m_vertex_buffer_ID;
    uint32_t m_index_buffer_ID;

    std::vector<float> m_vertex_buffer;
    std::vector<uint32_t> m_index_buffer;
};
