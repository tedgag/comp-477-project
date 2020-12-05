#version 330 core

in vec3 fragPos;
in vec3 fragNormal;
in vec3 fragColor;

uniform vec3 viewPos;

out vec4 fColor;

void main()
{
    vec3 color = fragColor;
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 lightDir = normalize(-vec3(-0.2f, -1.0f, -0.3f));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    // combine results
    vec3 ambient = vec3(0.5f, 0.5f, 0.5f);
    vec3 diffuse = vec3(0.4f, 0.4f, 0.4f) * diff;
    vec3 specular = vec3(0.5f, 0.5f, 0.5f) * spec;
    vec3 lighting = (ambient + diffuse + specular) * color;

    fColor = vec4(lighting, 1.0f);
}
