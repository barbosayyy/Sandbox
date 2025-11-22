#pragma once

#include "Core/Base.h"
#include "Math/Vectors.h"
#include <glew/glew.h>

#include <vector>
#include <string>
#include <xstring>

namespace Sb {

	enum class ImageFormat {
		JPG, PNG
	};

	enum class TextureType {
		DIFFUSE 	= 0,
		SPECULAR 	= 1,
		NORMAL 		= 2,
		EMISSIVE 	= 3
	};

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
		char* data() {return this->_string.data();}
		bool empty();
		size_t size() const {return this->_string.size();}
		const String substr(size_t off, size_t count) const {return this->_string.substr(off, count);}
		size_t rfind(const char* ptr, size_t offset) const {return this->_string.rfind(ptr, offset);}
		
		String operator+(const String& str) const {
			return this->_string + str._string;
		}
		String operator+(const char* str) const {
			return this->_string + str;
		}
		String operator+=(const String& str) {
			return this->_string += str._string;
		}
		String operator+=(const int& value) {
			return this->_string += std::to_string(value);
		}
		String operator+(char value){
			return this->_string = _string + value;
		}
		String operator+=(char value){
			return this->_string += value;
		}
		bool operator==(const String& str) const{
			return this->_string == str._string;
		}
		bool operator!=(const String& str) const{
			return this->_string != str._string;
		}

		const char* c_str() const {
			return this->_string.c_str();
		}

		operator const char*() const {
			return this->_string.c_str();
		}

		operator std::string() const{
			return this->_string;
		}
	};

	struct Resource {
		int id;
		std::string name;
		std::string path;
	};

	struct Vertex {
		Vertex() {}
		Vertex(vec3 pos, vec3 norm, vec2 tex) : position(pos), normal(norm), texCoords(tex) {}
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

	struct DefaultMesh {
		const String name;
		std::vector<Vertex> vertices;
        std::vector<u32> indices;
    };

	struct SbGUID {
        u64 h1;
        u64 h2;
        bool operator == (const SbGUID& other) const {
            return h1 == other.h1 && h2 == other.h2;
        }
    };
};

namespace std {
	template <>
	struct hash<Sb::SbGUID> {
		size_t operator()(const Sb::SbGUID& guid) const;
	};
}