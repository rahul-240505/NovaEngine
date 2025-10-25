#version 330 core
out vec4 FragColor; // Output color

uniform vec4 spriteColor; // Color passed from SpriteRenderer

void main()
{
    FragColor = spriteColor;
}