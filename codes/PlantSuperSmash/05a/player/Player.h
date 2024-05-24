#pragma once
#include "util.h"
#include "Camera.h"
#include "Animation.h"
#include "PlayerID.h"
#include <graphics.h>

class Player
{
public:
    Player()
    {
        this->current_animation = &this->animation_idle_right;
    }
    ~Player() = default;

    virtual void on_run( float distance )
    {
        this->position.x += distance;
    }

    virtual void on_update(int delta)
    {
        int direction = is_right_key_down - is_left_key_down;
        std::cout << " Player::virtual void on_update(int delta) direction= " << direction << "\n";
        if ( direction != 0 )
        {
            this->is_facing_right = direction > 0;
            this->current_animation = this->is_facing_right ? &this->animation_run_right : &this->animation_run_left;
            float distance = direction * this->run_velocity * delta;
            this->on_run( distance );
        }
        else
        {
            this->current_animation = this->is_facing_right ? &this->animation_idle_right : &this->animation_idle_left;
        }
        this->current_animation->on_update( delta );
    }

    virtual void on_draw( const Camera & camera )
    {
        current_animation->on_draw( camera, static_cast<int>( position.x ), static_cast<int>( position.y ) );
    }

    virtual void on_input( const ExMessage & msg )
    {
        std::cout << " Player::virtual void on_input( const ExMessage & msg )\n";
        switch ( msg.message )
        {
        case WM_KEYDOWN:
            switch ( this->id )
            {
            case PlayerID::P1:
                switch ( msg.vkcode )
                {
                    //'A'
                case 0x41:
                    this->is_left_key_down = true;
                    break;
                    //'D'
                case 0x44:
                    this->is_right_key_down = true;
                    break;
                default:
                    break;
                }
                break;
            case PlayerID::P2:
                switch ( msg.vkcode )
                {
                    //'<-'
                case VK_LEFT:
                    this->is_left_key_down = true;
                    break;
                    //'->'``
                case VK_RIGHT:
                    this->is_right_key_down = true;
                    break;
                default:
                    break;
                }

                break;
            default:
                break;
            }
            break;
        case WM_KEYUP:
            switch ( this->id )
            {
            case PlayerID::P1:
                switch ( msg.vkcode )
                {
                    //'A'
                case 0x41:
                    this->is_left_key_down = false;
                    break;
                    //'D'
                case 0x44:
                    this->is_right_key_down = false;
                    break;
                default:
                    break;
                }
                break;
            case PlayerID::P2:
                switch ( msg.vkcode )
                {
                    //'<-'
                case VK_LEFT:
                    this->is_left_key_down = false;
                    break;
                    //'->'``
                case VK_RIGHT:
                    this->is_right_key_down = false;
                    break;
                default:
                    break;
                }

                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    void set_id( PlayerID id )
    {
        this->id = id;
    }

    void set_position( float x, float y )
    {
        this->position.x = x;
        this->position.y = y;
    }

protected:
    const float run_velocity = 0.55f; //跑动速度
protected:
    Vector2 position; //角色位置

    Animation animation_idle_left;  //朝向左的默认动画
    Animation animation_idle_right; //朝向右的默认动画
    Animation animation_run_left;   //朝向左的奔跑动画
    Animation animation_run_right;  //朝向右的奔跑动画

    Animation * current_animation = nullptr;

    PlayerID id = PlayerID::P1; //玩家序号ID

    bool is_left_key_down = false; //向左移动按键是否按下
    bool is_right_key_down = false; //向右移动按键是否按下

    bool is_facing_right = true; //角色是否朝向右侧
};