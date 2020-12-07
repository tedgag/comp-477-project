#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aCenterPos;

uniform mat4 view;
uniform mat4 proj;

uniform float size;

uniform vec3 color;

out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragPos;

void main()
{

    mat4 model = mat4(
        vec4(size, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, size, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, size, 0.0f),
        vec4(aCenterPos, 1.0f)
    );

    fragNormal = mat3(transpose(inverse(model))) * aNormal;
    fragColor = color;
    gl_Position =  proj * view * model * vec4(aPos, 1.0f);
}
