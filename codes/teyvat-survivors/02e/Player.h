#pragma once
#include <string>
#include <graphics.h>
#include <vector>
#include "Animation.h"

class Player
{
public:
    Player() {
        loadimage(&img_shadow,_T("../../img/shadow_player.png"));
        this->anim_left  = new Animation( _T("../../img/player_left_%d.png"), 6, 45 );
        this->anim_right = new Animation( _T("../../img/player_right_%d.png"), 6, 45 );
    }
    ~Player() {
        delete this->anim_left;
        delete this->anim_right;
    }
    void ProcessEvent( const ExMessage & msg ) {
        if ( msg.message == WM_KEYDOWN ) {
            switch ( msg.vkcode )
            {
            case VK_UP:
                is_move_up = true;
                break;
            case VK_DOWN:
                is_move_down = true;
                break;
            case VK_LEFT:
                is_move_left = true;
                break;
            case VK_RIGHT:
                is_move_right = true;
                break;
            default:
                break;
            }
        }
        else if ( msg.message == WM_KEYUP ) {
            switch ( msg.vkcode )
            {
            case VK_UP:
                is_move_up = false;
                break;
            case VK_DOWN:
                is_move_down = false;
                break;
            case VK_LEFT:
                is_move_left = false;
                break;
            case VK_RIGHT:
                is_move_right = false;
                break;
            default:
                break;
            }
        }
    }
    void Move() {
        int dir_x = is_move_right - is_move_left;
        int dir_y = is_move_down - is_move_up;
        double len_dir = sqrt( dir_x * dir_x +  dir_y * dir_y );
        if ( len_dir != 0 ) {
            double normalized_x = dir_x / len_dir;
            double normalized_y = dir_y / len_dir;
            position.x += static_cast<int>( SPEED * normalized_x );
            position.y += static_cast<int>( SPEED * normalized_y );
        }

        if ( position.x < 0 )  position.x = 0;
        if ( position.y < 0 )  position.y = 0;
        if ( position.x + FRAME_WIDTH > WINDOW_WIDTH ) {
            position.x = WINDOW_WIDTH - FRAME_WIDTH;
        }
        if ( position.y + FRAME_HEIGHT > WINDOW_HEIGHT ) {
            position.y = WINDOW_HEIGHT - FRAME_HEIGHT;
        }
    }
    void Draw( int delta ) {
        int pos_shadow_x = position.x + ( FRAME_WIDTH - SHADOW_WIDTH ) / 2;
        int pos_shadow_y = position.y + FRAME_HEIGHT - 8;

        putimage_alpha(pos_shadow_x,pos_shadow_y,&img_shadow);

        int dir_x = is_move_right - is_move_left;
        int dir_y = is_move_down - is_move_up;

        static bool facing_left = false;
        if ( dir_x < 0 ) {
            facing_left = true;
        }
        else if ( dir_x > 0 ) {
            facing_left = false;
        }
        if ( facing_left ) {
            this->anim_left->Play( position.x, position.y, delta );
        }
        else{
            this->anim_right->Play( position.x, position.y, delta );
        }
    }

    const POINT & GetPosition() const{
        return this->position;
    }

    bool InPlayerRect( const POINT & point ) const {
        bool is_overlap_x = point.x >= this->position.x &&
                            point.x <= this->position.x + this->FRAME_WIDTH;
        bool is_overlap_y = point.y >= this->position.y &&
                            point.y <= this->position.y + this->FRAME_HEIGHT;

        return is_overlap_x && is_overlap_y;
    }
private:
    const int SPEED = 5;
    const int FRAME_WIDTH = 80;
    const int FRAME_HEIGHT = 80;
    const int SHADOW_WIDTH = 32;
private:
    IMAGE img_shadow;
    Animation * anim_left;
    Animation * anim_right;
    POINT position = {500, 500};

    bool is_move_up = false;
    bool is_move_down = false;
    bool is_move_left = false;
    bool is_move_right = false;
};

