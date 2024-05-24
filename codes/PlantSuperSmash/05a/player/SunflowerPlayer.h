#pragma once
#include "util.h"
#include "Camera.h"
#include "Player.h"
#include <graphics.h>

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;

class SunflowerPlayer : public Player
{
public:
    SunflowerPlayer()
    {
        this->animation_idle_left.set_atlas( &atlas_sunflower_idle_left );
        this->animation_idle_right.set_atlas( &atlas_sunflower_idle_right );
        this->animation_run_left.set_atlas( &atlas_sunflower_run_left );
        this->animation_run_right.set_atlas( &atlas_sunflower_run_right );

        this->animation_idle_left.set_interval( 75 );
        this->animation_idle_right.set_interval( 75 );
        this->animation_run_left.set_interval( 75 );
        this->animation_run_right.set_interval( 75 );
    }
    ~SunflowerPlayer() = default;

    void on_update(int delta)
    {
        //std::cout << "向日葵正在更新...\n";
        Player::on_update( delta );
    }

    void on_draw( const Camera & camera )
    {
        Player::on_draw( camera );
    }

    void on_input( const ExMessage & msg )
    {
        Player::on_input( msg );
    }
private:
};