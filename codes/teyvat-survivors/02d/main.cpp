#include <iostream>
#include <string>
#include <graphics.h>
#include "Player.h"

//teyvat-survivors

IMAGE img_background;

int main()
{
    initgraph(WINDOW_WIDTH,WINDOW_HEIGHT);
    bool running = true;
    
    ExMessage msg;

	loadimage(&img_background,_T("../../img/background.png"));

    Player player;
    
    BeginBatchDraw();
    while( running ){
        DWORD start_time = GetTickCount();
        while( peekmessage(&msg) ){
            player.ProcessEvent( msg );
        }

        player.Move();
        cleardevice();
	
		putimage(0,0,&img_background);
        player.Draw( 1000 / 144 );
        
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
