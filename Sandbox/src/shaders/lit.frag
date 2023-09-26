#version 330 core

//#define POINT_LIGHT
//#define DIR_LIGHT
#define SPOT_LIGHT

out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 TexCoords;

// Material structure
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
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

#ifdef POINT_LIGHT
	uniform Light_Point light;
#elif defined(DIR_LIGHT)
	uniform Light_Directional light;
#elif defined(SPOT_LIGHT)
	uniform Light_Spot light;
#endif

// Needs some improvements

void main()
{
	float distance;
	float attenuation;

	#if defined(POINT_LIGHT) || defined(SPOT_LIGHT)
		distance = length(light.position - fragPos);
		attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));
	#endif

	// Ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	vec3 norm = normalize(normal);		

	vec3 lightDir;

	#ifdef POINT_LIGHT
		lightDir = normalize(light.position-fragPos);
	#elif defined(DIR_LIGHT)
		lightDir = normalize(-light.direction);
	#elif defined(SPOT_LIGHT)
		lightDir = normalize(light.position-fragPos);
	#endif

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	// Specular
	vec3 viewDir = normalize(viewer.position-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	// Emissive
	vec3 emissive = material.emissiveStrength * texture(material.emissive, TexCoords).rgb;
		// Emissive map step clipping
		vec3 emissionMask = step(vec3(1.0f), vec3(1.0f) - texture(material.specular, TexCoords).rgb);
		vec3 emissiveFinal = emissive * emissionMask;

	vec3 color;

	#ifdef POINT_LIGHT
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	#endif

	#ifdef DIR_LIGHT
		color = ambient + diffuse + specular + emissiveFinal;
	#endif

	#ifdef SPOT_LIGHT
		float theta = dot(lightDir, normalize(-light.direction));
		float epsilon = light.innerRadius - light.outerRadius;
		float intensity = clamp((theta - light.outerRadius) / epsilon , 0.0, 1.0);
		ambient *= attenuation;
		diffuse *= attenuation * intensity;
		specular *= attenuation * intensity;
		color = ambient + diffuse + specular + emissiveFinal;
	#endif
	
	fragColor = vec4(color, 1.0);
}