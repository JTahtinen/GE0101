#include "texture.h"
#include <GLEW/glew.h>
#include <SDL2/SDL_image.h>
#include "../defs.h"
#include "renderers/renderer.h"
#include "../application/assetmanager.h"

Texture::Texture(const std::string& filepath)
	: 
	_filepath(filepath)
{
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &_id));
}

void Texture::bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, _id));
}

void Texture::unbind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, TEXTURE_SLOT_UNBIND));
}


std::shared_ptr<Texture> Texture::loadTexture(const std::string& filepath)
{
	SDL_Surface* texImage = IMG_Load(filepath.c_str());
	if (!texImage)
	{
		ERR("Could not open texture: " << filepath);
		return nullptr;
	}
	Texture* texture = new Texture(filepath);
	//std::unique_ptr<Texture> texture = std::make_unique<Texture>(filepath);
	GLCALL(glGenTextures(1, &texture->_id));
	GLCALL(glBindTexture(GL_TEXTURE_2D, texture->_id));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	texture->_widthInPixels = texImage->w;
	texture->_heightInPixels = texImage->h;
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texImage->w, texImage->h,
		0, GL_RGBA, GL_UNSIGNED_BYTE, texImage->pixels));
	SDL_FreeSurface(texImage);

	return std::shared_ptr<Texture>(texture);
}