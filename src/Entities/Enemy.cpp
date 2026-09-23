#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "Collisions.h"
#include "Animations.h"


void enemyAI(Enemy& enemy, SDL_FRect& dst, float& current_health, State& player)
{
    float closest_x = std::max(enemy.dst.x, std::min(dst.x, enemy.dst.x + enemy.dst.w));
    float closest_y = std::max(enemy.dst.y, std::min(dst.y, enemy.dst.y + enemy.dst.h));

    float dx = dst.x - closest_x;
    float dy = dst.y - closest_y;

    float playersDistance = std::sqrt(dx*dx + dy*dy);
    if (playersDistance < 100)
    {
        enemy.state = ATTACKPLAYER;
    }
    else enemy.state = PATROL;

    if (enemy.state == ATTACKPLAYER)
    {
        enemy.dst.x += (dx / playersDistance) * enemy.xvel;
        enemy.dst.y += (dy / playersDistance) * enemy.yvel;
        if (dx < 0) enemy.flip = true;
        if (dx > 0) enemy.flip = false;
        if (playersDistance == 32)
        {
            enemy.enemyState = IDLE;
        }
        else enemy.enemyState = RUN;

        if (playersDistance < 50)
        {
            if (checkCollisions(dst, enemy.dst))
            {
                if (player == ATTACK)
                {
                    enemy.health.current_health -= .5;
                }
                else 
                {
                    enemy.enemyState = ATTACK;
                    current_health -= .5;
                }
            }
        }
    }
    
    if (enemy.state == PATROL)
    {
        enemy.enemyState = RUN;
        enemy.dst.x += enemy.direction*enemy.xvel;
        if (enemy.dst.x <= enemy.patrolBegins)
        {
            enemy.direction = 1;
            enemy.flip = false;
        }
        if (enemy.dst.x >= enemy.patrolEnds)
        {
            enemy.direction = -1;
            enemy.flip = true;
        }
    }
}
