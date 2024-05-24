#pragma once
#include <graphics.h>
#include <functional>

class Timer {
public:
    Timer() = default;
    ~Timer() = default;
public:
    void restart() {
        this->pass_time = 0;
        this->shotted = false;
    }

    void set_wait_time( int val ) {
        this->wait_time = val;
    }

    void set_one_shot( bool flag ) {
        this->one_shot = flag;
    }

    void set_callback(std::function<void()> callback) {
        this->callback = callback;
    }

    void pause() {
        this->paused = true;
    }

    void resume() {
        this->paused = false;
    }

    void on_update( int delta ) {
        if ( this->paused ) {
            return;
        }
        this->pass_time += delta;
        if ( this->pass_time >= this->wait_time ) {
            if ( ( !this->one_shot || (this->one_shot && !this->shotted) ) && this->callback ) {
                this->callback();
            }
            this->shotted = true;
            this->pass_time = 0;
        }
    }

private:
    int pass_time = 0;
    int wait_time = 0;
    bool paused = false;
    bool shotted = false;
    bool one_shot = false;
private:
    std::function<void()> callback;
};