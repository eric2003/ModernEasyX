#include <iostream>
#include <filesystem>
#include <graphics.h>

int main()
{
	initgraph(1280,720);  
	IMAGE img_background;
	loadimage(&img_background,_T("../background.png"));
	putimage(0,0,&img_background);
	std::cin.get();
    
    return 0;
}
