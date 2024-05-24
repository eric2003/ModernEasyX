#pragma once
#include <graphics.h>
#include "Scene.h"

extern Scene * menu_scene;
extern Scene * game_scene;
extern Scene * selector_scene;

class SceneManager
{
public:
    enum class SceneType {
        Menu,
        Game,
        Selector
    };
public:
    SceneManager() = default;
    ~SceneManager() = default;
    void set_current_scene( Scene * scene ) {
        this->current_scene = scene;
        this->current_scene->on_enter();
    }

    void switch_to( SceneType type ) {
        this->current_scene->on_exit();
        switch ( type )
        {
        case SceneManager::SceneType::Menu:
            this->current_scene = menu_scene;
            break;
        case SceneManager::SceneType::Game:
            this->current_scene = game_scene;
            break;
        case SceneManager::SceneType::Selector:
            this->current_scene = selector_scene;
            break;
        default:
            break;
        }
        this->current_scene->on_enter();
    }

    void on_update(int delta) {
        this->current_scene->on_update(delta);
    }

    void on_draw() {
        this->current_scene->on_draw();
    }

    void on_input(const ExMessage &msg) {
        this->current_scene->on_input( msg );
    }

private:
    Scene * current_scene = nullptr;

};
