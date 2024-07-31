#ifndef SLIME_H
#define SLIME_H

#include "Monster.h"
#include <string>

class Player; // Forward declaration of Player class

class Slime : public Monster {
public:
    Slime();

    std::string GetName() const override;
    int GetAttack() const override;
    int GetHealth() const override;
    void TakeDamage(int amount) override;
    void Attack(Player& player) override;
    bool IsDefeated() const override;
    int GetDefense() const override;
    int GetExperienceReward() const override { return 5; }
};

#endif // SLIME_H
