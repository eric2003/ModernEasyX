#include <iostream>
#include <string>
#include <graphics.h>
#include "Animation.h"

//teyvat-survivors

Animation anim_left_player( _T("../../img/player_left_%d.png"), 6, 45 );
Animation anim_right_player( _T("../../img/player_right_%d.png"), 6, 45 );

POINT player_pos = {500, 500};
int PLAYER_SPEED = 5;

void DrawPlayer(int delta, int dir_x){
    static bool facing_left = false;
    if ( dir_x < 0 ) {
        facing_left = true;
    }
    else if ( dir_x > 0 ) {
        facing_left = false;
    }
    if ( facing_left ) {
        anim_left_player.Play( player_pos.x, player_pos.y, delta );
    }
    else {
        anim_right_player.Play( player_pos.x, player_pos.y, delta );
    }
}

int main()
{
    initgraph(1280,720);
    bool running = true;
    
    ExMessage msg;
	IMAGE img_background;
    bool is_move_up = false;
    bool is_move_down = false;
    bool is_move_left = false;
    bool is_move_right = false;
	loadimage(&img_background,_T("../../img/background.png"));
    
    BeginBatchDraw();
    while( running ){
        DWORD start_time = GetTickCount();
        while( peekmessage(&msg) ){
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

        if ( is_move_up ) {
            player_pos.y -= PLAYER_SPEED;
        }

        if ( is_move_down ) {
            player_pos.y += PLAYER_SPEED;
        }

        if ( is_move_left ) {
            player_pos.x -= PLAYER_SPEED;
        }

        if ( is_move_right ) {
            player_pos.x += PLAYER_SPEED;
        }

        cleardevice();
	
		putimage(0,0,&img_background);

        //DrawPlayer( 45, 1 );
        DrawPlayer( 45, -1 );
        
        FlushBatchDraw();
        
        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;
        if ( delta_time < 1000 / 144 ){
            Sleep(1000/144 - delta_time);
        }
    }
    
    EndBatchDraw();
    return 0;
}
