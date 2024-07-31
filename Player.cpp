#include "Player.h"
#include "Item.h"
#include "Monster.h"
#include <iostream>
#include <algorithm> // std::find
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds

Player::Player()
    : name(""), health(0), mana(0), stamina(0), Gold(0), level(1), exp(0), currentFloor(1),
      className("알 수 없음"), atk(0), def(0), mtk(0), agi(0), startExp(200), 
      defending(false), isDebuffed(false), originalAttack(0), levelUpPoints(0), cp(3), maxCP(3) {}

Player::Player(std::string playerName, int playerHealth, int playerMana, int playerStamina,
               int playerGold, int playerLevel, int playerExp, int floor,
               std::string clsName)
    : name(playerName), health(playerHealth), mana(playerMana), stamina(playerStamina),
      Gold(playerGold), level(playerLevel), exp(playerExp), currentFloor(floor),
      className(clsName), atk(0), def(0), mtk(0), agi(0), startExp(200),
      defending(false), isDebuffed(false), originalAttack(0), levelUpPoints(0), cp(3), maxCP(3) {}

Player::~Player() {
    for (auto item : inventory) {
        delete item;
    }
    inventory.clear(); // 인벤토리 클리어
    for (auto card : cards) {
        delete card;
    }
    cards.clear();
}

void Player::PlayerInfo() const {
    std::cout << "이름: " << name << " | 직업: " << className << std::endl;
    std::cout << "체력: " << health << " | 마나: " << mana << std::endl;
    std::cout << "스태미나: " << stamina << std::endl;
    std::cout << "공격력: " << atk << " | 방어력: " << def << std::endl;
    std::cout << "마법력: " << mtk << " | 민첩: " << agi << std::endl;
    std::cout << "골드: " << Gold << std::endl;
    std::cout << "레벨: " << level << " | 남은 경험치: " << GetRemainingExpForLevelUp() << std::endl;
}

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

void Player::AddCard(Card* card) {
    cards.push_back(card);
}

void Player::UseCard(int index, Monster& monster) {
    if (index >= 0 && index < cards.size()) {
        cards[index]->Use(*this, monster);
    } else {
        std::cerr << "잘못된 카드 인덱스입니다." << std::endl;
    }
}

const std::vector<Card*>& Player::GetCards() const {
    return cards;
}

int Player::GetCP() const {
    return cp;
}

void Player::SetCP(int cp) {
    this->cp = cp;
}

void Player::UseCP(int amount) {
    if (cp >= amount) {
        cp -= amount;
    } else {
        std::cerr << "CP가 부족하여 사용이 불가능합니다." << std::endl;
    }
}

void Player::RecoverCP(int amount) {
    cp += amount;
    // CP가 최대 CP를 초과하지 않도록 보장
    if (cp > maxCP) {
        cp = maxCP;
    }
}

int Player::GetMaxCP() const {
    return maxCP;
}

void Player::LevelUp() {
    level++;
    exp -= ExperienceNeededForLevel(level - 1);
    levelUpPoints += 3;
}

void Player::AddLevelUpPoints(int points) {
    levelUpPoints += points;
}

bool Player::UseLevelUpPoints(int attackIncrease, int defenseIncrease, int magicAttackIncrease, int agilityIncrease) {
    int totalPoints = attackIncrease + defenseIncrease + magicAttackIncrease + agilityIncrease;
    if (totalPoints > levelUpPoints) {
        std::cout << "레벨업 포인트가 부족합니다!" << std::endl;
        return false;
    }
    levelUpPoints -= totalPoints;
    return true;
}

int Player::GetLevelUpPoints() const {
    return levelUpPoints;
}

void Player::DecreaseStamina(int amount) {
    stamina -= amount;
    if (stamina <= 0) {
        stamina = 0;
        ApplyDebuff();
    }
}

void Player::SetStamina(int stamina) {
    this->stamina = stamina;
}

int Player::GetStamina() const {
    return stamina;
}

void Player::SetAttack(int attack) {
    this->atk = attack;
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

void Player::GainExperience(int amount) {
    exp += amount;
    while (exp >= ExperienceNeededForLevel(level)) {
        LevelUp();
    }
}

int Player::ExperienceNeededForLevel(int level) const {
    return level * 200;
}

std::vector<Item*> Player::GetPlayerInventory() const {
    return inventory;
}

std::string Player::GetName() const {
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

int Player::GetGold() const {
    return Gold;
}

void Player::SetClassName(const std::string& name) {
    className = name;
}

std::string Player::GetClassName() const {
    return className;
}

int Player::GetRemainingExpForLevelUp() const {
    int requiredExp = ExperienceNeededForLevel(level) - ExperienceNeededForLevel(level - 1);
    return requiredExp - exp;
}

bool Player::IsDefeated() const {
    return health <= 0;
}

void Player::SetDefending(bool defending) {
    this->defending = defending;
}

bool Player::IsDefending() const {
    return defending;
}

void Player::Attack(Monster& monster) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << name << "이(가) " << monster.GetName() << "을(를) 공격합니다!" << std::endl;
    monster.TakeDamage(atk); // 플레이어의 공격력 사용
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << monster.GetName() << "의 남은 체력: " << monster.GetHealth() << std::endl; // 몬스터의 남은 체력 출력
}

void Player::TakeDamage(int amount) {
    int reducedDamage;

    if (defending) {
        // 방어 중일 때, 방어력 + 추가 방어력
        int totalDefense = def + def / 2;
        reducedDamage = std::max(0, amount - totalDefense); // 방어 효과 적용
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << name << "이(가) 방어 중! 방어력: " << totalDefense << std::endl;
    } else {
        // 방어 중이지 않을 때, 기본 방어력만 적용
        reducedDamage = std::max(0, amount - def); // 방어 효과 적용
    }

    // 피해를 체력에서 차감
    health -= reducedDamage;
    if (health < 0) health = 0;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << name << "이(가) " << reducedDamage << "의 피해를 입었습니다! 남은 체력: " << health << std::endl;
    // 방어 상태를 초기화
    defending = false;
}

void Player::ApplyDebuff() {
    if (!isDebuffed) {
        isDebuffed = true;
        originalAttack = atk; // 현재 공격력을 원래의 공격력으로 저장
        atk /= 2; // 공격력을 절반으로 감소
    }
}

void Player::RemoveDebuff() {
    if (isDebuffed) {
        isDebuffed = false;
        atk = originalAttack; // 원래의 공격력으로 복원
    }
}
