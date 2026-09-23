#ifndef HEALTH_H
#define HEALTH_H

#include <SDL3/SDL.h>
typedef struct {
    int max_health;
    float current_health;
    SDL_FRect bg_health;
    SDL_FRect displayedHealth;

} Health;

void health(Health& _health);

#endif
