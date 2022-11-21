#ifndef RPP_CAMERA_H
#define RPP_CAMERA_H

#include "glm/glm.hpp"

struct Camera {
    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    float zoom = 1.0f;

    explicit Camera(glm::vec2 viewportSize, float zoom);
    ~Camera() = default;
};

#endif // RPP_CAMERA_H
