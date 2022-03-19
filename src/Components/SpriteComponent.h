#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include <string>

struct SpriteComponent {
	std::string assetId;
	int width;
	int height;
	SDL_Rect srcRect;

	SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int srcRectX = 0, int srcRectY = 0)
	{
		this->assetId = assetId;
		this->width = width;
		this->height = height;
		this->srcRect = {srcRectX, srcRectY, width, height};
	}
};

#endif
