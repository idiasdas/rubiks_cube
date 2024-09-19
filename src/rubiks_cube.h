#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "log.h"

#define PI glm::pi<float>()

#define EPS 0.0001f

#define WHITE            \
    {                    \
        1.0f, 1.0f, 1.0f \
    }
#define RED              \
    {                    \
        1.0f, 0.0f, 0.0f \
    }
#define GREEN            \
    {                    \
        0.0f, 1.0f, 0.0f \
    }
#define BLUE             \
    {                    \
        0.0f, 0.0f, 1.0f \
    }
#define YELLOW           \
    {                    \
        1.0f, 1.0f, 0.0f \
    }
#define ORANGE           \
    {                    \
        1.0f, 0.5f, 0.0f \
    }
#define BLACK            \
    {                    \
        0.0f, 0.0f, 0.0f \
    }

#define VA -1.0f, 1.0f, 1.0f
#define VB 1.0f, 1.0f, 1.0f
#define VC -1.0f, -1.0f, 1.0f
#define VD 1.0f, -1.0f, 1.0f
#define VE -1.0f, 1.0f, -1.0f
#define VF 1.0f, 1.0f, -1.0f
#define VG -1.0f, -1.0f, -1.0f
#define VH 1.0f, -1.0f, -1.0f

#define X_AXIS           \
    {                    \
        1.0f, 0.0f, 0.0f \
    }
#define Y_AXIS           \
    {                    \
        0.0f, 1.0f, 0.0f \
    }
#define Z_AXIS           \
    {                    \
        0.0f, 0.0f, 1.0f \
    }
