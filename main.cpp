// main.cpp

#include <iostream>
#include <cstdlib>
#include "Game.h"


int main()
{
    srand(time(NULL));
    
    HungryHippo myGame;
    
    myGame.play();
//    std::cout << std::endl << std::endl;
//    myGame.showField(false);
//    
//    for(int i=0; i<5; i++){    
//        if(i==4) system("clear");
//        myGame.moveBalls();
//
//        std::cout << std::endl << std::endl;
//        myGame.showField(false);
//    }
//
//    std::cout << myGame.toEnd() << std::endl;
//    
//    myGame.showField(true);
//    myGame.hipposEat();
//    myGame.showField(false);
//    myGame.moveBalls();
//    myGame.showField(false);
    

    return 0;
}
