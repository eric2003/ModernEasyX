#pragma once
#include "util.h"
#include "Camera.h"
#include "Player.h"
#include "SunBullet.h"
#include <graphics.h>

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;
extern Atlas atlas_sun_text;

extern Player * player_1;
extern Player * player_2;

class SunflowerPlayer : public Player
{
public:
    SunflowerPlayer()
    {
        this->animation_idle_left.set_atlas( &atlas_sunflower_idle_left );
        this->animation_idle_right.set_atlas( &atlas_sunflower_idle_right );
        this->animation_run_left.set_atlas( &atlas_sunflower_run_left );
        this->animation_run_right.set_atlas( &atlas_sunflower_run_right );
        this->animation_attack_ex_left.set_atlas( &atlas_sunflower_attack_ex_left );
        this->animation_attack_ex_right.set_atlas( &atlas_sunflower_attack_ex_right );
        this->animation_sun_text.set_atlas( &atlas_sun_text );

        this->animation_idle_left.set_interval( 75 );
        this->animation_idle_right.set_interval( 75 );
        this->animation_run_left.set_interval( 75 );
        this->animation_run_right.set_interval( 75 );
        this->animation_attack_ex_left.set_interval( 100 );
        this->animation_attack_ex_right.set_interval( 100 );
        this->animation_sun_text.set_interval( 100 );

        this->animation_attack_ex_left.set_loop( false );
        this->animation_attack_ex_right.set_loop( false );
        this->animation_sun_text.set_loop( false );

        this->animation_attack_ex_left.set_callback(
            [&]() {
                this->is_attacking_ex = false;
                this->is_sun_text_visible = false;
            }
        );

        this->animation_attack_ex_right.set_callback(
            [&]() {
                this->is_attacking_ex = false;
                this->is_sun_text_visible = false;
            }
        );

        this->size.x = 96;
        this->size.y = 96;

        this->attack_cd = 250;

    }
    ~SunflowerPlayer() = default;

    void on_update(int delta)
    {
        Player::on_update( delta );
        if ( this->is_sun_text_visible )
        {
            this->animation_sun_text.on_update( delta );
        }
    }

    void on_draw( const Camera & camera )
    {
        Player::on_draw( camera );
        if ( this->is_sun_text_visible )
        {
            Vector2 text_position;
            IMAGE * frame = this->animation_sun_text.get_frame();
            text_position.x = this->position.x - ( this->size.x - frame->getwidth() ) / 2;
            text_position.y = this->position.y - frame->getheight();
            this->animation_sun_text.on_draw( camera, static_cast<int>( text_position.x ), static_cast<int>( text_position.y ) );
        }
    }

    void on_input( const ExMessage & msg )
    {
        Player::on_input( msg );
    }

    void on_attack()
    {
        Bullet * bullet = new SunBullet();
        Vector2 bullet_position;
        const Vector2 & bullet_size = bullet->get_size();

        bullet_position.x = this->position.x + ( this->size.x - bullet_size.x ) / 2;
        bullet_position.y = this->position.y;

        bullet->set_position( bullet_position.x, bullet_position.y );
        bullet->set_velocity( this->is_facing_right ? this->velocity_sun.x : -this->velocity_sun.x, this->velocity_sun.y );

        bullet->set_collide_target( this->id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1 );

        bullet->set_callback(
            [&]() {
                this->mp += 35;
            }
        );

        bullet_list.push_back( bullet );
    }
    void on_attack_ex()
    {
        this->is_attacking_ex = true;
        this->is_sun_text_visible = true;

        this->animation_sun_text.reset();
        this->is_facing_right ? this->animation_attack_ex_right.reset() : this->animation_attack_ex_left.reset();

        Bullet * bullet = new SunBullet();
        Player * target_player = ( this->id == PlayerID::P1 ? player_2 : player_1 );

        Vector2 bullet_position, bullet_velocity;

        const Vector2 & bullet_size = bullet->get_size();
        const Vector2 & target_size = target_player->get_size();
        const Vector2 & target_position = target_player->get_position();

        bullet_position.x = target_position.x + ( target_size.x - bullet_size.x ) / 2;
        bullet_position.y = - this->size.y;

        bullet_velocity.x = 0;
        bullet_velocity.y = this->speed_sun_ex;

        bullet->set_position( bullet_position.x, bullet_position.y );
        bullet->set_velocity( bullet_velocity.x, bullet_velocity.y );

        bullet->set_collide_target( this->id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1 );

        bullet->set_callback(
            [&]() {
                this->mp += 50;
            }
        );
        bullet_list.push_back( bullet );

        mciSendString( _T( "play sun_text form 0" ), NULL, 0, NULL );
    }
private:
    const float speed_sun_ex = 0.15f;                // 大型日光炸弹下落速度
    const Vector2 velocity_sun = { 0.25f, -0.5f };   // 小型日光炸弹抛射速度
private:
    Animation animation_sun_text;       // 头顶文本动画
    bool is_sun_text_visible = false;   // 是否显示头顶文本
};
