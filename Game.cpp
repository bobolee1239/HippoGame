// Game.cpp

#include <iostream>
#include <stdlib.h>
#include "Game.h"
#include <time.h>
#include <unistd.h>

// constructor
HungryHippo::HungryHippo() {
    // configure para
    int trials = 0;
    do {
        if(trials > 0) std::cout << "Improper N!! (N > 3 and a odd number), plz try again!" << std::endl;
        std::cout << "Field size N?  >";
        std::cin >> N;
        trials += 1;
    } while ((N % 2 == 0) || (N < 4));
    
    trials = 0;
    do { 
        if(trials > 0) std::cout << "Improper # of balls! (field is " << N << " x " << N << " )" << std::endl;
        std::cout << "# of balls on field?  >";
        std::cin >> numBalls;
        trials += 1;
    } while (numBalls > N * N);
    
    std::cout << "Period of hippo eat?  >";
    std::cin >> freq;

    // New Hippoes
    hippos[0].x = N/2 + 1;
    hippos[0].y = 0;
    hippos[0].xDir = 0;
    hippos[0].yDir = 1;

    hippos[1].x = N + 1;
    hippos[1].y = N/2 + 1;
    hippos[1].xDir = -1;
    hippos[1].yDir = 0;

    hippos[2].x = N/2 + 1;
    hippos[2].y = N + 1;
    hippos[2].xDir = 0;
    hippos[2].yDir = -1;

    hippos[3].x = 0;
    hippos[3].y = N/2 + 1;
    hippos[3].xDir = 1;
    hippos[3].yDir = 0;

    for(int i=0; i<4; i++) 
        hippos[i].freq = freq;
    // New Balls
    balls = new Ball[numBalls];
    int bias = N*N / numBalls;
    int num = 0;
    for (int i=0; i<numBalls; i++){
        balls[i].x = num%N + 1;
        balls[i].y = num/N + 1;
        balls[i].isAlive = true;
        num += bias;
    }

    // New & Init Field as 2D char array
    field = new char*[N+2];
    for(int i=0; i<N+2; i++)  field[i] = new char[N+2];
    for (int i=0; i<N+2; i++){
        for(int j=0; j<N+2; j++)
            field[i][j] = ' ';
    }
}

// Deconstructor
HungryHippo::~HungryHippo(){
    delete[] balls;
    for(int i=0; i<N+2; i++)    delete[] field[i];
    delete[] field;
}

int HungryHippo::getN() { return N; }
int HungryHippo::getFreq() { return freq;}
int HungryHippo::getNumBalls() {return numBalls;}

void HungryHippo::showField(bool isEating){
    // update view 
    system("clear");
    updateView(isEating);
    
    std::cout << "\n\n\n";
    // print out field
    for(int i=0; i<N+2; i++){
        std::cout << '\t';
        for(int j=0; j<N+2; j++){
            std::cout << " " << field[i][j];
        }
        std::cout << std::endl;
    }
}

bool HungryHippo::isBallAt(int x, int y){
    // Complexity: O(n) 
    bool ballExist = false;
    for(int i=0; i<numBalls; i++){
        ballExist = (balls[i].x == x && balls[i].y == y);
        //std::cout << "#" << i << ": "<<  x << ',' << y << "\t" << balls[i].x << ',' << balls[i].y << std::endl;
        if(ballExist) break;
    }
    return ballExist;
}

bool HungryHippo::isInField(int x, int y){
    return (x > 0 && x < N+1) && (y > 0 && y < N+1);
}

void HungryHippo::moveBall(Ball* ball){
    int xmove = 0;
    int ymove = 0;
    
    do {
        xmove = rand() % 3 - 1; // -1, 0, 1 
        ymove = rand() % 3 - 1; // -1, 0, 1
        if(xmove == 0 && ymove == 0) break;
        //std::cout << xmove << ',' << ymove << std::endl;
        //std::cout << ball->x + xmove << ", " << ball->y + ymove<< ": " 
        //          << isBallAt(ball->x + xmove, ball->y + ymove) << ", "<< ~isInField(ball->x + xmove, ball->y + ymove)<< std::endl;
    } while(isBallAt(ball->x + xmove, ball->y + ymove) || (!isInField(ball->x + xmove, ball->y + ymove)));

    ball->x += xmove;
    ball->y += ymove;
}

void HungryHippo::moveBalls(){
    for(int i=0; i<numBalls; i++){
        moveBall(&balls[i]);
    }
}

void HungryHippo::hipposEat(){
    for(int i=0; i<4; i++){
        for(int j=0; j<2; j++){
            for(int k=0; k<numBalls; k++){
                if(!balls[k].isAlive) 
                    continue;
                else if((hippos[i].x + hippos[i].xDir*(j+1)) == balls[k].x && (hippos[i].y + hippos[i].yDir*(j+1)) == balls[k].y)    
                    balls[k].isAlive = false;
            }
        }
    }
}

void HungryHippo::updateView(bool isEating){
    // reset to space 
    for(int i=0; i<N+2; i++)
        for (int j=0; j<N+2; j++)
            field[i][j] = (isInField(i, j))?' ':'=';
   
        
    // update ball position 
    for(int i=0; i<numBalls; i++){
        if(!balls[i].isAlive) continue;
        field[balls[i].x][balls[i].y] = '*';
    }
    // update hippo position && and range of hippo
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            //std::cout << "#" << i << ": " << hippos[i].x + j*(hippos[i].xDir) << ", " << hippos[i].y + j*(hippos[i].yDir) << std::endl;
            field[hippos[i].x + j*hippos[i].xDir][hippos[i].y + j*hippos[i].yDir] = 'X';
            if(!isEating) break;
             
        }    
    }
}

bool HungryHippo::toEnd(){
    bool con = false;
    for(int i=0; i<numBalls; i++){
        con = con || balls[i].isAlive; 
    }
    return !con;
}

void HungryHippo::play(){
    int count = 0;
//    std::cout << "/////////////////////////////////\n";
//    std::cout << "////////// GAME START //////////" << std::endl;
//    std::cout << "/////////////////////////////////\n";
    showField(false);
    while(true){
        if(toEnd()) break;
        
        moveBalls();
        showField(false);

        if(count == freq){
            showField(true);
            hipposEat();
            count = 0;
        }

        count += 1;
        usleep(1000000);
    }
    std::cout << "\n\n";
    std::cout << "  ///////////////////////////////////\n";
    std::cout << "  ////////// GAME OVER !! //////////" << std::endl;
    std::cout << "  ///////////////////////////////////\n";

}
