#version 420 core
out vec4 FragColor;

in vec2 TexCoords;

#define MAX_NUM_TOTAL_LIGHTS 255    // UBO max

// Geometry pass samples
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light{
    vec3 position;
    vec3 color;
    int type;
    float linear;
    float quadratic;
    float intensity;
    float radius;
};

layout (std140, binding = 0) uniform Lights {
    Light light[MAX_NUM_TOTAL_LIGHTS];
    int numLights;
} ubo;

uniform vec3 ambientLight;
uniform vec3 viewPosition;

void main() {
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    vec3 lighting = (Diffuse * ambientLight);
    vec3 viewDir = normalize(viewPosition - FragPos);

    for(int i = 0; i < ubo.numLights; ++i) 
    {
        float distance = length(ubo.light[i].position - FragPos);
        if(distance < ubo.light[i].radius){
            vec3 lightDir = normalize(ubo.light[i].position - FragPos);
            vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * ubo.light[i].color;

            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
            vec3 specular = ubo.light[i].color * spec * Specular;

            float attenuation = 1.0 / (1.0+ubo.light[i].linear * distance + ubo.light[i].quadratic * distance * distance);
            diffuse *= attenuation;
            specular *= attenuation;
            lighting += diffuse + specular;
        }
    }
    FragColor = vec4(lighting, 1.0);
}