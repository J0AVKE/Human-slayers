#include <SDL3/SDL.h>
#include "Health.h"
#include <iostream>


void health(Health& _health)
{
    float current_width = _health.bg_health.w*(float(_health.current_health)/_health.max_health);
    if (current_width <= 0)
    {
        current_width = 0;
    }
    if (current_width >= _health.bg_health.w)
    {
        current_width = _health.bg_health.w;
    }
    _health.displayedHealth.w = current_width;
}
