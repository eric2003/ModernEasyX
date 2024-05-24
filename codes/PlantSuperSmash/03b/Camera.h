#pragma once
#include <graphics.h>
#include <complex>
#include "Vector2.h"


class Camera {
public:
    Camera() {}
    ~Camera() {}
public:
    Vector2 get_position() const {
        return this->position;
    }
    void on_update( int delta ) {
        const Vector2 speed = { -0.35f,0 };
        this->position += speed * static_cast<float>( delta );
    }
private:
    Vector2 position;
};