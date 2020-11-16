#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 color;

out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragPos;

void main()
{
    fragColor = color;
    fragNormal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position =  proj * view * model * vec4(aPos, 1.0);
}
