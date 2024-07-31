#ifndef __GAME_H__
#define __GAME_H__

#include "InGame.h"
#include <string>

class Game {
private:
    InGame* ingame; // 포인터로 수정

public:
    Game(InGame* ingame) : ingame(ingame) {}
    void gamemenu() const;
    void game() const;
    
};

#endif
