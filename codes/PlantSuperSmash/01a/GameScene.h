#pragma once
#include "Scene.h"
#include <iostream>

class GameScene :public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;
    void on_enter() {
        std::cout << "Enter the game scene" << std::endl;
    };
    void on_update() {
        std::cout << "The game is running..." << std::endl;
    };
    void on_draw() {
        outtextxy( 0, 0, _T( "In-game graphics" ) );
    };
    void on_input(const ExMessage &msg) {};
    void on_exit() {
        std::cout << "Exit during game session" << std::endl;
    };

};
