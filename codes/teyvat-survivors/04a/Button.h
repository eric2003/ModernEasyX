#pragma once
#include <graphics.h>

class Button
{
public:
    Button( RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed ) {
        this->region = rect;
        loadimage( &img_idle, path_img_idle );
        loadimage( &img_hovered, path_img_hovered );
        loadimage( &img_pushed, path_img_pushed );
    }
    ~Button() {
        ;
    }
protected:
    virtual void OnClick() = 0;
public:
    void Draw() {
        switch ( status )
        {
        case Button::Status::Idle:
            putimage( region.left, region.top, &img_idle );
            break;
        case Button::Status::Hovered:
            putimage( region.left, region.top, &img_hovered );
            break;
        case Button::Status::Pushed:
            putimage( region.left, region.top, &img_pushed );
            break;
        default:
            break;
        };
    }

    void ProcessEvent( const ExMessage & msg ) {
        switch ( msg.message )
        {
        case WM_MOUSEMOVE:
            if ( this->status == Status::Idle && this->CheckCursorHit(msg.x,msg.y) ) {
                this->status = Status::Hovered;
            }
            else if ( this->status == Status::Hovered && !this->CheckCursorHit(msg.x,msg.y) ) {
                this->status = Status::Idle;
            }
            break;
        case WM_LBUTTONDOWN:
            if ( this->CheckCursorHit( msg.x, msg.y ) ) {
                this->status = Status::Pushed;
            }
            break;
        case WM_LBUTTONUP:
            if ( this->status == Status::Pushed ) {
                this->OnClick();
            }
            break;
        default:
            break;
        }
    }
private:
    //Detecting Mouse Clicks
    bool CheckCursorHit( int x, int y ) {
        return x >= this->region.left && x <= this->region.right &&
               y >= this->region.top && y <= this->region.bottom;
    }
private:
    enum class Status {
        Idle = 0,
        Hovered,
        Pushed
    };
private:
    RECT region;
    IMAGE img_idle;
    IMAGE img_hovered;
    IMAGE img_pushed;
    Status status = Status::Idle;
};

extern bool is_game_started;
extern bool running;

class StartGameButton : public Button {
public:
    StartGameButton( RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed )
        : Button(rect,path_img_idle,path_img_hovered,path_img_pushed)
    {
    }
protected:
    void OnClick()
    {
        is_game_started = true;
    }
};

class QuitGameButton : public Button {
public:
    QuitGameButton( RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed )
        : Button(rect,path_img_idle,path_img_hovered,path_img_pushed)
    {
    }
protected:
    void OnClick()
    {
        running = false;
    }
};

