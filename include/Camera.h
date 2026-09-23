#ifndef CAMERA_H
#define CAMERA_H

struct Vec2f
{
    float x;
    float y;
};
struct Camera
{
    Vec2f position;
    int width;
    int height;
};

#endif

