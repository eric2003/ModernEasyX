#pragma once
#include "util.h"
#include "Camera.h"


class Platform
{
public:
    struct CollisionShape
    {
        float y;
        float left, right;
    };
public:
    CollisionShape shape;
    IMAGE * img = nullptr;
    POINT render_position = { 0 };
public:
    Platform() = default;
    ~Platform() = default;
    void on_draw( const Camera & camera ) const
    {
        putimage_alpha( camera, this->render_position.x, this->render_position.y, img );
    }
};