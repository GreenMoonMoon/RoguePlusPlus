#ifndef RPP_CAMERA_H
#define RPP_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using glm::vec2;
using glm::mat4;

struct Camera {
    vec2 halfSize;
    mat4 view;

    Camera(vec2 viewportSize);
    ~Camera() = default;
};

#endif // RPP_CAMERA_H
