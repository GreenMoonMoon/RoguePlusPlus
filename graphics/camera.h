#ifndef RPP_CAMERA_H
#define RPP_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Camera {
    glm::vec2 halfSize;
    glm::mat4 view;

    Camera(glm::vec2 viewportSize);
    ~Camera() = default;
};

#endif // RPP_CAMERA_H
