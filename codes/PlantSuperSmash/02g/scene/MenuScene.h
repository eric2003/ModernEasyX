#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "Animation.h"
#include <iostream>

extern Atlas atlas_peashooter_run_right;
extern SceneManager sceneManager;

class MenuScene :public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;
    void on_enter() {
        //std::cout << "Enter the main menu" << std::endl;
        this->animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
        this->animation_peashooter_run_right.set_interval( 75 );
        this->animation_peashooter_run_right.set_loop( true );
    };
    void on_update(int delta) {
        //std::cout << "Main menu is running... delta = " << delta << std::endl;
        this->animation_peashooter_run_right.on_update( delta );
    };
    void on_draw() {
        //outtextxy( 0, 0, _T( "Main menu drawing content" ) );
        this->animation_peashooter_run_right.on_draw( 100, 100 );
    };
    void on_input(const ExMessage &msg) {
        if ( msg.message == WM_KEYDOWN ) {
            sceneManager.switch_to(SceneManager::SceneType::Game);
        }
    };
    void on_exit() {
        std::cout << "Exit the main menu" << std::endl;
    };

private:
    Animation animation_peashooter_run_right;

};
