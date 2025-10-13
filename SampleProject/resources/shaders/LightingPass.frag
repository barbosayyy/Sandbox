#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

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
    float radius;
};

const int n_lights = 32;
uniform Light lights[n_lights];
uniform vec3 ambientLight;
uniform vec3 viewPosition;

void main() {
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    vec3 lighting = (Diffuse * ambientLight);
    vec3 viewDir = normalize(viewPosition - FragPos);

    for(int i = 0; i < n_lights; ++i)
    {
        float distance = length(lights[i].position - FragPos);
        if(distance < lights[i].radius){
            vec3 lightDir = normalize(lights[i].position - FragPos);
            vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].color;

            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
            vec3 specular = lights[i].color * spec * Specular;

            float attenuation = 1.0 / (1.0+lights[i].linear * distance + lights[i].quadratic * distance * distance);
            diffuse *= attenuation;
            specular *= attenuation;
            lighting += diffuse + specular;
        }
    }
    FragColor = vec4(lighting, 1.0);
}