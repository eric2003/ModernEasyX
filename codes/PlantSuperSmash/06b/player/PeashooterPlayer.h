#pragma once
#include "util.h"
#include "Camera.h"
#include "Player.h"
#include "PeaBullet.h"
#include <graphics.h>

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_attack_ex_left;
extern Atlas atlas_peashooter_attack_ex_right;

extern Camera main_camera;

class PeashooterPlayer : public Player
{
public:
    PeashooterPlayer()
    {
        this->animation_idle_left.set_atlas( &atlas_peashooter_idle_left );
        this->animation_idle_right.set_atlas( &atlas_peashooter_idle_right );
        this->animation_run_left.set_atlas( &atlas_peashooter_run_left );
        this->animation_run_right.set_atlas( &atlas_peashooter_run_right );
        this->animation_attack_ex_left.set_atlas( &atlas_peashooter_attack_ex_left );
        this->animation_attack_ex_right.set_atlas( &atlas_peashooter_attack_ex_right );

        this->animation_idle_left.set_interval( 75 );
        this->animation_idle_right.set_interval( 75 );
        this->animation_run_left.set_interval( 75 );
        this->animation_run_right.set_interval( 75 );
        this->animation_attack_ex_left.set_interval( 75 );
        this->animation_attack_ex_right.set_interval( 75 );

        this->size.x = 96;
        this->size.y = 96;

        this->timer_attack_ex.set_wait_time( this->attack_ex_duration );
        this->timer_attack_ex.set_one_shot( true );
        this->timer_attack_ex.set_callback(
            [&]() {
                this->is_attacking_ex = false;
            }
        );

        this->timer_spwan_pea_ex.set_wait_time( 100 );
        this->timer_spwan_pea_ex.set_callback(
            [&]() {
                this->spawn_pea_bullet( this->speed_pea_ex );
            }
        );
        this->attack_cd = 100;

    }
    ~PeashooterPlayer() = default;

    void on_update(int delta)
    {
        Player::on_update( delta );

        if ( this->is_attacking_ex )
        {
            main_camera.shake( 5, 100 );
            this->timer_attack_ex.on_update( delta );
            this->timer_spwan_pea_ex.on_update( delta );
        }
    }

    void on_draw( const Camera & camera )
    {
        Player::on_draw( camera );
    }

    void on_input( const ExMessage & msg )
    {
        Player::on_input( msg );
    }

    void on_attack()
    {
        this->spawn_pea_bullet( this->speed_pea );

        switch ( rand() % 2 )
        {
        case 0:
            mciSendString( _T( "play pea_shoot_1 form 0" ), NULL, 0, NULL );
            break;
        case 1:
            mciSendString( _T( "play pea_shoot_2 form 0" ), NULL, 0, NULL );
            break;
        }
    }

    void on_attack_ex()
    {
        this->is_attacking_ex = true;
        this->timer_attack_ex.restart();
        this->is_facing_right ? this->animation_attack_ex_right.reset() : this->animation_attack_ex_left.reset();
        mciSendString( _T( "play pea_shoot_ex form 0" ), NULL, 0, NULL );
    }

private:
    void spawn_pea_bullet( float speed )
    {
        Bullet * bullet = new PeaBullet();

        Vector2 bullet_position, bullet_velocity;
        const Vector2 & bullet_size = bullet->get_size();
        bullet_position.x = this->is_facing_right
            ? this->position.x + this->size.x - bullet_size.x / 2
            : this->position.x - bullet_size.x / 2;
        bullet_position.y = this->position.y;
        bullet_velocity.x = this->is_facing_right ? speed : - speed;
        bullet_velocity.y = 0;
        bullet->set_position( bullet_position.x, bullet_position.y );
        bullet->set_velocity( bullet_velocity.x, bullet_velocity.y );

        bullet->set_collide_target( this->id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1 );

        bullet->set_callback(
            [&]() {
                this->mp += 25;
            }
        );
        bullet_list.push_back( bullet );
    }
private:
    const float speed_pea = 0.75f;         // 普通攻击豌豆子弹速度
    const float speed_pea_ex = 1.5f;       // 特殊攻击豌豆子弹速度
    const int attack_ex_duration = 2500;   // 特殊攻击状态持续时长
private:
    Timer timer_attack_ex;                // 特殊攻击状态定时器
    Timer timer_spwan_pea_ex;             // 豌豆子弹发射定时器
};