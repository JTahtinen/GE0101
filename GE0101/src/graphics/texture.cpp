#include "texture.h"
#include <GLEW/glew.h>
#include <SDL2/SDL_image.h>
#include "../defs.h"



Texture::Texture(const std::string& filepath)
	: 
	_filepath(filepath)
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	SDL_Surface* texImage = IMG_Load(filepath.c_str());

	if (!texImage)
	{
		WARN("Could not open texture: " << filepath);
		__debugbreak();
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texImage->w, texImage->h,
		0, GL_RGBA, GL_UNSIGNED_BYTE, texImage->pixels);
	unbind();
	SDL_FreeSurface(texImage);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}