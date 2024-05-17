#pragma once

#include "Base.h"
#include "../Math/Vectors.h"
#include <string>
#include <ostream>
#include <glew/glew.h>
#include <variant>
#include <xstring>

namespace Sandbox
{
	enum class ImageFormat {
		JPG, PNG
	};

	enum class TextureType {
		NONE 		= 0,
		DIFFUSE 	= 1,
		SPECULAR 	= 2,
		EMISSIVE 	= 3
	};

	// std::string Wrapper
	class String
	{
	private:
		std::string _string;

	public:
		String() {}
		String(const char* str) : _string(str) {}
		String(const std::string& str) : _string(str) {}

		void append(String& str);
		void append(const std::string& str);
		char& at(int index);
		bool empty();
		
		String operator+(const String& str) const {
			String temp;
			temp._string = this->_string + str._string;
			return temp;
		}
		String operator+(const char* str) const {
			String temp;
			temp._string = str + this->_string;
			return temp;
		}
		String operator+=(const String& str) {
			this->_string += str._string;
			return _string;
		}
		String operator+=(const int& value) {
			this->_string += std::to_string(value);
			return _string;
		}
		bool operator==(const String& str) const{
			return this->_string == str._string;
		}
		bool operator!=(const String& str) const{
			return this->_string != str._string;
		}
		friend std::ostream& operator<<(std::ostream& os, const String& str) {
			os << str._string;
			return os;
		}

		const char* c_str() const {
			return _string.c_str();
		}

		operator const char*() const {
			return _string.c_str();
		}

		operator std::string() const{
			return _string;
		}
	};

	struct Resource {
		int id;
		std::string name;
		std::string path;
	};

	struct Vertex {
		vec3 position;
		vec3 normal;
		vec2 texCoords;
	};

	struct Color {
		float r;
		float g;
		float b;
		float a;
		Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha){};
	};

	struct ShaderData {
		u16 vertexID;
		u16 fragmentID;
		ShaderData(u16 vId, u16 fId) : vertexID(vId), fragmentID(fId){};
	};
}