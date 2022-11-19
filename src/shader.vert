#version 330 core // version 330 for OpenGL 3.3

layout (location = 0); 
in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}