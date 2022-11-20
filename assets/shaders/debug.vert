#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 mvp;
out vec2 uv;
const float aspect_ratio = 576.0/720.0;

void main() {
    uv = aUV;
    gl_Position = vec4(aPos, 0.0, 1.0) * mvp;
}