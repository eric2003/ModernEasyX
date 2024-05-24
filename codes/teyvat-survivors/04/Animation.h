#pragma once
#include <string>
#include <graphics.h>
#include <vector>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

class Atlas;

extern Atlas * atlas_player_left;
extern Atlas * atlas_player_right;
extern Atlas * atlas_enemy_left;
extern Atlas * atlas_enemy_right;

inline void putimage_alpha( int x, int y, IMAGE * img ) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend( GetImageHDC( NULL ), x, y, w, h,
        GetImageHDC( img ), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
    );
}

class Atlas {
public:
    Atlas(LPCTSTR path, int num) {
        TCHAR path_file[256];
        for ( std::size_t i = 0; i < num; ++ i ) {
            _stprintf_s( path_file, path, i );
            IMAGE * frame = new IMAGE();
            loadimage( frame, path_file );
            this->frame_list.push_back( frame );
        }
    }
    ~Atlas() {
        for ( std::size_t i = 0; i < this->frame_list.size(); ++ i ) {
            delete this->frame_list[ i ];
        }
    }
public:
    std::vector<IMAGE *> frame_list;
};


class Animation
{
public:
    Animation(Atlas * atlas, int interval) {
        this->anim_atlas = atlas;
        this->interval_ms = interval;
    };

    ~Animation() = default;
    void Play( int x, int y, int delta) {
        this->timer += delta;
        if ( this->timer >= this->interval_ms ) {
            this->idx_frame = ( this->idx_frame + 1 ) % this->anim_atlas->frame_list.size();
            this->timer = 0;
        }
        putimage_alpha( x, y, this->anim_atlas->frame_list[ this->idx_frame ] );
    }
private:
    int timer = 0;
    int idx_frame = 0;
    int interval_ms = 0;
private:
    Atlas * anim_atlas;
};

