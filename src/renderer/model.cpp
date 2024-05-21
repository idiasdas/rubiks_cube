#include "model.h"

Model::Model()
{
    glGenVertexArrays(1, &m_vertex_array_ID);
}

void Model::bind_array() const
{
    glBindVertexArray(m_vertex_array_ID);
}

void Model::unbind_array() const
{
    glBindVertexArray(0);
}

void Model::bind_buffer() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
}

void Model::unbind_buffer() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::buffer_data(std::vector<float> buffer)
{
    m_buffer = buffer;
    glGenBuffers(1, &m_vertex_buffer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_buffer)*sizeof(float), &m_buffer[0], GL_STATIC_DRAW);

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
}

void Model::draw(Shader &shader)
{
    shader.bind();
    glBindVertexArray(m_vertex_array_ID);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, m_buffer.size() / 3); // 3 indices starting at 0 -> 1 triangle
}
