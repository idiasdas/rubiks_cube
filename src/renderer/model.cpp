#include "model.h"

Model::Model()
{
    glGenVertexArrays(1, &m_vertex_array_ID);
}

void Model::buffer_data(std::vector<float> buffer)
{
    glBindVertexArray(m_vertex_array_ID);
    m_vertex_buffer = buffer;
    glCreateBuffers(1, &m_vertex_buffer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer.size()*sizeof(float), &m_vertex_buffer[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        6*sizeof(float), // stride
        (void *)0 // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glVertexAttribPointer(
        1,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        6*sizeof(float),        // stride
        (void *)(3 * sizeof(float)) // array buffer offset
    );

    for (uint32_t i = 0; i < m_vertex_buffer.size() / 6; i++)
        m_index_buffer.push_back(i);

    glCreateBuffers(1, &m_index_buffer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer.size()*sizeof(uint32_t), m_index_buffer.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::draw(Shader &shader)
{
    shader.bind();
    glBindVertexArray(m_vertex_array_ID);
    glDrawElements(GL_TRIANGLES, m_index_buffer.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
