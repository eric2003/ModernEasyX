#pragma once
#include "Bullet.h"
#include "Animation.h"


extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;
extern Camera main_camera;

class SunBulletEx : public Bullet
{
public:
    SunBulletEx()
    {
        this->size.x = 288;
        this->size.y = 288;

        this->damage = 20;

        this->animation_idle.set_atlas( &atlas_sun_ex );
        this->animation_idle.set_interval( 50 );

        this->animation_explode.set_atlas( &atlas_sun_ex_explode );
        this->animation_explode.set_interval( 50 );
        this->animation_explode.set_loop( false );
        this->animation_explode.set_callback(
            [&]() {
                this->can_remove = true;
            }
        );

        IMAGE * frame_idle = this->animation_idle.get_frame();
        IMAGE * frame_explode = this->animation_explode.get_frame();

        this->explode_render_offset.x = ( frame_idle->getwidth() - frame_explode->getwidth() ) / 2.0f;
        this->explode_render_offset.y = ( frame_idle->getheight() - frame_explode->getheight() ) / 2.0f;

    }

    ~SunBulletEx() = default;

    void on_collide()
    {
        Bullet::on_collide();

        main_camera.shake( 20, 350 );

        mciSendString( _T("play sun_explode_ex from 0"), NULL, 0, NULL);

    }

    void on_update( int delta )
    {
        if ( this->valid )
        {
            this->position += this->velocity * static_cast<float>( delta );
        }

        if ( !this->valid )
        {
            this->animation_explode.on_update( delta );
        }
        else
        {
            this->animation_idle.on_update( delta );
        }

        if ( this->check_if_exceeds_screen() )
        {
            this->can_remove = true;
        }
    }

    void on_draw( const Camera &camera ) const 
    {
        if ( this->valid )
        {
            this->animation_idle.on_draw( camera, static_cast<int>( this->position.x ), static_cast<int>( this->position.y ) );
        }
        else
        {
            this->animation_explode.on_draw( camera,
                static_cast<int>( this->position.x + this->explode_render_offset.x ), 
                static_cast<int>( this->position.y + this->explode_render_offset.y ) );
        }
    }

    bool check_collision( const Vector2 & position, const Vector2 & size )
    {
        bool is_collide_x = ( max( this->position.x - this->size.x, position.x + size.x ) -
            min( this->position.x, position.x ) <= this->size.x + size.x );
        bool is_collide_y = ( max( this->position.y - this->size.y, position.y + size.y ) -
            min( this->position.y, position.y ) <= this->size.y + size.y );

        return is_collide_x && is_collide_y;
    }
private:
    const float gravity = 1.0e-3f; // 日光炸弹重力
private:
    Animation animation_idle;      // 日光炸弹默认动画
    Animation animation_explode;   // 日光炸弹爆炸动画
    Vector2 explode_render_offset; // 爆炸动画渲染偏倚
};