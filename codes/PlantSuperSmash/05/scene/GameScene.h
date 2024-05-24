#pragma once
#include "util.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Platform.h"

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

extern Camera main_camera;
extern SceneManager sceneManager;
extern std::vector<Platform> platform_list;

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

        platform_list.resize( 4 );

        Platform & large_platform = platform_list[ 0 ];
        large_platform.img = &img_platform_large;
        large_platform.render_position.x = 122;
        large_platform.render_position.y = 455;
        large_platform.shape.left = static_cast<float>(large_platform.render_position.x) + 30;
        large_platform.shape.right = static_cast<float>(large_platform.render_position.x) + img_platform_large.getwidth() - 30;
        large_platform.shape.y = static_cast<float>( large_platform.render_position.y ) + 60;

        Platform & small_platform_1 = platform_list[ 1 ];
        small_platform_1.img = &img_platform_small;
        small_platform_1.render_position.x = 175;
        small_platform_1.render_position.y = 360;
        small_platform_1.shape.left = static_cast<float>(small_platform_1.render_position.x) + 40;
        small_platform_1.shape.right = static_cast<float>(small_platform_1.render_position.x) + img_platform_small.getwidth() - 40;
        small_platform_1.shape.y = static_cast<float>( small_platform_1.render_position.y ) + img_platform_small.getheight() / 2;

        Platform & small_platform_2 = platform_list[ 2 ];
        small_platform_2.img = &img_platform_small;
        small_platform_2.render_position.x = 855;
        small_platform_2.render_position.y = 360;
        small_platform_2.shape.left = static_cast<float>(small_platform_2.render_position.x) + 40;
        small_platform_2.shape.right = static_cast<float>(small_platform_2.render_position.x) + img_platform_small.getwidth() - 40;
        small_platform_2.shape.y = static_cast<float>( small_platform_2.render_position.y ) + img_platform_small.getheight() / 2;

        Platform & small_platform_3 = platform_list[ 3 ];
        small_platform_3.img = &img_platform_small;
        small_platform_3.render_position.x = 515;
        small_platform_3.render_position.y = 225;
        small_platform_3.shape.left = static_cast<float>(small_platform_3.render_position.x) + 40;
        small_platform_3.shape.right = static_cast<float>(small_platform_3.render_position.x) + img_platform_small.getwidth() - 40;
        small_platform_3.shape.y = static_cast<float>( small_platform_3.render_position.y ) + img_platform_small.getheight() / 2;
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
