#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "texture.h"
#include "shaders.h"

enum struct ImageType {
	JPG, PNG
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

//struct Texture {
//	unsigned int id;
//	ImageType imgType;
//};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	//~Mesh();
	
	void draw(Shader& shader);
private:
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;

	void createMesh();
};