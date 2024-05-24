#include <iostream>
#include <string>
#include <graphics.h>
#include "MenuScene.h"

IMAGE img_background;
IMAGE img_menu;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 720;


int main()
{
    ExMessage msg;
    const int FPS = 60;
    DWORD timeFPS = 1000 / FPS;

    initgraph(WINDOW_WIDTH,WINDOW_HEIGHT,EW_SHOWCONSOLE);

    BeginBatchDraw();

    std::shared_ptr<Scene> scene(new MenuScene());
    scene->on_enter();

    while( true ){
        DWORD frame_start_time = GetTickCount();
        while( peekmessage(&msg) ){
            scene->on_input( msg );
        }

        scene->on_update();

        cleardevice();

        scene->on_draw();
       
        FlushBatchDraw();
        
        DWORD frame_end_time = GetTickCount();
        DWORD frame_delta_time = frame_end_time - frame_start_time;
        if ( frame_delta_time < timeFPS ){
            Sleep( timeFPS - frame_delta_time );
        }
    }
    
    EndBatchDraw();
    return 0;
}
