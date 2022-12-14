#version 330 core // version 330 for OpenGL 3.3

// values input from the vertex array
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;

out vec3 colour;

uniform float scale;

void main()
{
    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    colour = aColour;
}