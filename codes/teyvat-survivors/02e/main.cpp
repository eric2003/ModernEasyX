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

int main()
{
    initgraph(WINDOW_WIDTH,WINDOW_HEIGHT);
    bool running = true;
    
    ExMessage msg;

	loadimage(&img_background,_T("../../img/background.png"));

    Player player;
    std::vector<Enemy *> enemy_list;
    
    BeginBatchDraw();
    while( running ){
        DWORD start_time = GetTickCount();
        while( peekmessage(&msg) ){
            player.ProcessEvent( msg );
        }

        player.Move();
        TryGenerateEnemy( enemy_list );
        for ( Enemy *enemy: enemy_list ) {
            enemy->Move( player );
        }

        //Detecting collisions between enemies and players
        for ( Enemy *enemy: enemy_list ) {
            enemy->Move( player );
            if ( enemy->CheckPlayerCollision(player) ) {
                MessageBox(GetHWnd(),_T("Type \"1\" to watch the defeat CG"), _T("Game Over"), MB_OK);
                running = false;
                break;
            }
        }

        cleardevice();
	
		putimage(0,0,&img_background);
        player.Draw( 1000 / 144 );
        for ( Enemy *enemy: enemy_list ) {
            enemy->Draw( 1000 / 144 );
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
