#pragma once

#include <iostream>
#include <glew/glew.h>
#include "../Core/Singleton.h"
#include "../Core/Utils.h"
#include "../Core/Types.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sandbox
{
	class Shader {
	public:
		GLuint _shader;
	
		Shader(const char* vertexPath, const char* fragmentPath);

		void Use();

		void SetInt(const char* uniformName, GLint value) const;
		void SetFloat(const char* uniformName, GLfloat value) const;
		void SetVec3(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3) const;
		void SetVec3(const char* uniformName, glm::vec3 value) const;
		void SetVec4(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const;
		void SetMat3(const char* uniformName, glm::mat3 value) const;
		void SetMat4(const char* uniformName, glm::mat4 value) const;
		//const u16 ShaderInstanceId() const {return _shaderInstanceId;};
		//u16& ShaderInstanceId() {return _shaderInstanceId;};
		//const u16 ShaderResourceId() const {return _shaderResourceId;};
		//u16& ShaderResourceId() {return _shaderResourceId;};
	private:
		//u16 _shaderInstanceId;
		//u16 _shaderResourceId;
		GLuint CompileShader(GLenum shaderType, const char* shaderSource);
		GLuint Load(const char* vertexPath, const char* fragmentPath);
	};
}