#version 450 core

in vec2 uv;

out vec4 FragColor;

void main() {
    if ( length(uv - 0.5) > 0.45) discard;
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}