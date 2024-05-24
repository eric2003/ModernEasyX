#include <iostream>
#include <string>
#include <graphics.h>
#include "Player.h"
#include "Enemy.h"

//teyvat-survivors

IMAGE img_background;

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

int main()
{
    initgraph(WINDOW_WIDTH,WINDOW_HEIGHT);
    bool running = true;
    
    ExMessage msg;

	loadimage(&img_background,_T("../../img/background.png"));

    Player player;
    std::vector<Enemy *> enemy_list;
    std::vector<Bullet> bullet_list( 3 );
    
    BeginBatchDraw();
    while( running ){
        DWORD start_time = GetTickCount();
        while( peekmessage(&msg) ){
            player.ProcessEvent( msg );
        }

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
                    enemy->Hurt();
                }
            }
        }

        for ( std::size_t i = 0; i < enemy_list.size(); ++ i ) {
            Enemy * enemy = enemy_list[ i ];
            if ( !enemy->CheckAlive() ) {
                std::swap(enemy_list[ i ],enemy_list.back());
                enemy_list.pop_back();
                delete enemy;
                i --;
            }
        }

        cleardevice();
	
		putimage(0,0,&img_background);
        player.Draw( 1000 / 144 );
        for ( Enemy *enemy: enemy_list ) {
            enemy->Draw( 1000 / 144 );
        }

        for ( const Bullet &bullet: bullet_list ) {
            bullet.Draw();
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
