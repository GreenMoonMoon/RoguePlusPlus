#ifndef SM64_CAMERA_H
#define SM64_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using glm::vec4;
using glm::mat4x4;
using glm::mat4;

struct Camera {
    mat4 transform;
    mat4 view;
    mat4 projection;
};

#endif // SM64_CAMERA_H
