#ifndef MONSTERFIGHT_H
#define MONSTERFIGHT_H

#include "Player.h"
#include "Monster.h"
#include <memory>

class MonsterFight {
public:
    static std::unique_ptr<Monster> CreateRandomMonster();
    static void StartFight(const Player& player); // const Player&로 수정
    static void MonsterTurn(Monster& monster, Player& player);
    static void PlayerTurn(Player& player, Monster& monster,bool& escaped);
    static void AttemptEscape(Player& player,Monster& monster,bool& escaped);
};

#endif // MONSTERFIGHT_H
