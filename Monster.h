#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Player; // Forward declaration to avoid circular dependency

class Monster {
public:
    Monster(const std::string& name, int health, int attackPower, int defensePower = 0);

    virtual std::string GetName() const;
    virtual int GetHealth() const;
    virtual bool IsDefeated() const;
    virtual void Attack(Player& player);
    virtual int GetAttack() const = 0; 
    virtual void TakeDamage(int damage);
    virtual int GetDefense() const;

    virtual int GetExperienceReward() const = 0;

    virtual ~Monster() = default;

protected:
    std::string name;
    int health;
    int attackPower;
    int defensePower;
};

#endif // MONSTER_H
