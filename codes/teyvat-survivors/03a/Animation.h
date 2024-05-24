#pragma once
#include <string>
#include <graphics.h>
#include <vector>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

inline void putimage_alpha( int x, int y, IMAGE * img ) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend( GetImageHDC( NULL ), x, y, w, h,
        GetImageHDC( img ), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
    );
}

class IMAGE;
class Animation
{
public:
    Animation(LPCTSTR path, int num, int interval) {
        this->interval_ms = interval;
        TCHAR path_file[ 256 ];
        for ( std::size_t i = 0; i < num; ++ i ) {
            _stprintf_s( path_file, path, i );
            IMAGE * frame = new IMAGE();
            loadimage( frame, path_file );
            this->frame_list.push_back( frame );
        }
    };
    ~Animation() {
        for ( std::size_t i = 0; i < this->frame_list.size(); ++ i ) {
            delete this->frame_list[ i ];
        }
    };
    void Play( int x, int y, int delta) {
        this->timer += delta;
        if ( this->timer >= this->interval_ms ) {
            this->idx_frame = ( this->idx_frame + 1 ) % this->frame_list.size();
            this->timer = 0;
        }
        putimage_alpha( x, y, this->frame_list[ this->idx_frame ] );
    }
private:
    int timer = 0;
    int idx_frame = 0;
    int interval_ms = 0;
    std::vector<IMAGE *> frame_list;
};

