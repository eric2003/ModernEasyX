#pragma once
#include "Atlas.h"
#include "util.h"
#include <functional>
#include <iostream>
#include <graphics.h>

class Animation
{
public:
    Animation() = default;
    ~Animation() = default;

    void reset() {
        this->timer = 0;
        this->idx_frame = 0;
    }

    void set_atlas(Atlas * new_atlas) {
        this->reset();
        this->atlas = new_atlas;
    }

    void set_loop( bool flag ) {
        this->is_loop = flag;
    }

    void set_interval( int ms ) {
        this->interval = ms;
    }

    int get_idx_frame() {
        return this->idx_frame;
    }

    IMAGE * get_frame() {
        return this->atlas->get_image( this->idx_frame );
    }

    bool check_finished() {
        if ( this->is_loop ) return false;
        return ( this->idx_frame == this->atlas->get_size() - 1 );
    }

    void on_update(int delta) {
        this->timer += delta;
        if ( this->timer >= this->interval ) {
            this->timer = 0;
            this->idx_frame ++;
            if ( this->idx_frame >= this->atlas->get_size() ) {
                this->idx_frame = this->is_loop ? 0: this->atlas->get_size() - 1;
                if ( !this->is_loop && callback ) {
                    callback();
                }
            }
        }
    }

    void on_update_test(int delta) {
        this->idx_frame ++;
        this->idx_frame = this->idx_frame % this->atlas->get_size();
    }

    void on_update_test1(int delta) {
        this->idx_frame ++;
        if ( this->idx_frame >= this->atlas->get_size() ) {
            this->idx_frame = this->is_loop ? 0: this->atlas->get_size() - 1;
        }
    }

    void on_update_test2(int delta) {
        this->timer += delta;
        if ( this->timer >= this->interval ) {
            this->timer = 0;
            this->idx_frame ++;
            if ( this->idx_frame >= this->atlas->get_size() ) {
                this->idx_frame = this->is_loop ? 0 : this->atlas->get_size() - 1;
            }
        }
    }

    void on_update_test3(int delta) {
        std::cout << "on_update_test3 : delta = " << delta << "\n";
        this->timer += delta;
        if ( this->timer >= this->interval ) {
            this->timer = 0;
            this->idx_frame ++;
            if ( this->idx_frame >= this->atlas->get_size() ) {
                this->idx_frame = this->is_loop ? 0 : this->atlas->get_size() - 1;
            }
        }
    }


    void on_draw(int x, int y) const {
        putimage_alpha( x, y, this->atlas->get_image( this->idx_frame ) );
    }

    void on_draw_test(int x, int y, int frame) const {
        putimage_alpha( x, y, this->atlas->get_image( frame ) );
    }

    void on_draw_test1(int x, int y) const {
        putimage_alpha( x, y, this->atlas->get_image( this->idx_frame ) );
    }

    void set_callback(std::function<void()> callback) {
        this->callback = callback;
    }
private:
    int timer = 0;
    int interval = 0;
    int idx_frame = 0;
    bool is_loop = true;
    Atlas * atlas = nullptr;
    std::function<void()> callback;
};
