#pragma once

#include <iostream>
#include <vector>

#define PI 3.1415f

#define WHITE   {1.0f, 1.0f, 1.0f}
#define RED     {1.0f, 0.0f, 0.0f}
#define GREEN   {0.0f, 1.0f, 0.0f}
#define BLUE    {0.0f, 0.0f, 1.0f}
#define YELLOW  {1.0f, 1.0f, 0.0f}
#define ORANGE  {1.0f, 0.5f, 0.0f}
#define BLACK   {0.0f, 0.0f, 0.0f}

#define  VA  -1.0f,  1.0f,  1.0f
#define  VB   1.0f,  1.0f,  1.0f
#define  VC  -1.0f, -1.0f,  1.0f
#define  VD   1.0f, -1.0f,  1.0f
#define  VE  -1.0f,  1.0f, -1.0f
#define  VF   1.0f,  1.0f, -1.0f
#define  VG  -1.0f, -1.0f, -1.0f
#define  VH   1.0f, -1.0f, -1.0f

#define X_AXIS {1.0f, 0.0f, 0.0f}
#define Y_AXIS {0.0f, 1.0f, 0.0f}
#define Z_AXIS {0.0f, 0.0f, 1.0f}

#define RIGHT_FACE  {2, 5, 8, 11, 14, 17, 20, 23, 26}
#define LEFT_FACE   {6, 3, 0, 15, 12, 9, 24, 21, 18}
#define TOP_FACE    {6, 7, 8, 3, 4, 5, 0, 1, 2}
#define BOTTOM_FACE {18, 19, 20, 21, 22, 23, 24, 25, 26}
#define FRONT_FACE  {0, 1, 2, 9, 10, 11, 18, 19, 20}
#define BACK_FACE   {8, 7, 6, 17, 16, 15, 26, 25, 24}

/*
    A vector with 27 integers represents the position of each piece in the cube. (See cube.h -> m_state)
    The above definitions determine which indices in the m_state vector are in each face of the cube.
    The order represented on this vector is the following:
        6  7  8
      3  4  5          ->  top face
    0  1  2

        15 16 17
      12 13 14
    9  10 11

        24 25 26
      21 22 23         -> bottom face
    18 19 20

    The position 0 corresnponds to the piece on the (-1, 1, 1) coordinates.
    The position 26 corresnponds to the piece on the (1, -1, -1) coordinates.
*/
