#pragma once
#include <graphics.h>
#include <cmath>


class Vector2 {
public:
    Vector2() = default;
    ~Vector2() = default;
    Vector2( float x, float y) {
        this->x = x;
        this->y = y;
    }
public:
    Vector2 & operator +=( const Vector2 & rhs ) {
        this->x += rhs.x;
        this->y += rhs.y;
        return * this;
    }
    Vector2 & operator -=( const Vector2 & rhs ) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return * this;
    }
    Vector2 & operator +=( const float & value ) {
        this->x += value;
        this->y += value;
        return * this;
    }

    Vector2 & operator -=( const float & value ) {
        this->x -= value;
        this->y -= value;
        return * this;
    }

    Vector2 & operator *=( const float & value ) {
        this->x *= value;
        this->y *= value;
        return * this;
    }

    Vector2 & operator /=( const float & value ) {
        this->x /= value;
        this->y /= value;
        return * this;
    }

    Vector2 operator *( const float & value ) const {
        return Vector2(this->x*value,  this->y * value);
    }

    float length() {
        return std::sqrt( x * x + y * y );
    }

    Vector2 normalize() {
        float len = this->length();
        if ( len == 0 ) {
            return Vector2( 0, 0 );
        }
        return Vector2( this->x/len,  this->y/len );
    }

public:
    float x = 0;
    float y = 0;
};