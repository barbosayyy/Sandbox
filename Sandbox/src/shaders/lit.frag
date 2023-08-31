#version 330 core
out vec4 fragColor;
in vec3 normal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float lightPos;

uniform float ambientStrength;

vec3 light;
vec3 norm = normalize(normal);
vec3 lightDir = normalize(lightPos-fragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * lightColor;

void main()
{
	vec3 ambient = ambientStrength*lightColor;

	light = (ambient+diffuse) * objectColor;
	fragColor = vec4(light, 1.0);
}