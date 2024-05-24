#pragma once
#include "Bullet.h"
#include "Animation.h"

extern IMAGE img_pea;
extern Atlas atlas_pea_break;

class PeaBullet : public Bullet
{
public:
    PeaBullet()
    {
        this->size.x = 64;
        this->size.y = 64;

        this->damage = 10;

        this->animation_break.set_atlas( &atlas_pea_break );
        this->animation_break.set_interval( 100 );
        this->animation_break.set_loop( false );
        this->animation_break.set_callback(
            [&]() {
                this->can_remove = true;
            }
        );
    }
    ~PeaBullet() = default;

    void on_collide()
    {
        Bullet::on_collide();
        switch ( rand() % 3 )
        {
        case 0:
            mciSendString( _T("play pea_break_1 from 0"), NULL, 0, NULL);
            break;
        case 1:
            mciSendString( _T("play pea_break_2 from 0"), NULL, 0, NULL);
            break;
        case 2:
            mciSendString( _T("play pea_break_3 from 0"), NULL, 0, NULL);
            break;
        default:
            break;
        }
    }

    void on_update( int delta )
    {
        this->position += velocity * static_cast<float>( delta );

        if ( !this->valid )
        {
            this->animation_break.on_update( delta );
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
            putimage_alpha( camera, static_cast<int>( this->position.x ), static_cast<int>( this->position.y ), &img_pea );
        }
        else
        {
            this->animation_break.on_draw( camera, static_cast<int>( this->position.x ), static_cast<int>( this->position.y ) );
        }
    }
private:
    Animation animation_break; //Íã¶¹×Óµ¯ÆÆËé¶¯»­
};