#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Player; // Forward declaration of Player class

class Monster {
public:
    virtual ~Monster() = default;

    virtual std::string GetName() const = 0;
    virtual int GetAttack() const = 0;
    virtual int GetHealth() const = 0;
    virtual void TakeDamage(int amount) = 0;
    virtual void Attack(const Player& player) const = 0;
    virtual bool IsDefeated() const = 0;
    virtual int GetDefense() const = 0; // Added virtual method for defense
};

#endif // MONSTER_H
