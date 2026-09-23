#include "Tilemap.h"
#include <SDL3/SDL.h>
#include <vector>

void renderTile(SDL_Renderer* renderer, SDL_Texture* texture, const std::vector<std::vector<int>>& tilemap, int tilesize)
{
   for(int row = 0; row < tilemap.size(); ++row)
   {
       for(int col = 0; col < tilemap[row].size(); ++col)
       {
           int tileID = tilemap[row][col];

           if (tileID == 0) continue;

           SDL_FRect dstRect = {
               (float)(col * tilesize),
               (float)(row * tilesize),
               (float)tilesize,
               (float)tilesize
           };
           SDL_RenderTexture(renderer, texture, NULL, &dstRect);
       }
   } 
}
