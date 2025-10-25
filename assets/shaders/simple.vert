#version 330 core
layout (location = 0) in vec3 aPos; // Vertex position

uniform mat4 model;      // Model matrix (position, rotation, scale)
uniform mat4 projection; // Projection matrix (camera view)

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
}