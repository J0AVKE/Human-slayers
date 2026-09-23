#include <SDL3/SDL.h>
#include <iostream>
#include "Animations.h"
#include <SDL3_image/SDL_image.h>

void loadImage(SDL_Renderer* renderer, std::string filename, Animation& frameName)
{
	for (int i = 1; i <= frameName.frameNo; ++i)
	{
		std::string fullpath = filename + std::to_string(i) + ".png";

		// Loads texture to the vector in the struct
		SDL_Texture* imgTexture = IMG_LoadTexture(renderer, fullpath.c_str());
		if (imgTexture){
			frameName.frames.push_back(imgTexture);
		}
	}
}
