#include "Slime.h"
#include "Player.h"
#include <iostream>
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds

Slime::Slime()
    : Monster("Slime", 30, 5, 2) // 슬라임 이름, 기본 체력, 공격력, 방어력
{}

std::string Slime::GetName() const {
    return "Slime";
}

int Slime::GetAttack() const {
    return attackPower;
}

int Slime::GetHealth() const {
    return health;
}

void Slime::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Slime::Attack(Player& player) {
    std::cout << "Slime이(가) " << player.GetName() << "을(를) 공격합니다!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    player.TakeDamage(GetAttack()); // 플레이어의 TakeDamage 메서드 호출
}

bool Slime::IsDefeated() const {
    return health <= 0;
}

int Slime::GetDefense() const {
    return defensePower;
}
