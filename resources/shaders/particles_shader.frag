#version 330 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;

uniform sampler2D shadowMap;
uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

out vec4 fColor;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(-vec3(-0.2f, -1.0f, -0.3f));
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // Check whether current frag pos is in shadow
    // Float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}


void main()
{
    vec3 color = texture(diffuseTexture, fragTexCoords).rgb;

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
    // calculate shadow
    // float shadow = ShadowCalculation(fragPosLightSpace);
    // vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    fColor = vec4(lighting, 1.0f);
}
