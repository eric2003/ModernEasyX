#include <iostream>
#include <string>
#include <graphics.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "SelectorScene.h"
#include "SceneManager.h"


IMAGE img_background;
IMAGE img_menu;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 720;

Scene * menu_scene = nullptr;
Scene * game_scene = nullptr;
Scene * selector_scene = nullptr;

SceneManager sceneManager;

int main()
{
    ExMessage msg;
    const int FPS = 60;
    DWORD timeFPS = 1000 / FPS;

    initgraph(WINDOW_WIDTH,WINDOW_HEIGHT,EW_SHOWCONSOLE);

    BeginBatchDraw();

    menu_scene = new MenuScene();
    game_scene = new GameScene();
    selector_scene = new SelectorScene();

    sceneManager.set_current_scene( menu_scene );

    //std::shared_ptr<Scene> scene(new MenuScene());
    //scene->on_enter();

    while( true ){
        DWORD frame_start_time = GetTickCount();
        while( peekmessage(&msg) ){
            //scene->on_input( msg );
            sceneManager.on_input( msg );
        }

        sceneManager.on_update();

        cleardevice();

        sceneManager.on_draw();
       
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
