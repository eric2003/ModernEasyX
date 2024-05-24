#pragma once
#include "Scene.h"
#include "Animation.h"
#include "SceneManager.h"
#include <iostream>

extern IMAGE img_menu_background;

extern IMAGE img_VS;
extern IMAGE img_1P;
extern IMAGE img_2P;

extern IMAGE img_1P_desc;
extern IMAGE img_2P_desc;

extern IMAGE img_gravestone_left;
extern IMAGE img_gravestone_right;

extern IMAGE img_selector_tip;
extern IMAGE img_selector_background;

extern IMAGE img_1P_selector_btn_idle_left;
extern IMAGE img_1P_selector_btn_idle_right;

extern IMAGE img_1P_selector_btn_down_left;
extern IMAGE img_1P_selector_btn_down_right;

extern IMAGE img_2P_selector_btn_idle_left;
extern IMAGE img_2P_selector_btn_idle_right;

extern IMAGE img_2P_selector_btn_down_left;
extern IMAGE img_2P_selector_btn_down_right;

extern IMAGE img_peashooter_selector_background_left;
extern IMAGE img_peashooter_selector_background_right;

extern IMAGE img_sunflower_selector_background_left;
extern IMAGE img_sunflower_selector_background_right;

extern IMAGE img_sky;
extern IMAGE img_hills;

extern IMAGE img_platform_large;  // 大型平台图片
extern IMAGE img_platform_small;  // 小型平台图片

extern IMAGE img_1P_cursor;  // 1P 指示光标图片
extern IMAGE img_2P_cursor;

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;

extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;

extern Atlas atlas_peashooter_attack_ex_left;
extern Atlas atlas_peashooter_attack_ex_right;

extern Atlas atlas_peashooter_die_left;
extern Atlas atlas_peashooter_die_right;

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;

extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;

extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;

extern Atlas atlas_sunflower_die_left;
extern Atlas atlas_sunflower_die_right;

extern IMAGE img_pea;
extern Atlas atlas_pea_break;

extern Atlas atlas_sun;
extern Atlas atlas_sun_explode;
extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;
extern Atlas atlas_sun_text;

extern Atlas atlas_run_effect;
extern Atlas atlas_jump_effect;
extern Atlas atlas_land_effect;

extern IMAGE img_1P_winner;
extern IMAGE img_2P_winner;
extern IMAGE img_winner_bar;

extern IMAGE img_avatar_peashooter;
extern IMAGE img_avatar_sunflower;

extern SceneManager sceneManager;

class SelectorScene :public Scene
{
public:
    SelectorScene() = default;
    ~SelectorScene() = default;
    void on_enter()
    {
        animation_peashooter.set_atlas( &atlas_peashooter_idle_right );
        animation_sunflower.set_atlas( &atlas_sunflower_idle_right );

        animation_peashooter.set_interval( 100 );
        animation_sunflower.set_interval( 100 );

        static const int OFFSET_X = 50;

        pos_img_VS.x = ( ::getwidth() - img_VS.getwidth() ) / 2;
        pos_img_VS.y = ( ::getheight() - img_VS.getheight() ) / 2;

        pos_img_tip.x = ( ::getwidth() - img_selector_tip.getwidth() ) / 2;
        pos_img_tip.y = ::getheight() - 125;

        pos_img_1P.x = ( ::getwidth() / 2 - img_1P.getwidth() ) / 2 - OFFSET_X;
        pos_img_1P.y = 35;

        pos_img_2P.x = ( ::getwidth() /2  - img_2P.getwidth() ) / 2 + OFFSET_X;
        pos_img_2P.y = pos_img_1P.y;

        pos_img_1P_desc.x = ( ::getwidth() / 2 - img_1P_desc.getwidth() ) / 2 - OFFSET_X;
        pos_img_1P_desc.y = ::getheight() - 150;

        pos_img_2P_desc.x = ( ::getwidth() / 2 - img_2P_desc.getwidth() ) / 2 + OFFSET_X;
        pos_img_2P_desc.y = pos_img_1P_desc.y;

        pos_img_1P_gravestone.x = ( ::getwidth() / 2 - img_gravestone_right.getwidth() ) / 2 - OFFSET_X;
        pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;

        pos_img_2P_gravestone.x = ::getwidth() / 2 + ( ::getwidth() / 2 - img_gravestone_left.getwidth() ) / 2 + OFFSET_X;
        pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;

        pos_animation_1P.x = ( ::getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth() ) / 2 - OFFSET_X;
        pos_animation_1P.y = pos_img_1P_gravestone.y + 80;

        pos_animation_2P.x = ::getwidth() / 2 + ( ::getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth() ) / 2 + OFFSET_X;
        pos_animation_2P.y = pos_animation_1P.y;

        pos_img_1P_name.y = pos_animation_1P.y + 155;
        pos_img_2P_name.y = pos_img_1P_name.y;

        pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
        pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + ( img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight() ) / 2;

        pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
        pos_1P_selector_btn_right.y = pos_img_1P_gravestone.y;

        pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
        pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;

        pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
        pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

    }

    void on_update()
    {
        std::cout << "The game is running..." << std::endl;
    }

    void on_draw( const Camera & camera )
    {
        outtextxy( 0, 0, _T( "In-game graphics" ) );
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
    POINT pos_img_VS = { 0 };                     // VS艺术字图片位置
    POINT pos_img_tip = { 0 };                    // 提示信息文本图片位置
    POINT pos_img_1P = { 0 };                     // 1P 文本图片位置
    POINT pos_img_2P = { 0 };                     // 2P 文本图片位置
    POINT pos_img_1P_desc = { 0 };                // 1P 键位描述图片位置
    POINT pos_img_2P_desc = { 0 };                // 2P 键位描述图片位置
    POINT pos_img_1P_name = { 0 };                // 1P 角色姓名文本位置
    POINT pos_img_2P_name = { 0 };                // 2P 角色姓名文本位置
    POINT pos_animation_1P = { 0 };               // 1P 角色动画位置
    POINT pos_animation_2P = { 0 };               // 2P 角色动画位置
    POINT pos_img_1P_gravestone = { 0 };          // 1P 墓碑图片位置
    POINT pos_img_2P_gravestone = { 0 };          // 2P 墓碑图片位置
    POINT pos_1P_selector_btn_left = { 0 };       // 1P 向左切换按钮位置
    POINT pos_1P_selector_btn_right = { 0 };      // 1P 向右切换按钮位置
    POINT pos_2P_selector_btn_left = { 0 };       // 2P 向左切换按钮位置
    POINT pos_2P_selector_btn_right = { 0 };      // 2P 向右切换按钮位置
private:
    Animation animation_peashooter;               //豌豆射手动画
    Animation animation_sunflower;                //向日葵动画



};
