#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL3/SDL.h>
#include <vector>

void renderTile(SDL_Renderer* renderer, SDL_Texture* texture, const std::vector<std::vector<int>>& tilemap, int tilesize);

#

