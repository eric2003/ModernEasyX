#pragma once
#include <graphics.h>
#include "Camera.h"

inline void putimage_alpha( const Camera & camera, int dst_x, int dst_y, IMAGE * img ) {
    int w = img->getwidth();
    int h = img->getheight();
    const Vector2 & pos_camera = camera.get_position();
    int x = static_cast<int>( dst_x - pos_camera.x );
    int y = static_cast<int>( dst_y - pos_camera.y );
    AlphaBlend( GetImageHDC( NULL ), x, y, w, h,
        GetImageHDC( img ), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
    );
}

inline void flip_image( IMAGE * src, IMAGE * dst ) {
    int w = src->getwidth();
    int h = src->getheight();
    Resize( dst, w, h );

    DWORD * src_buffer = GetImageBuffer( src );
    DWORD * dst_buffer = GetImageBuffer( dst );

    for ( int y = 0; y < h; ++ y ) {
        for ( int x = 0; x < w; ++ x ) {
            int idx_src = y * w + x;
            int idx_dst = y * w + ( w - x - 1 );
            dst_buffer[ idx_dst ] = src_buffer[ idx_src ];
        }
    }
}

