#pragma once

enum class rotation { // все против часовой стрелки
    Right,
    Bottom,
    Front,
    None
};

#define ROT_STEP 80
#define CUBES_NUM 8

#define CAMERA_Z 5.0f

constexpr float ROTATE_STEP = 180.f / 300;
constexpr float MAX_POLAR_ANGLE = 180 / 3;