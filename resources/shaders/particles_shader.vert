#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aCenterPos;

uniform mat4 view;
uniform mat4 proj;

out vec2 fragTexCoords;
out vec3 fragNormal;
out vec3 fragPos;

void main()
{
    float size = 0.1;

    mat4 model = mat4(
        vec4(size, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, size, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, size, 0.0f),
        vec4(aCenterPos, 1.0f)
    );

    fragNormal = mat3(transpose(inverse(model))) * aNormal;
    fragTexCoords = aTexCoords;
    gl_Position =  proj * view * model * vec4(aPos, 1.0f);
}
