#ifndef INGAME_H
#define INGAME_H

#include "Player.h"
#include <string>

class InGame {
public:
    enum ClassType { WARRIOR, MAGE, ROGUE };

    InGame(ClassType type, const std::string& name);
    InGame(const Player& player);

    std::string GetCharacterName() const;
    std::string GetClassName() const;
    int GetCurrentFloor() const;
    void SetCurrentFloor(int floor);
    void SetPlayerCurrentFloor();
    void PlayerInfo() const;

    void WarriorGuide() const;
    void MageGuide() const;
    void RogueGuide() const;

    const Player& GetPlayer() const;

    void SetPlayerAttack(int attack);
    void SetPlayerDefense(int defense);
    void SetPlayerMagicAttack(int magicAttack);
    void SetPlayerAgility(int agility);

    int GetPlayerAttack() const;
    int GetPlayerDefense() const;
    int GetPlayerMagicAttack() const;
    int GetPlayerAgility() const;

    void GainPlayerExperience(int amount);
    void LevelUpPlayer();

private:
    ClassType type;
    std::string name;
    Player player;
    int currentFloor;
};

#endif // INGAME_H
