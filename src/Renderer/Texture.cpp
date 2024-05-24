#include "Texture.h"
#include "../Core/Types.h"
#include "../Core/Debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

using namespace Sandbox;

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
		Logger::Trace(LogLevel::ERROR, "Texture: Failed to load texture from: ", path);
	}
	
	stbi_image_free(data);
}

Texture::~Texture()
{

}

TextureManager::TextureManager()
{
	if(_instance == nullptr)
		_instance = this;
}

TextureManager::~TextureManager()
{
	
}

const Texture& TextureManager::GetTexture(int textureId) const
{
	if(textureId >= 0 || textureId <= _textures.size()-1)
		return _textures.at(textureId);
}

void TextureManager::AddTexture(Texture& newTexture)
{
	if(newTexture.GetID() != NULL)
		this->_textures.push_back(newTexture);
}

void TextureManager::RemoveTexture(int textureId)
{
	auto _iterator = _textures.begin()+textureId;
	if(textureId >= 0 || textureId <= _textures.size()-1)
		_textures.erase(_iterator);
}
