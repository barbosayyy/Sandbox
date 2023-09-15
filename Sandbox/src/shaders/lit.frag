#version 330 core
out vec4 fragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float shininess;
	float emissiveStrength;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	
};

struct Observer {
	vec3 position;
};

in vec3 normal;
in vec3 fragPos;
in vec2 TexCoords;

uniform Material material;
uniform Light light;
uniform Observer viewer;

vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

vec3 norm = normalize(normal);
vec3 lightDir = normalize(light.position-fragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

vec3 viewDir = normalize(viewer.position-fragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

vec3 emissive = material.emissiveStrength * texture(material.emissive, TexCoords).rgb;
vec3 emissionMask = step(vec3(1.0f), vec3(1.0f) - texture(material.specular, TexCoords).rgb);
vec3 emissiveFinal = emissive * emissionMask;

void main()
{
	vec3 light = ambient + diffuse + specular + emissiveFinal;
	fragColor = vec4(light, 1.0);
}