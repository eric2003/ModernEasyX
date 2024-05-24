#include <iostream>
#include <string>
#include <graphics.h>

//teyvat-survivors

int idx_current_anim = 0;
const int PLAYER_ANIM_NUM = 6;

IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];

void LoadAnimation() {
    for ( std::size_t i = 0; i < PLAYER_ANIM_NUM; ++ i ) {
        //std::wstring path = L"../../img/player_left_" + std::to_wstring( i ) + L".png";
        //loadimage( &img_player_left[ i ], path.c_str() );
        std::string path = "../../img/player_left_" + std::to_string( i ) + ".png";
        loadimage( &img_player_left[ i ], path.c_str());
    }
    for ( std::size_t i = 0; i < PLAYER_ANIM_NUM; ++ i ) {
        //std::wstring path = L"../../img/player_right_" + std::to_wstring( i ) + L".png";
        //loadimage( &img_player_right_[ i ], path.c_str() );
        std::string path = "../../img/player_right_" + std::to_string( i ) + ".png";
        loadimage( &img_player_right[ i ], path.c_str());
    }
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
        }
        static int counter = 0;
        if ( ++ counter % 5 == 0 ) {
            idx_current_anim ++;
        }
        idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;
        cleardevice();
		
		putimage(0,0,&img_background);
        putimage(500,500,&img_player_left[ idx_current_anim ]);
        
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
