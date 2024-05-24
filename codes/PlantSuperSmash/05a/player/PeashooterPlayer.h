#pragma once
#include "util.h"
#include "Camera.h"
#include "Player.h"
#include <graphics.h>

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;

class PeashooterPlayer : public Player
{
public:
    PeashooterPlayer()
    {
        this->animation_idle_left.set_atlas( &atlas_peashooter_idle_left );
        this->animation_idle_right.set_atlas( &atlas_peashooter_idle_right );
        this->animation_run_left.set_atlas( &atlas_peashooter_run_left );
        this->animation_run_right.set_atlas( &atlas_peashooter_run_right );

        this->animation_idle_left.set_interval( 75 );
        this->animation_idle_right.set_interval( 75 );
        this->animation_run_left.set_interval( 75 );
        this->animation_run_right.set_interval( 75 );
    }
    ~PeashooterPlayer() = default;

    void on_update(int delta)
    {
        //std::cout << "豌豆射手正在更新...\n";
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