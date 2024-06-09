#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

class Model
{
public:
    /*
        Represents a vertex array object from OpenGL.
        It buffers all vertices on the GPU and uses the indices to tell OpenGL what to draw.
        A model also contains translation, rotation, and scaling matrix to transform the vertices before drawing.
    */
    Model();

    /*
        Sends the vertices described on buffer to the GPU.
        Currently, the vertices have two attributes:
        - position (3 floats: x, y, z)
        - color (3 floats: r, g, b)

        Therefore, the buffer layout is:
        - {v1_x, v1_y, v1_z, v1_r, v1_g, v1_b, v2_x, v2_y, v2_z, v2_r, v2_g, v2_b, ...}

    */
    void buffer_vertices(const std::vector<float> buffer);

    /*
        Creates an index buffer and loads it on the GPU.
        This is used to tell the GPU which vertices to draw.
    */
    void buffer_indices(const std::vector<uint32_t> buffer);

    /*
        Draws the buffered vertices according to the buffered indices.
        The vertices are multiplied by the transformation matrix MVP.
        Uses the shader for the OpenGL draw call.
    */
    void draw(const Shader &shader, const glm::mat4 MVP) const;


    /*
        It scales the model on each axis according to the coordinates of scale_vector.
        For example, scale_vector == glm::vec3(10, 0, 0) streches the model by a factor of ten along the x-axis.
    */
    void scale(const glm::vec3& scale_vector);

    /*
        Rotates the model around the rotation_axis.
        This is axis is relative to the model's local coordinates.
        If you want to rotate the model around an axis on the global
        coordinate system, you must first translate the model to the origin,
        rotate it around the axis, and then translate it to the correct position.
    */
    void rotate(const float rotation_degree, const glm::vec3& rotation_axis);

    /*
        Translates the model according to the translation_vector.
        For example, translation_vector == glm::vec3(10, 0, 0) moves the object 10 units along the x-axis.
    */
    void translate(const glm::vec3& translation_vector);

    void set_scale_matrix(const glm::mat4& scale_matrix) { m_scale_matrix = scale_matrix;}
    void set_rotation_matrix(const glm::mat4& rotation_matrix) { m_rotation_matrix = rotation_matrix;}
    void set_translation_matrix(const glm::mat4& translation_matrix) { m_translation_matrix = translation_matrix;}

    glm::mat4 get_scale_matrix() const { return m_scale_matrix;}
    glm::mat4 get_rotation_matrix() const { return m_rotation_matrix;}
    glm::mat4 get_translation_matrix() const { return m_translation_matrix;}
    glm::mat4 get_model_matrix() const { return m_translation_matrix * m_rotation_matrix * m_scale_matrix; }

private:
    uint32_t m_vertex_array_ID;
    uint32_t m_vertex_buffer_ID;
    uint32_t m_index_buffer_ID;

    uint32_t m_indices_count;

    glm::mat4 m_scale_matrix;
    glm::mat4 m_rotation_matrix;
    glm::mat4 m_translation_matrix;
};
