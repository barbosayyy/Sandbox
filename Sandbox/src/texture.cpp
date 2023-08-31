#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* texturePath, ImageType imageType, GLint texWrapMethod)
{
	load(texturePath, imageType, texWrapMethod);
}

//Texture::Texture(const char* texturePath)
//{
//	load();
//}

void Texture::load(const char* texturePath, ImageType imageType, GLint texWrapMethod)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texWrapMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texWrapMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(texturePath, &this->width, &this->height, &this->nrOfchannels, 0);
	if (data)
	{
		if (imageType == ImageType::JPG)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}		
		else if(imageType == ImageType::PNG)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "Texture_load: Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}