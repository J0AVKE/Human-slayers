#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SDL3/SDL.h>
#include <vector>

struct Animation {
    std::vector<SDL_Texture*> frames;
	int frameNo;
};

enum State
{
	IDLE,
    RUN,
    ATTACK,
};

void loadImage(SDL_Renderer* renderer, std::string filename, Animation& frameName);
#endif
