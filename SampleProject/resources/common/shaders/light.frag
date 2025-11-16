#version 330 core
out vec4 fragColor;

struct Material{
    vec4 col;
};

uniform Material material;

void main()
{
    fragColor = material.col;
}