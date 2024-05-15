#include "Texture.h"
#include "../Core/Types.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

using namespace Sandbox;

// std::map<uint8_t, GLenum> textureUnitMap = 

// std::map<TextureType, String> textureTypeMap = {
// 	{TextureType::DIFFUSE, "diffuse"},
// 	{TextureType::SPECULAR,"specular"},
// 	{TextureType::EMISSIVE,"emissive"},
// };

Texture::Texture(const char* texturePath, ImageFormat imageType, TextureType textureType, GLint texWrapMethod)
{
	this->_type = textureType;
	Load(texturePath, imageType, texWrapMethod);
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

void Texture::Load(const char* texturePath, ImageFormat imageType, GLint texWrapMethod)
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texWrapMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texWrapMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	_data = stbi_load(texturePath, &this->_width, &this->_height, &this->_nrOfchannels, 0);
	if (_data)
	{
		if (imageType == ImageFormat::JPG)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}		
		else if(imageType == ImageFormat::PNG)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "Texture_load: Failed to load texture" << std::endl;
	}

	stbi_image_free(_data);
}

const Texture& TextureManager::GetTexture(int textureId) const
{
	if(textureId >= 0 || textureId <= _textures.size()-1)
		return _textures.at(textureId);
}

void TextureManager::AddTexture(Texture& newTexture)
{
	if(newTexture._texture != NULL)
		this->_textures.push_back(newTexture);
}

void TextureManager::RemoveTexture(int textureId)
{
	auto _iterator = _textures.begin()+textureId;
	if(textureId >= 0 || textureId <= _textures.size()-1)
		_textures.erase(_iterator);
}
