#include <iostream>
#include <graphics.h>

int main()
{
    initgraph(600,480);
	int x = 300;
	int y = 300;
    while( true ){
		ExMessage msg;
		while( peekmessage(&msg) ){
			if( msg.message == WM_MOUSEMOVE ){
				x = msg.x;
				y = msg.y;
			}
		}
        solidcircle(x,y,100);
    }
    return 0;
}
