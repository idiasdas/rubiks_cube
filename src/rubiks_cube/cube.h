#pragma once
#include "rubiks_cube.h"

#include <vector>
#include <glm/glm.hpp>

#include "builder.h"
#include "renderer/model.h"
#include "renderer/camera.h"

class Cube
{
public:
    Cube();

    void draw(Shader &shader, Camera &camera) const;

private:
    std::vector<Model> m_pieces;
};
