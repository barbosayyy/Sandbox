#version 330 core
out vec4 fragColor;
in vec3 normal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewerPos;
uniform vec3 lightPos;

uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;

vec3 norm = normalize(normal);

vec3 lightDir = normalize(lightPos-fragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * lightColor;

vec3 viewDir = normalize(viewerPos-fragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
vec3 specular = specularStrength * spec * lightColor;

void main()
{
	vec3 ambient = ambientStrength*lightColor;

	vec3 light = (ambient+diffuse+specular) * objectColor;
	fragColor = vec4(light, 1.0);
}