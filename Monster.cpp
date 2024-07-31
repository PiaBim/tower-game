#include "Monster.h"
#include "Player.h"
#include <iostream>


Monster::Monster(const std::string& name, int health, int attackPower, int defensePower)
    : name(name), health(health), attackPower(attackPower), defensePower(defensePower) {}

std::string Monster::GetName() const {
    return name;
}

int Monster::GetHealth() const {
    return health;
}

bool Monster::IsDefeated() const {
    return health <= 0;
}

void Monster::Attack(Player& player) {
    std::cout << name << "이(가) " << player.GetName() << "을(를) 공격합니다!" << std::endl;
    player.TakeDamage(GetAttack()); // 공격력으로 피해를 입힘
}

void Monster::TakeDamage(int damage) {
    int effectiveDamage = damage - GetDefense(); // 방어력 고려
    if (effectiveDamage < 0) effectiveDamage = 0; // 피해량이 음수가 되지 않도록
    health -= effectiveDamage;
    if (health < 0) health = 0;
    std::cout << name << "이(가) " << effectiveDamage << "의 피해를 입었습니다! 남은 체력: " << health << std::endl;
}

int Monster::GetAttack() const {
    return attackPower;
}

int Monster::GetDefense() const {
    return defensePower;
}
