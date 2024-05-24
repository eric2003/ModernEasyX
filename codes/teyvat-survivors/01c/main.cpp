#include <iostream>
#include <string>
#include <graphics.h>

//teyvat-survivors

int idx_current_anim = 0;
const int PLAYER_ANIM_NUM = 6;

IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];

POINT player_pos = {500, 500};
int PLAYER_SPEED = 5;

void LoadAnimation() {
    for ( std::size_t i = 0; i < PLAYER_ANIM_NUM; ++ i ) {
        std::string path = "../../img/player_left_" + std::to_string( i ) + ".png";
        loadimage( &img_player_left[ i ], path.c_str());
    }
    for ( std::size_t i = 0; i < PLAYER_ANIM_NUM; ++ i ) {
        std::string path = "../../img/player_right_" + std::to_string( i ) + ".png";
        loadimage( &img_player_right[ i ], path.c_str());
    }
}

inline void putimage_alpha( int x, int y, IMAGE * img ) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend( GetImageHDC( NULL ), x, y, w, h,
        GetImageHDC( img ), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
    );
}

int main()
{
    initgraph(1280,720);
    bool running = true;
    
    ExMessage msg;
	IMAGE img_background;
	loadimage(&img_background,_T("../../img/background.png"));
    LoadAnimation();
    
    BeginBatchDraw();
    while( running ){
        DWORD start_time = GetTickCount();
        while( peekmessage(&msg) ){
            if ( msg.message == WM_KEYDOWN ) {
                switch ( msg.vkcode )
                {
                case VK_UP:
                    player_pos.y -= PLAYER_SPEED;
                    break;
                case VK_DOWN:
                    player_pos.y += PLAYER_SPEED;
                    break;
                case VK_LEFT:
                    player_pos.x -= PLAYER_SPEED;
                    break;
                case VK_RIGHT:
                    player_pos.x += PLAYER_SPEED;
                    break;
                default:
                    break;
                }
            }
        }
        static int counter = 0;
        if ( ++ counter % 5 == 0 ) {
            idx_current_anim ++;
        }
        idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;
        cleardevice();
		
		putimage(0,0,&img_background);
        //putimage(player_pos.x,player_pos.y,&img_player_left[ idx_current_anim ]);
        putimage_alpha(player_pos.x,player_pos.y,&img_player_left[ idx_current_anim ]);
        
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
