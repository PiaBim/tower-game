#include "InGame.h"
#include <iostream>

InGame::InGame(ClassType type, const std::string& name)
    : type(type), name(name), currentFloor(1) {
    // 클래스 타입에 따른 스탯 초기화
    switch (type) {
        case WARRIOR:
            player = Player(name, 150, 30, 100, 200, 1, 0, 1, "전사");
            player.SetAttack(4);
            player.SetDefense(4);
            player.SetMagicAttack(0);
            player.SetAgility(2);
            break;
        case MAGE:
            player = Player(name, 100, 100, 50, 200, 1, 0, 1, "마법사");
            player.SetAttack(1);
            player.SetDefense(2);
            player.SetMagicAttack(4);
            player.SetAgility(1);
            break;
        case ROGUE:
            player = Player(name, 120, 50, 80, 200, 1, 0, 1, "도적");
            player.SetAttack(3);
            player.SetDefense(2);
            player.SetMagicAttack(1);
            player.SetAgility(4);
            break;
        default:
            player = Player(name, 100, 50, 50, 200, 1, 0, 1, "알 수 없음");
            player.SetAttack(0);
            player.SetDefense(0);
            player.SetMagicAttack(0);
            player.SetAgility(0);
            break;
    }
}

InGame::InGame(const Player& player)
    : player(player), currentFloor(player.GetCurrentFloor()) {
    // Player 객체를 기반으로 InGame 초기화
    type = (player.GetClassName() == "전사") ? WARRIOR :
           (player.GetClassName() == "마법사") ? MAGE : ROGUE;
    name = player.getName();
}

std::string InGame::GetCharacterName() const {
    return name;
}

std::string InGame::GetClassName() const {
    switch (type) {
        case WARRIOR: return "전사";
        case MAGE: return "마법사";
        case ROGUE: return "도적";
        default: return "알 수 없음";
    }
}

int InGame::GetCurrentFloor() const {
    return currentFloor;
}

void InGame::SetCurrentFloor(int floor) {
    currentFloor = floor;
    SetPlayerCurrentFloor(); // 플레이어 객체의 현재 층수도 업데이트
}

void InGame::SetPlayerCurrentFloor() {
    player.SetCurrentFloor(currentFloor); // Player 객체의 층수를 업데이트
}

void InGame::PlayerInfo() const {
    player.PlayerInfo(); // Player 객체의 PlayerInfo 호출
}

void InGame::WarriorGuide() const {
    std::cout << "전사는 강력한 전투 능력과 높은 방어력을 가진 클래스입니다." << std::endl;
    std::cout << "전사 클래스를 하시겠습니까?" << std::endl;
}

void InGame::MageGuide() const {
    std::cout << "마법사는 강력한 마법 공격 능력을 가진 클래스입니다." << std::endl;
    std::cout << "마법사 클래스를 하시겠습니까?" << std::endl;
}

void InGame::RogueGuide() const {
    std::cout << "도적은 높은 민첩성과 적은 마법 공격 능력을 가진 클래스입니다." << std::endl;
    std::cout << "도적 클래스를 하시겠습니까?" << std::endl;
}

const Player& InGame::GetPlayer() const {
    return player; // Player 객체 반환
}

void InGame::SetPlayerAttack(int attack) {
    player.SetAttack(attack);
}

void InGame::SetPlayerDefense(int defense) {
    player.SetDefense(defense);
}

void InGame::SetPlayerMagicAttack(int magicAttack) {
    player.SetMagicAttack(magicAttack);
}

void InGame::SetPlayerAgility(int agility) {
    player.SetAgility(agility);
}

int InGame::GetPlayerAttack() const {
    return player.GetAttack();
}

int InGame::GetPlayerDefense() const {
    return player.GetDefense();
}

int InGame::GetPlayerMagicAttack() const {
    return player.GetMagicAttack();
}

int InGame::GetPlayerAgility() const {
    return player.GetAgility();
}

void InGame::GainPlayerExperience(int amount) {
    player.GainExperience(amount);
}

void InGame::LevelUpPlayer() {
    player.LevelUp();
}
