#pragma once
#include "util.h"
#include "Camera.h"

extern bool is_debug;


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
        if ( is_debug )
        {
            setlinecolor( RGB( 255, 0, 0 ) );
            line( camera, static_cast<int>(this->shape.left), static_cast<int>(this->shape.y),
                static_cast<int>(this->shape.right), static_cast<int>(this->shape.y) );
        }
    }
};