#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "Collisions.h"

bool checkCollisions(SDL_FRect& playerRect, SDL_FRect& wall)
{
    return (playerRect.x < wall.x + wall.w &&
            playerRect.x + playerRect.w > wall.x &&
            playerRect.y < wall.y + wall.h &&
            playerRect.y + playerRect.h > wall.y);
}


void updatePhysics(SDL_FRect& playerDest, std::vector<SDL_FRect>& mapObstacles, float& xVelocity, float& yVelocity, const float physicsGravity, bool& grounded, bool xchange)
{
    if (xchange) playerDest.x += xVelocity;
    // Horizontal axis movements collision of the player to the wall/Obstacle
    for (auto& wall: mapObstacles)
    {
        if (checkCollisions(playerDest, wall))
        {
            if (xVelocity > 0.0f)
            {
                playerDest.x = wall.x - playerDest.w;
            }

            else if (xVelocity < 0.0f)
            {
                playerDest.x = wall.x + wall.w;
            }
            if (xchange)
            {
                xVelocity = 0.0f;
            }
            break;
        }
    }

    yVelocity += physicsGravity;
    playerDest.y += yVelocity;

    for (auto& wall:mapObstacles)
    {
        if (checkCollisions(playerDest, wall))
        {
            if (yVelocity > 0.0f)
            {
                playerDest.y = wall.y - playerDest.h;
                grounded = true;
            }
            else if (yVelocity < 0.0f)
            {
                playerDest.y = wall.y + wall.h;
            }
            yVelocity = 0.0f;
            break;
        }
    }
}
void updatePhysics(SDL_FRect& playerDest, SDL_FRect& mapObstacles, float& xVelocity, float& yVelocity, const float physicsGravity, bool& grounded, bool xchange)
{
    // Horizontal axis movements collision of the player to the wall/Obstacle
    if (checkCollisions(playerDest, mapObstacles))
    {
        if (xVelocity > 0.0f)
        {
            playerDest.x = mapObstacles.x - playerDest.w;
        }

        else if (xVelocity < 0.0f)
        {
            playerDest.x = mapObstacles.x + mapObstacles.w;
        }
        if (xchange)
        {
            xVelocity = 0.0f;
        }
    }

    if (checkCollisions(playerDest, mapObstacles))
    {
        if (yVelocity > 0.0f)
        {
            playerDest.y = mapObstacles.y - playerDest.h;
            grounded = true;
        }
        else if (yVelocity < 0.0f)
        {
            playerDest.y = mapObstacles.y + mapObstacles.h;
        }
        yVelocity = 0.0f;
    }
}
