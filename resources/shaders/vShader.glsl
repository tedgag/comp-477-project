#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 lightSpaceMatrix;

out vec2 fragTexCoords;
out vec3 fragNormal;
out vec3 fragPos;
out vec4 fragPosLightSpace;


void main()
{
    //mat4 modelMatrix = globalRotationMatrix * worldMatrix;
    //fragPos = vec3(model * vec4(aPos, 1.0));
    //fragNormal = mat3(transpose(inverse(model))) * aNormal;
    fragTexCoords = aTexCoords;
    //fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
    gl_Position =  proj * view * model * vec4(aPos, 1.0);
}
