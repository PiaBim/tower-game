#include "Card.h"
#include <iostream>

SlashCard::SlashCard() : name("베기 카드"), cpCost(1) {}

void SlashCard::Use(Player& player, Monster& monster) {
    if (player.GetCP() >= GetCPCost()) {
        player.UseCP(GetCPCost()); // CP 소모
        int damage = player.GetAttack(); // 공격력 비례
        std::cout << "베기 카드 사용! 몬스터에 " << damage << "의 피해를 입혔습니다." << std::endl;
        monster.TakeDamage(damage);
    } else {
        std::cerr << "CP가 부족하여 카드 사용이 불가능합니다." << std::endl;
    }
}

const std::string& SlashCard::GetName() const {
    return name;
}

int SlashCard::GetCPCost() const {
    return cpCost;
}

ChargeCard::ChargeCard() : name("돌진 카드"), cpCost(1) {}

void ChargeCard::Use(Player& player, Monster& monster) {
    if (player.GetCP() >= GetCPCost()) {
        player.UseCP(GetCPCost()); // CP 소모
        int damage = player.GetAttack() + (player.GetAgility() / 2); // 공격력 + 민첩의 절반 비례
        std::cout << "돌진 카드 사용! 몬스터에 " << damage << "의 피해를 입혔습니다." << std::endl;
        monster.TakeDamage(damage);
    } else {
        std::cerr << "CP가 부족하여 카드 사용이 불가능합니다." << std::endl;
    }
}

const std::string& ChargeCard::GetName() const {
    return name;
}

int ChargeCard::GetCPCost() const {
    return cpCost;
}
