#pragma once
#include <graphics.h>
#include <vector>

class Atlas
{
public:
    Atlas() = default;
    ~Atlas() = default;

    void load_from_file(LPCTSTR path_template, int num) {
        this->img_list.clear();
        this->img_list.resize( num );

        TCHAR path_file[ 256 ];
        for ( std::size_t i = 0; i < num; ++ i ) {
            _stprintf_s( path_file, path_template, i + 1 );
            loadimage( &this->img_list[ i ], path_file );
        }
    }

    void clear() {
        this->img_list.clear();
    }

    int get_size() {
        return static_cast<int>( this->img_list.size() );
    }

    IMAGE * get_image( int idx ) {
        if ( idx < 0 || idx >= this->img_list.size() ) {
            return nullptr;
        }
        return & this->img_list[ idx ];
    }

    void add_image( const IMAGE & img ) {
        this->img_list.push_back( img );
    }
private:
    std::vector<IMAGE> img_list;
};
