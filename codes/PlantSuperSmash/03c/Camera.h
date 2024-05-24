#pragma once
#include <graphics.h>
#include "Timer.h"
#include "Vector2.h"
#include <iostream>


class Camera {
public:
    Camera() {
        this->timer_shake.set_one_shot( true );
        this->timer_shake.set_callback(
            [&]() {
                this->is_shaking = false;
                this->reset();
            }
        );
    }
    ~Camera() {}
public:

    Vector2 get_position() const {
        return this->position;
    }

    void reset() {
        this->position.x = 0;
        this->position.y = 0;
    }

    void on_update( int delta ) {
        //const Vector2 speed = { -0.35f,0 };
        //this->position += speed * static_cast<float>( delta );
        this->timer_shake.on_update( delta );
        if ( this->is_shaking ) {
            this->position.x = ( -50 + rand() % 100 ) / 50.0f * this->shaking_strength;
            this->position.y = ( -50 + rand() % 100 ) / 50.0f * this->shaking_strength;
        }
    }

    void shake( float strength, int duration ) {
        std::cout << "shake\n";
        this->is_shaking = true;
        this->shaking_strength = strength;

        this->timer_shake.set_wait_time( duration );
        this->timer_shake.restart();
    }
private:
    Vector2 position;
    Timer timer_shake;
    bool is_shaking = false;
    float shaking_strength = 0;
};