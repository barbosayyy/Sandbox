#pragma once

#include <iostream>
#include <glew/glew.h>
#include "utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	GLuint shader;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setInt(const char* uniformName, GLint value) const;
	void setFloat(const char* uniformName, GLfloat value) const;
	void setVec3(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3) const;
	void setVec3(const char* uniformName, glm::vec3 value) const;
	void setVec4(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const;
	void setMat3(const char* uniformName, glm::mat3 value) const;
	void setMat4(const char* uniformName, glm::mat4 value) const;

private:
	GLuint compileShader(GLenum shaderType, const char* shaderSource);
	GLuint load(const char* vertexPath, const char* fragmentPath);
};