#ifndef ENEMY_H
#define ENENY_H

#include <SDL3/SDL.h>
#include <iostream>
#include "Animations.h"
#include "Health.h"

enum EnemyState{
    PATROL,
    ATTACKPLAYER,
};

struct Enemy{
    std::string name;
    SDL_FRect dst;
    EnemyState state = PATROL;
    int patrolBegins;
    int patrolEnds;
    int direction = 1;
    float xvel;
    float yvel;
    bool grounded = false;
    bool flip = false;
    int index = 0;
    int safe = 0;
    SDL_FlipMode flipframe = SDL_FLIP_NONE;
    State enemyState = RUN;
    Health health;
    std::vector<Animation> enemyFrames;
};


void enemyAI(Enemy& enemy, SDL_FRect& dst, float& current_health, State& player);

#endif
