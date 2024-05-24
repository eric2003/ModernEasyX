#pragma once
#include "Vector2.h"
#include "PlayerID.h"
#include "Camera.h"
#include <functional>

class Bullet
{
public:
    Bullet() = default;
    ~Bullet() = default;
    void set_damage( int val )
    {
        this->damage = val;
    }

    int get_damage()
    {
        return this->damage;
    }

    void set_position( float x, float y )
    {
        this->position.x = x;
        this->position.y = y;
    }

    const Vector2 & get_position() const
    {
        return this->position;
    }

    void set_velocity( float x, float y )
    {
        this->velocity.x = x;
        this->velocity.y = y;
    }

    const Vector2 & get_size() const
    {
        return this->size;
    }

    void set_collide_target( PlayerID target )
    {
        this->target_id = target;
    }

    PlayerID get_collide_target() const
    {
        return this->target_id;
    }

    void set_callback(std::function<void()> callback)
    {
        this->callback = callback;
    }

    void set_valid( bool flag )
    {
        this->valid = flag;
    }

    bool get_valid() const
    {
        return valid;
    }

    bool check_can_remove() const
    {
        return this->can_remove;
    }

    virtual void on_collide()
    {
        if (  this->callback )
        {
            this->callback();
        }
    }

    virtual bool check_collision( const Vector2 & position, const Vector2 & size )
    {
        return this->position.x + this->size.x / 2 >= position.x
            && this->position.x + this->size.x / 2 <= position.x + size.x
            && this->position.y + this->size.y / 2 >= position.y
            && this->position.y + this->size.y / 2 <= position.y + size.y;
    }

    virtual void on_update( int delta ) {};
    virtual void on_draw( const Camera &camera ) const {};

protected:
    Vector2 size;                       // 子弹尺寸
    Vector2 position;                   // 子弹位置
    Vector2 velocity;                   // 子弹速度
    int damage = 10;                    // 子弹伤害
    bool valid = true;                  // 子弹是否有效
    bool can_remove = false;            // 子弹是否可以被移除
    std::function<void()> callback;     // 子弹碰撞回调函数
    PlayerID target_id = PlayerID::P1;  //子弹碰撞目标玩家ID

protected:
    bool check_if_exceeds_screen()
    {
        return ( position.x + size.x <= 0 || position.x >= getwidth()
            || position.y + size.y <= 0 || position.y >= getheight() );
    }
};