#version 420 core

out vec4 color;

in  VS_OUT {
    vec4 color;
} fs_in;


void main(void) {
    color = vec4(1.0, 0.5, 0.0, 0.0);
}