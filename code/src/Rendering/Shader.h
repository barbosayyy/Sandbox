#pragma once

#include <glew/glew.h>
#include "Core/Singleton.h"
#include "Core/Utils.h"
#include "Core/Types.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sb {
	class Shader {
	private:
			struct ShaderManifestID {
				u32 vertexManifestID;
				u32 fragmentManifestID;
			};
			GLuint CompileShaderSource(GLenum shaderType, const String& shaderPath);
			GLuint Load(const String& vertexPath, const String& fragmentPath);
	public:
		Shader();
		Shader(const String& vertexPath, const String& fragmentPath);

		void Use();

		void SetInt(const char* uniformName, GLint value) const;
		void SetFloat(const char* uniformName, GLfloat value) const;
		void SetVec3(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3) const;
		void SetVec3(const char* uniformName, glm::vec3 value) const;
		void SetVec4(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const;
		void SetMat3(const char* uniformName, glm::mat3 value) const;
		void SetMat4(const char* uniformName, glm::mat4 value) const;
		GLuint _shader;
		ShaderManifestID _assetID;
	};
}