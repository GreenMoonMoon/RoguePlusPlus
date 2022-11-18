#include "camera.h"

Camera::Camera(vec2 viewportSize) {
    halfSize = viewportSize * 0.5f;
    view = glm::ortho(-halfSize.x, halfSize.x, -halfSize.y, halfSize.y);
}
