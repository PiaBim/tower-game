#include "Goblin.h"
#include "Player.h"
#include <iostream>
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds

Goblin::Goblin()
    : Monster("Goblin", 40, 10, 5) // 고블린 이름, 기본 체력, 공격력, 방어력
{}

std::string Goblin::GetName() const {
    return "Goblin";
}

int Goblin::GetAttack() const {
    return attackPower;
}

int Goblin::GetHealth() const {
    return health;
}

void Goblin::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Goblin::Attack(Player& player) {
    std::cout << "Goblin이(가) " << player.GetName() << "을(를) 공격합니다!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    player.TakeDamage(GetAttack()); // 플레이어의 TakeDamage 메서드 호출
}

bool Goblin::IsDefeated() const {
    return health <= 0;
}

int Goblin::GetDefense() const {
    return defensePower;
}
