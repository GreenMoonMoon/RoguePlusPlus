#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aVel;

uniform mat4 mvp;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0) * mvp;
    gl_PointSize = 25.0;
}