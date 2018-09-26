// Game.h 

#ifndef _GAME_H
#define _GAME_H 

struct Ball {
    int x;
    int y;
    bool isAlive;
};

struct Hippo {
    int x;
    int y;
    int freq;
    int xDir;
    int yDir;
};

class HungryHippo {
public:
    HungryHippo();
    ~HungryHippo();
    void showField(bool isEating);
    void moveBall(Ball* ball);
    void moveBalls();
    void hipposEat();
    bool isBallAt(int x, int y);
    bool isInField(int x, int y);
    void play();
    void updateView(bool isEating);
    int getN();
    int getFreq();
    int getNumBalls();
    bool toEnd(); 

//private:
    int N;
    int numBalls;
    char** field;
    int freq;
    Ball* balls;
    Hippo hippos[4];

};

#endif
