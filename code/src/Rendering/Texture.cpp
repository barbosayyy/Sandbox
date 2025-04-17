#include "Texture.h"
#include "Core/Types.h"
#include "Core/Debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

using namespace SbEngine;

Texture::Texture(const char* path, TextureType tType, GLint wrapMethod, bool flipVertical, bool gammaCorrection) : _type(tType)
{
	this->_name = std::string(path).substr(std::string(path).find_last_of("/")+1, std::string(path).size());

	glGenTextures(1, &_id);

	stbi_set_flip_vertically_on_load(flipVertical);
	unsigned char* data = stbi_load(path, &this->_width, &this->_height, &this->_nrOfChannels, 0);

	//TODO: check for number of channels

	if (data)
	{
		GLenum format;
		if(this->_nrOfChannels == 1)
			format = GL_RED;
		else if(this->_nrOfChannels == 3)
			format = GL_RGB;
		else if(this->_nrOfChannels == 4)
			format = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, _id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, this->_width, this->_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMethod);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMethod);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		Logger::Error("Texture: Failed to load texture from: ", path);
	}
	
	stbi_image_free(data);
}

Texture::~Texture()
{

}