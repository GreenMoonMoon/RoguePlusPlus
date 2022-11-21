#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec2 viewportSize, float zoom) {
    view = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(glm::vec2(2.0f) / (viewportSize * zoom), 0.0f));
//    glm::vec2 scale = glm::vec2(size.y/size.x, 1.0f);
//    view = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 0.0f) * 2.0f);
//    view = glm::translate(view, glm::vec3(-1.0f, -1.0f, 0.0f));
}
