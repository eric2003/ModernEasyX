#include <iostream>
#include <string>
#include <graphics.h>
#include "Player.h"
#include "Enemy.h"
#include "Button.h"

//teyvat-survivors

IMAGE img_background;
IMAGE img_menu;

Atlas * atlas_player_left=0;
Atlas * atlas_player_right=0;
Atlas * atlas_enemy_left=0;
Atlas * atlas_enemy_right=0;
bool is_game_started = false;
bool running = true;


//Spawn new enemies
void TryGenerateEnemy(std::vector<Enemy*>&enemy_list) {
    const int INTERVAL = 100;
    static int counter = 0;
    if ( ( ++ counter ) %  INTERVAL == 0 ) {
        enemy_list.push_back( new Enemy() );
    }
}

//Update bullet position
void UpdateBullets(std::vector<Bullet> &bullet_list, const Player &player) {
    const double RADIAL_SPEED = 0.0045;
    const double TANGENT_SPEED = 0.0055;
    double radian_interval = 2 * 3.14159 / bullet_list.size();
    POINT player_position = player.GetPosition();
    double radius = 100 + 25 * sin( GetTickCount() * RADIAL_SPEED );
    int FRAME_WIDTH = player.GetFrameWidth();
    int FRAME_HEIGHT = player.GetFrameHeight();

    for ( std::size_t i = 0; i < bullet_list.size(); ++ i ) {
        double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;
        bullet_list[ i ].position.x = player_position.x + FRAME_WIDTH / 2 + static_cast<int>( radius * sin( radian ) );
        bullet_list[ i ].position.y = player_position.y + FRAME_HEIGHT / 2 + static_cast<int>( radius * cos( radian ) );
    }
}

void DrawPlayerScore(int score){
    static TCHAR text[64];
    _stprintf_s( text, _T("current player's score:%d"), score );
    setbkmode( TRANSPARENT );
    settextcolor( RGB( 255, 85, 185 ) );
    outtextxy( 10, 10, text );
}

int main()
{
    initgraph(WINDOW_WIDTH,WINDOW_HEIGHT);
    atlas_player_left  = new Atlas( _T("../../img/player_left_%d.png"), 6 );
    atlas_player_right = new Atlas( _T("../../img/player_right_%d.png"), 6 );
    atlas_enemy_left = new Atlas( _T("../../img/enemy_left_%d.png"), 6 );
    atlas_enemy_right = new Atlas( _T("../../img/enemy_right_%d.png"), 6 );

    mciSendString( _T( "open ../../mus/bgm.mp3 alias bgm" ), NULL, 0, NULL );
    mciSendString( _T( "open ../../mus/hit.wav alias hit" ), NULL, 0, NULL );

    mciSendString( _T( "play bgm repeat from 0" ), NULL, 0, NULL );

    int score = 0;
    
    ExMessage msg;
    RECT region_btn_start_game, region_btn_quit_game;
    region_btn_start_game.left = ( WINDOW_WIDTH - BUTTON_WIDTH ) / 2;
    region_btn_start_game.right = region_btn_start_game.left + BUTTON_WIDTH;
    region_btn_start_game.top = 430;
    region_btn_start_game.bottom = region_btn_start_game.top + BUTTON_HEIGHT;

    region_btn_quit_game.left = ( WINDOW_WIDTH - BUTTON_WIDTH ) / 2;
    region_btn_quit_game.right = region_btn_quit_game.left + BUTTON_WIDTH;
    region_btn_quit_game.top = 550;
    region_btn_quit_game.bottom = region_btn_quit_game.top + BUTTON_HEIGHT;

    StartGameButton btn_start_game = StartGameButton(region_btn_start_game,
        _T("../../img/ui_start_idle.png"),
        _T("../../img/ui_start_hovered.png"),
        _T("../../img/ui_start_pushed.png")
        );

    QuitGameButton btn_quit_game = QuitGameButton(region_btn_quit_game,
        _T("../../img/ui_quit_idle.png"),
        _T("../../img/ui_quit_hovered.png"),
        _T("../../img/ui_quit_pushed.png")
    );


    loadimage(&img_menu,_T("../../img/menu.png"));
    loadimage(&img_background,_T("../../img/background.png"));

    Player player;
    std::vector<Enemy *> enemy_list;
    std::vector<Bullet> bullet_list( 3 );

   
    BeginBatchDraw();
    while( running ){
        DWORD start_time = GetTickCount();
        while( peekmessage(&msg) ){
            if ( is_game_started ) {
                player.ProcessEvent( msg );
            }
            else {
                btn_start_game.ProcessEvent( msg );
                btn_quit_game.ProcessEvent( msg );
            }
            
        }

        if ( is_game_started ) {
            player.Move();
            UpdateBullets( bullet_list, player );

            TryGenerateEnemy( enemy_list );
            for ( Enemy *enemy: enemy_list ) {
                enemy->Move( player );
            }

            //Detecting collisions between enemies and players
            for ( Enemy *enemy: enemy_list ) {
                if ( enemy->CheckPlayerCollision(player) ) {
                    MessageBox(GetHWnd(),_T("Type \"1\" to watch the defeat CG"), _T("Game Over"), MB_OK);
                    running = false;
                    break;
                }
            }

            //Detecting collisions between bullets and enemies
            for ( Enemy *enemy: enemy_list ) {
                for ( const Bullet& bullet : bullet_list ) {
                    if ( enemy->CheckBulletCollision( bullet ) ) {
                        mciSendString( _T( "play hit from 0" ), NULL, 0, NULL );
                        enemy->Hurt();
                        score ++;
                    }
                }
            }

            //Removed enemies whose health reached zero
            for ( std::size_t i = 0; i < enemy_list.size(); ++ i ) {
                Enemy * enemy = enemy_list[ i ];
                if ( !enemy->CheckAlive() ) {
                    std::swap(enemy_list[ i ],enemy_list.back());
                    enemy_list.pop_back();
                    delete enemy;
                    i --;
                }
            }
        }


        cleardevice();
        if ( is_game_started ) {
            putimage(0,0,&img_background);
            player.Draw( 1000 / 144 );
            for ( Enemy *enemy: enemy_list ) {
                enemy->Draw( 1000 / 144 );
            }

            for ( const Bullet &bullet: bullet_list ) {
                bullet.Draw();
            }

            DrawPlayerScore( score );
        }
        else {
            putimage(0,0,&img_menu);
            btn_start_game.Draw();
            btn_quit_game.Draw();
        }
    
        
        FlushBatchDraw();
        
        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;
        if ( delta_time < 1000 / 144 ){
            Sleep(1000/144 - delta_time);
        }
    }
    
    EndBatchDraw();
    return 0;
}
