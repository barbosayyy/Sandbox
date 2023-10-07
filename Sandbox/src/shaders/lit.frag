#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 TexCoords;

out vec4 fragColor;

struct Material {
	sampler2D diffuse1;
	sampler2D diffuse2;
	sampler2D diffuse3;

	sampler2D specular1;
	sampler2D specular2;
	sampler2D specular3;

	sampler2D emissive1;
	sampler2D emissive2;
	sampler2D emissive3;

	float shininess;
	float emissiveStrength;
};

struct Light_Point {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	

	float constant;
	float linear;
	float quadratic;
};

struct Light_Directional {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Light_Spot {
	vec3 position;
	vec3 direction;
	float innerRadius;
	float outerRadius;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Observer {
	vec3 position;
};

uniform Material material;
uniform Observer viewer;

#define NR_POINT_LIGHTS		4
uniform Light_Point pointLight[NR_POINT_LIGHTS];

uniform Light_Directional dirLight;
uniform Light_Spot spotLight;

vec3 calcDirLight(Light_Directional light, vec3 norm, vec3 viewDir);
vec3 calcPointLight(Light_Point light, vec3 norm, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(Light_Spot light, vec3 norm, vec3 fragPos, vec3 viewDir);

vec3 calcDirLight(Light_Directional light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	return (ambient + diffuse + specular);
}

vec3 calcSpotLight(Light_Spot light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));

	vec3 lightDir = normalize(light.position-fragPos);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calcPointLight(Light_Point light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));

	vec3 lightDir = normalize(light.position-fragPos);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

void main()
{
	vec3 emissive = material.emissiveStrength * texture(material.emissive, TexCoords).rgb;
		// Emissive map step clipping
		vec3 emissionMask = step(vec3(1.0f), vec3(1.0f) - texture(material.specular, TexCoords).rgb);
		vec3 emissiveFinal = emissive * emissionMask;

	vec3 viewDir = normalize(viewer.position-fragPos);
	vec3 norm = normalize(normal);

	vec3 color = calcDirLight(dirLight, norm, viewDir);
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		color += calcPointLight(pointLight[i], norm, fragPos, viewDir);
	}
	color += calcSpotLight(spotLight, norm, fragPos, viewDir);
	
	color += emissiveFinal;
	
	fragColor = vec4(color, 1.0);
}