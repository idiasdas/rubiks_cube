#include "model.h"

Model::Model()
{
    glGenVertexArrays(1, &m_vertex_array_ID);
    m_scale_matrix = glm::mat4(1);
    m_rotation_matrix = glm::mat4(1);
    m_translation_matrix = glm::mat4(1);
}

void Model::buffer_vertices(const std::vector<float> buffer)
{
    glBindVertexArray(m_vertex_array_ID);
    // m_vertex_buffer = buffer;
    glCreateBuffers(1, &m_vertex_buffer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), &buffer[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glVertexAttribPointer(
        0,                 // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                 // size
        GL_FLOAT,          // type
        GL_FALSE,          // normalized?
        6 * sizeof(float), // stride
        (void *)0          // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glVertexAttribPointer(
        1,                          // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                          // size
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        6 * sizeof(float),          // stride
        (void *)(3 * sizeof(float)) // array buffer offset
    );

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::buffer_indices(const std::vector<uint32_t> buffer)
{
    m_index_buffer = buffer;

    glBindVertexArray(m_vertex_array_ID);
    glCreateBuffers(1, &m_index_buffer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.size() * sizeof(uint32_t), m_index_buffer.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::draw(const Shader &shader, const glm::mat4 MVP) const
{
    shader.bind();
    uint32_t matrix_ID = shader.get_uniform_location("MVP");
    glUniformMatrix4fv(matrix_ID, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(m_vertex_array_ID);
    glDrawElements(GL_TRIANGLES, m_index_buffer.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Model::scale(const glm::vec3& scale_vector)
{
    m_scale_matrix = glm::translate(m_scale_matrix, scale_vector);
}

void Model::rotate(const float rotation_degree, const glm::vec3& rotation_axis)
{
    m_rotation_matrix = glm::rotate(glm::mat4(1), rotation_degree, rotation_axis) * m_rotation_matrix;
}

void Model::translate(const glm::vec3& translation_vector)
{
    m_translation_matrix = glm::translate(m_translation_matrix, translation_vector);
}
