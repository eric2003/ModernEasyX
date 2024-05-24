#pragma once
#include "Camera.h"
#include "Timer.h"
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
        this->animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
        this->animation_peashooter_run_right.set_interval( 75 );
        this->animation_peashooter_run_right.set_loop( true );

        this->timer.set_wait_time( 1000 );
        this->timer.set_one_shot( false );
        this->timer.set_callback(
            []() {
                std::cout << "Shot!" << std::endl;
            }
        );
    };
    void on_update(int delta) {
        this->timer.on_update( delta );
        this->camera.on_update( delta );
        this->animation_peashooter_run_right.on_update( delta );
    };
    void on_draw() {
        const Vector2 & pos_camera = camera.get_position();
        //this->animation_peashooter_run_right.on_draw( 100, 100 );
        int x = static_cast<int>( 100 - pos_camera.x );
        int y = static_cast<int>( 100 - pos_camera.y );
        this->animation_peashooter_run_right.on_draw( x, y );
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
    Timer timer;
    Camera camera;
    Animation animation_peashooter_run_right;

};
