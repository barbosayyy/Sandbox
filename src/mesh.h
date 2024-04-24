#pragma once

#include <vector>
#include "math.h"
#include "texture.h"
#include "shaders.h"
#include <map>
#include <iterator>

enum struct ImageType {
	JPG, PNG
};

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 texCoords;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Shader& shader);
	~Mesh();
	
	void draw();
	void bindTextures();

	Shader& shader;
private:
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;

	void createMesh();
};