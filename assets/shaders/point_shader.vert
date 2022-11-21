#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aVel;

uniform mat4 camera;
uniform mat4 transform;

out vec2 uv;

void main() {
    uv = aPos * 0.5 + 0.5;
    gl_Position = camera * transform * vec4(aPos, 1.0, 1.0);
}