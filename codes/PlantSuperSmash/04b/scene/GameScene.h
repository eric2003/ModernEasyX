#pragma once
#include "util.h"
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

extern Camera main_camera;

extern SceneManager sceneManager;

class GameScene :public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;
    void on_enter()
    {
        this->pos_img_sky.x = ( ::getwidth() - img_sky.getwidth() ) / 2;
        this->pos_img_sky.y = ( ::getheight() - img_sky.getheight() ) / 2;

        this->pos_img_hills.x = ( ::getwidth() - img_hills.getwidth() ) / 2;
        this->pos_img_hills.y = ( ::getheight() - img_hills.getheight() ) / 2;
    }

    void on_update(int delta)
    {
        std::cout << "The game is running..." << std::endl;
    }

    void on_draw( const Camera & camera )
    {
        putimage_alpha( camera, pos_img_sky.x, pos_img_sky.y, &img_sky );
        putimage_alpha( camera, pos_img_hills.x, pos_img_hills.y, &img_hills );
    }
    void on_input( const ExMessage & msg )
    {
        if ( msg.message == WM_KEYDOWN ) {
            sceneManager.switch_to(SceneManager::SceneType::Menu);
        }
    }

    void on_exit()
    {
        std::cout << "Exit during game session" << std::endl;
    }
private:
    POINT pos_img_sky = { 0 }; // Ìì¿Õ±³¾°Í¼Î»ÖÃ
    POINT pos_img_hills = { 0 }; // É½Âö±³¾°Í¼Î»ÖÃ

};
