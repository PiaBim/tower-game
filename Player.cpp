#include "Player.h"
#include "Item.h" // 실제 아이템 헤더를 포함해야 합니다.
#include <iostream>
#include <algorithm> // std::find

Player::Player() 
    : name(""), health(0), mana(0), stemina(0), Gold(0), level(1), exp(0), currentFloor(1), 
      className("알 수 없음"), atk(0), def(0), mtk(0), agi(0), startExp(200) {}

Player::Player(string playername, int playerhealth, int playermana, int playerstemina, 
               int playergold, int playerlevel, int playerexp, int floor, 
               string clsName)
    : name(playername), health(playerhealth), mana(playermana), stemina(playerstemina), 
      Gold(playergold), level(playerlevel), exp(playerexp), currentFloor(floor), 
      className(clsName), atk(0), def(0), mtk(0), agi(0), startExp(200) {}

Player::~Player() {
    for (auto item : inventory) {
        delete item;
    }
    inventory.clear(); // 인벤토리 클리어
}

// 나머지 메서드는 변동 없음

void Player::PlayerInfo() const {
    cout << "이름: " << name <<"|"<< "직업: " << className << endl;
    cout << "체력: " << health << "|" << "마나: " << mana << endl;
    cout << "스태미나: " << stemina << endl;
    cout << "공격력: " << atk <<"|" << "방어력: " << def << endl;
    cout << "마법력: " << mtk <<"|" << "민첩: " << agi << endl;  
    cout << "골드: " << Gold << endl;
    cout << "레벨: " << level << "|" << "남은 경험치: " << GetRemainingExpForLevelUp() << endl;
}

// 인벤토리에 아이템 추가 및 제거
void Player::AddItem(Item* item) {
    inventory.push_back(item);
}

void Player::RemoveItem(Item* item) {
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        delete *it;
        inventory.erase(it);
    }
}

// 능력치 설정 및 반환
void Player::SetAttack(int attack) {
    atk = attack;
}

void Player::SetDefense(int defense) {
    def = defense;
}

void Player::SetMagicAttack(int magicAttack) {
    mtk = magicAttack;
}

void Player::SetAgility(int agility) {
    agi = agility;
}

int Player::GetAttack() const {
    return atk;
}

int Player::GetDefense() const {
    return def;
}

int Player::GetMagicAttack() const {
    return mtk;
}

int Player::GetAgility() const {
    return agi;
}

// 경험치 및 레벨 관리
void Player::GainExperience(int amount) {
    exp += amount;
    // 레벨 업 로직을 추가할 수 있음
    while (exp >= ExperienceNeededForLevel(level)) { // 경험치가 현재 레벨업 필요 경험치 이상이면
        LevelUp();
    }
}

void Player::LevelUp() {
    level++;
    exp -= ExperienceNeededForLevel(level - 1); // 레벨업 시 잔여 경험치 설정
    // 레벨업 시 능력치 증가 등의 로직을 추가할 수 있음
}

int Player::ExperienceNeededForLevel(int level) const {
    // 레벨업에 필요한 경험치는 (레벨 x 200)로 설정
    return level * 200;
}

vector<Item*> Player::GetPlayerInventory() const {
    return inventory;
}

string Player::getName() const {
    return name;
}

void Player::SetCurrentFloor(int floor) {
    currentFloor = floor;
}

int Player::GetCurrentFloor() const {
    return currentFloor;
}

int Player::GetLevel() const {
    return level;
}

int Player::GetExp() const {
    return exp;
}

int Player::GetHealth() const {
    return health;
}

int Player::GetMana() const {
    return mana;
}

int Player::GetStamina() const {
    return stemina;
}

int Player::GetGold() const {
    return Gold;
}

void Player::SetClassName(const string& name) {
    className = name;
}

string Player::GetClassName() const {
    return className;
}

// 현재 레벨업까지 남은 경험치 반환
int Player::GetRemainingExpForLevelUp() const {
    int requiredExp = ExperienceNeededForLevel(level) - ExperienceNeededForLevel(level - 1);
    return requiredExp - exp;
}

