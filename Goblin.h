#ifndef GOBLIN_H
#define GOBLIN_H

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
    void Attack(const Player& player) const override;
    bool IsDefeated() const override;
    int GetDefense() const override; // Override for GetDefense

private:
    int health;
    const int attackPower;
    const int defensePower; // Added defense power
};

#endif // GOBLIN_H
