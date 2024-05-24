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

        pos_img_2P.x = ::getwidth() /2 + ( ::getwidth() /2  - img_2P.getwidth() ) / 2 + OFFSET_X;
        pos_img_2P.y = pos_img_1P.y;

        pos_img_1P_desc.x = ( ::getwidth() / 2 - img_1P_desc.getwidth() ) / 2 - OFFSET_X;
        pos_img_1P_desc.y = ::getheight() - 150;

        pos_img_2P_desc.x = ::getwidth() / 2 + ( ::getwidth() / 2 - img_2P_desc.getwidth() ) / 2 + OFFSET_X;
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

    void on_update( int delta )
    {
        this->animation_peashooter.on_update( delta );
        this->animation_sunflower.on_update( delta );

        this->selector_background_scroll_offset_x += 5;

        if ( this->selector_background_scroll_offset_x >= img_peashooter_selector_background_left.getwidth() )
        {
            this->selector_background_scroll_offset_x = 0;
        }
    }

    void on_draw( const Camera & camera )
    {
        IMAGE * img_p1_selector_background = nullptr;
        IMAGE * img_p2_selector_background = nullptr;
        switch ( player_type_2 )
        {
        case SelectorScene::PlayerType::Peashooter:
            img_p1_selector_background = &img_peashooter_selector_background_right;
            break;
        case SelectorScene::PlayerType::Sunflower:
            img_p1_selector_background = &img_sunflower_selector_background_right;
            break;
        case SelectorScene::PlayerType::Invalid:
            img_p1_selector_background = &img_peashooter_selector_background_right;
            break;
        default:
            break;
        }

        switch ( player_type_1 )
        {
        case SelectorScene::PlayerType::Peashooter:
            img_p2_selector_background = &img_peashooter_selector_background_left;
            break;
        case SelectorScene::PlayerType::Sunflower:
            img_p2_selector_background = &img_sunflower_selector_background_left;
            break;
        case SelectorScene::PlayerType::Invalid:
            img_p2_selector_background = &img_peashooter_selector_background_left;
            break;
        default:
            break;
        }
        ::putimage( 0, 0, &img_selector_background );

        ::putimage_alpha( camera, this->selector_background_scroll_offset_x - img_p1_selector_background->getwidth(),
                                  0, img_p1_selector_background );
        ::putimage_alpha( camera, this->selector_background_scroll_offset_x, 0,
            img_p1_selector_background->getwidth() - this->selector_background_scroll_offset_x, 0,
            img_p1_selector_background, 0, 0 );

        ::putimage_alpha( camera, getwidth() - img_p2_selector_background->getwidth(), 0,
            img_p2_selector_background->getwidth() - this->selector_background_scroll_offset_x, 0,
            img_p2_selector_background, this->selector_background_scroll_offset_x, 0 );

        ::putimage_alpha( camera, getwidth() - this->selector_background_scroll_offset_x, 0, img_p2_selector_background );

        ::putimage_alpha( camera, pos_img_VS.x, pos_img_VS.y, &img_VS );

        ::putimage_alpha( camera, pos_img_1P.x, pos_img_1P.y, &img_1P );
        ::putimage_alpha( camera, pos_img_2P.x, pos_img_2P.y, &img_2P );

        ::putimage_alpha( camera, pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right );
        ::putimage_alpha( camera, pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left );

        switch ( player_type_1 )
        {
        case SelectorScene::PlayerType::Peashooter:
            img_p1_selector_background = &img_peashooter_selector_background_right;
            this->animation_peashooter.on_draw( camera, pos_animation_1P.x, pos_animation_1P.y );
            pos_img_1P_name.x = pos_img_1P_gravestone.x + ( img_gravestone_right.getwidth() - textwidth(str_peashooter_name) ) / 2;
            outtextxy_shaded( pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name );
            break;
        case SelectorScene::PlayerType::Sunflower:
            img_p1_selector_background = &img_sunflower_selector_background_right;
            this->animation_sunflower.on_draw( camera, pos_animation_1P.x, pos_animation_1P.y );
            pos_img_1P_name.x = pos_img_1P_gravestone.x + ( img_gravestone_right.getwidth() - textwidth(str_sunflower_name) ) / 2;
            outtextxy_shaded( pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name );
            break;
        case SelectorScene::PlayerType::Invalid:
            img_p1_selector_background = &img_peashooter_selector_background_right;
            break;
        default:
            break;
        }

        switch ( player_type_2 )
        {
        case SelectorScene::PlayerType::Peashooter:
            img_p2_selector_background = &img_peashooter_selector_background_left;
            this->animation_peashooter.on_draw( camera, pos_animation_2P.x, pos_animation_2P.y );
            pos_img_2P_name.x = pos_img_2P_gravestone.x + ( img_gravestone_left.getwidth() - textwidth(str_peashooter_name) ) / 2;
            outtextxy_shaded( pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name );
            break;
        case SelectorScene::PlayerType::Sunflower:
            img_p2_selector_background = &img_sunflower_selector_background_left;
            this->animation_sunflower.on_draw( camera, pos_animation_2P.x, pos_animation_2P.y );
            pos_img_2P_name.x = pos_img_2P_gravestone.x + ( img_gravestone_left.getwidth() - textwidth(str_sunflower_name) ) / 2;
            outtextxy_shaded( pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name );
            break;
        case SelectorScene::PlayerType::Invalid:
            img_p2_selector_background = &img_peashooter_selector_background_left;
            break;
        default:
            break;
        }

        ::putimage_alpha( camera, this->pos_1P_selector_btn_left.x, this->pos_1P_selector_btn_left.y,
            this->is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left );
        ::putimage_alpha( camera, this->pos_1P_selector_btn_right.x, this->pos_1P_selector_btn_right.y,
            this->is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right );
        ::putimage_alpha( camera, this->pos_2P_selector_btn_left.x, this->pos_2P_selector_btn_left.y,
            this->is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left );
        ::putimage_alpha( camera, this->pos_2P_selector_btn_right.x, this->pos_2P_selector_btn_right.y,
            this->is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right );

        ::putimage_alpha( camera, pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc );
        ::putimage_alpha( camera, pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc );

        ::putimage_alpha( camera, pos_img_tip.x, pos_img_tip.y, &img_selector_tip );

    }

    void on_input( const ExMessage & msg )
    {
        switch ( msg.message )
        {
        case WM_KEYDOWN:
            switch ( msg.vkcode )
            {
                //'A'
            case 0x41:
                this->is_btn_1P_left_down = true;
                break;
                //'D'
            case 0x44:
                this->is_btn_1P_right_down = true;
                break;
                //'<-'
            case VK_LEFT:
                this->is_btn_2P_left_down = true;
                break;
                //'->'
            case VK_RIGHT:
                this->is_btn_2P_right_down = true;
                break;
            }
            break;
        case WM_KEYUP:
            switch ( msg.vkcode )
            {
                //'A'
            case 0x41:
            {
                this->is_btn_1P_left_down = false;
                int invalid_value = static_cast<int>( SelectorScene::PlayerType::Invalid );
                int value = static_cast<int>( this->player_type_1 ) - 1;
                this->player_type_1 = static_cast<SelectorScene::PlayerType>( ( invalid_value + value ) % invalid_value );
                mciSendString( _T( "play ui_switch from 0" ), NULL, 0, NULL );
                break;
            }
            //'D'
            case 0x44:
            {
                this->is_btn_1P_right_down = false;
                int invalid_value = static_cast<int>( SelectorScene::PlayerType::Invalid );
                int value = static_cast<int>( this->player_type_1 ) + 1;
                this->player_type_1 = static_cast<SelectorScene::PlayerType>( ( invalid_value + value ) % invalid_value );
                mciSendString( _T( "play ui_switch from 0" ), NULL, 0, NULL );
                break;
            }
            //'<-'
            case VK_LEFT:
            {
                this->is_btn_2P_left_down = false;
                int invalid_value = static_cast<int>( SelectorScene::PlayerType::Invalid );
                int value = static_cast<int>( this->player_type_2 ) - 1;
                this->player_type_2 = static_cast<SelectorScene::PlayerType>( ( invalid_value + value ) % invalid_value );
                mciSendString( _T( "play ui_switch from 0" ), NULL, 0, NULL );
                break;
            }
            //'->'
            case VK_RIGHT:
            {
                this->is_btn_2P_right_down = false;
                int invalid_value = static_cast<int>( SelectorScene::PlayerType::Invalid );
                int value = static_cast<int>( this->player_type_2 ) + 1;
                this->player_type_2 = static_cast<SelectorScene::PlayerType>( ( invalid_value + value ) % invalid_value );
                mciSendString( _T( "play ui_switch from 0" ), NULL, 0, NULL );
                break;
            }
            }
            break;
        default:
            break;
        }
    }

    void on_exit()
    {
        std::cout << "Exit during game session" << std::endl;
    }
private:
    enum class PlayerType
    {
        Peashooter = 0,
        Sunflower,
        Invalid
    };
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

    SelectorScene::PlayerType player_type_1 = SelectorScene::PlayerType::Peashooter; // 1P 角色类型
    SelectorScene::PlayerType player_type_2 = SelectorScene::PlayerType::Sunflower;  // 2P 角色类型

    LPCTSTR str_peashooter_name = _T("豌豆射手");
    LPCTSTR str_sunflower_name = _T("向日葵");

    int selector_background_scroll_offset_x = 0;  //背景板滚动距离

    bool is_btn_1P_left_down = false;  // 1P 向左切换按钮是否按下
    bool is_btn_1P_right_down = false; // 1P 向右切换按钮是否按下
    bool is_btn_2P_left_down = false;  // 2P 向左切换按钮是否按下
    bool is_btn_2P_right_down = false; // 2P 向右切换按钮是否按下
private:
    void outtextxy_shaded( int x, int y, LPCTSTR str )
    {
        ::settextcolor( RGB( 45, 45, 45 ) );
        ::outtextxy( x + 3, y + 3, str );
        ::settextcolor( RGB( 255, 255, 255 ) );
        ::outtextxy( x, y, str );
    }
};
