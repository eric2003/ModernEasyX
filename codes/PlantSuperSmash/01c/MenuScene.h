#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>

extern SceneManager sceneManager;

class MenuScene :public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;
    void on_enter() {
        std::cout << "Enter the main menu" << std::endl;
    };
    void on_update() {
        std::cout << "Main menu is running..." << std::endl;
    };
    void on_draw() {
        outtextxy( 0, 0, _T( "Main menu drawing content" ) );
    };
    void on_input(const ExMessage &msg) {
        if ( msg.message == WM_KEYDOWN ) {
            sceneManager.switch_to(SceneManager::SceneType::Game);
        }
    };
    void on_exit() {
        std::cout << "Exit the main menu" << std::endl;
    };

};
