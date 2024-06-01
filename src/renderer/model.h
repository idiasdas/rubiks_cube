#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"

class Model
{
public:
    Model();
    void buffer_vertices(std::vector<float> buffer);
    void buffer_indices(std::vector<uint32_t> buffer);
    void draw(Shader &shader, glm::mat4 MVP);

    glm::mat4 get_model_matrix() const { return m_model_matrix; }
    void set_model_matrix(glm::mat4 &matrix) { m_model_matrix = matrix; }

private:
    uint32_t m_vertex_array_ID;
    uint32_t m_vertex_buffer_ID;
    uint32_t m_index_buffer_ID;

    std::vector<float> m_vertex_buffer;
    std::vector<uint32_t> m_index_buffer;

    glm::mat4 m_model_matrix;
};
