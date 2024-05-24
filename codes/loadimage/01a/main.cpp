#include <iostream>
#include <filesystem>
#include <graphics.h>

int main()
{
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::cout << "Current Path: " << currentPath << std::endl;

	std::filesystem::path targetPath("d:/work/easyx_work/ModernEasyX/codes/loadimage/01a/background.png");
	std::filesystem::path relativePath = std::filesystem::relative(targetPath, currentPath);
	std::cout << relativePath << std::endl;

	initgraph(1280,720);  
	IMAGE img_background;
	loadimage(&img_background,_T("../background.png"));
	putimage(0,0,&img_background);
	std::cin.get();
    
    return 0;
}
