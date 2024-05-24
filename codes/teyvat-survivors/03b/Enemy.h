#pragma once
#include <graphics.h>
#include "Animation.h"
#include "Bullet.h"
#include "Player.h"

class Enemy
{
public:
    Enemy() {
        loadimage(&img_shadow,_T("../../img/shadow_enemy.png"));
        this->anim_left  = new Animation( _T("../../img/enemy_left_%d.png"), 6, 45 );
        this->anim_right = new Animation( _T("../../img/enemy_right_%d.png"), 6, 45 );

        //Enemy spawn border
        enum class SpawnEdge {
            Up = 0,
            Down,
            Left,
            Right
        };

        //Places enemies at random locations outside the map border
        SpawnEdge edge = static_cast<SpawnEdge>( rand() % 4 );
        switch ( edge )
        {
        case SpawnEdge::Up:
            this->position.x = rand() % WINDOW_WIDTH;
            this->position.y = -FRAME_HEIGHT;
            break;
        case SpawnEdge::Down:
            this->position.x = rand() % WINDOW_WIDTH;
            this->position.y = WINDOW_HEIGHT;
            break;
        case SpawnEdge::Left:
            this->position.x = -FRAME_WIDTH;
            this->position.y = rand() % WINDOW_HEIGHT;
            break;
        case SpawnEdge::Right:
            this->position.x = WINDOW_WIDTH;
            this->position.y = rand() % WINDOW_HEIGHT;
            break;
        default:
            break;
        }
    }
    ~Enemy() {
        delete this->anim_left;
        delete this->anim_right;
    }

    bool CheckBulletCollision(const Bullet & bullet){
        bool is_overlap_x = bullet.position.x >= position.x &&
                          bullet.position.x <= position.x + this->FRAME_WIDTH;
        bool is_overlap_y = bullet.position.y >= position.y &&
                          bullet.position.y <= position.y + this->FRAME_HEIGHT;

        return is_overlap_x && is_overlap_y;
    }

    bool CheckPlayerCollision(const Player & player){
        POINT check_position = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };
        return player.InPlayerRect( check_position );
    }

    void Move(const Player & player) {
        const POINT & player_position = player.GetPosition();
        int dir_x = player_position.x - this->position.x;
        int dir_y = player_position.y - this->position.y;
        double len_dir = sqrt( dir_x * dir_x +  dir_y * dir_y );
        if ( len_dir != 0 ) {
            double normalized_x = dir_x / len_dir;
            double normalized_y = dir_y / len_dir;
            position.x += static_cast<int>( SPEED * normalized_x );
            position.y += static_cast<int>( SPEED * normalized_y );
        }
        if ( dir_x < 0 ) {
            this->facing_left = true;
        }
        else if ( dir_x > 0 ) {
            this->facing_left = false;
        }
    }
    void Draw( int delta ) {
        int pos_shadow_x = position.x + ( FRAME_WIDTH - SHADOW_WIDTH ) / 2;
        int pos_shadow_y = position.y + FRAME_HEIGHT - 35;

        putimage_alpha(pos_shadow_x,pos_shadow_y,&img_shadow);

        if ( facing_left ) {
            this->anim_left->Play( position.x, position.y, delta );
        }
        else{
            this->anim_right->Play( position.x, position.y, delta );
        }
    }
    void Hurt() {
        this->alive = false;
    }
    bool CheckAlive() {
        return this->alive;
    }
private:
    const int SPEED = 2;
    const int FRAME_WIDTH = 80;
    const int FRAME_HEIGHT = 80;
    const int SHADOW_WIDTH = 48;
private:
    IMAGE img_shadow;
    Animation * anim_left;
    Animation * anim_right;
    POINT position = {0, 0};

    bool facing_left = false;
    bool alive = true;
};

