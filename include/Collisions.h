#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <iostream>
#include <SDL3/SDL.h>
#include <vector>

// returns true if collision occur and false if not
bool checkCollisions(SDL_FRect& playerRect, SDL_FRect& wall);

// Updates the player movements and restricts player movement if collisions occur
void updatePhysics(SDL_FRect& playerDest, std::vector<SDL_FRect>& mapObstacles, float& xVelocity, float& yVelocity, const float physicsGravity, bool& grounded, bool);

void updatePhysics(SDL_FRect& playerDest, SDL_FRect& mapObstacles, float& xVelocity, float& yVelocity, const float physicsGravity, bool& grounded, bool xhange);

#endif
