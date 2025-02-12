#ifndef GOBLINE_H
#define GOBLINE_H

#include "Monster.h"
#include <string>

class Player; // Forward declaration of Player class

class Goblin : public Monster {
public:
    Goblin();

    std::string GetName() const override;
    int GetAttack() const override;
    int GetHealth() const override;
    void TakeDamage(int amount) override;
    void Attack(Player& player) override;
    bool IsDefeated() const override;
    int GetDefense() const override;
    int GetExperienceReward() const override { return 7; }
};

#endif 