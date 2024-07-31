#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <string>
#include <vector>

class Card;
class Item;
class Monster;

class Player {
public:
    Player();
    Player(std::string playerName, int playerHealth, int playerMana, int playerStamina,
           int playerGold, int playerLevel, int playerExp, int floor,
           std::string clsName);
    ~Player();

    void PlayerInfo() const;
    void AddItem(Item* item);
    void RemoveItem(Item* item);
    
    void DecreaseStamina(int amount);
    void SetStamina(int stamina);
    int GetStamina() const;
    
    void SetAttack(int attack);
    void SetDefense(int defense);
    void SetMagicAttack(int magicAttack);
    void SetAgility(int agility);

    int GetAttack() const;
    int GetDefense() const;
    int GetMagicAttack() const;
    int GetAgility() const;

    void GainExperience(int amount);
    void LevelUp();
    int ExperienceNeededForLevel(int level) const;
    std::vector<Item*> GetPlayerInventory() const;
    
    std::string GetName() const;
    void SetCurrentFloor(int floor);
    int GetCurrentFloor() const;
    int GetLevel() const;
    int GetExp() const;
    int GetHealth() const;
    int GetMana() const;
    int GetGold() const;
    
    void SetClassName(const std::string& name);
    std::string GetClassName() const;
    int GetRemainingExpForLevelUp() const;

    bool IsDefeated() const;
    void SetDefending(bool defending);
    bool IsDefending() const;
    
    void Attack(Monster& monster);
    void TakeDamage(int amount);

    // New methods for debuff
    void ApplyDebuff();
    void RemoveDebuff();

    void AddLevelUpPoints(int points);
    bool UseLevelUpPoints(int attackIncrease, int defenseIncrease, int magicAttackIncrease, int agilityIncrease);
    int GetLevelUpPoints() const;

    void AddCard(Card* card);
    void UseCard(int index, Monster& monster);
    const std::vector<Card*>& GetCards() const;
    int GetCP() const; // CP 조회
    void SetCP(int cp); // CP 설정
    void UseCP(int amount); // CP 사용
    void RecoverCP(int amount);
    int GetMaxCP() const;

    

private:
    std::string name;
    int health;
    int mana;
    int stamina;
    int Gold;
    int level;
    int exp;
    int currentFloor;
    std::string className;
    int atk;
    int def;
    int mtk;
    int agi;
    int startExp;
    int levelUpPoints;
    
    bool defending;
    bool isDebuffed; // New variable to track debuff state
    int originalAttack; // New variable to store the original attack value

    std::vector<Item*> inventory; // Add inventory to the private section

    std::vector<Card*> cards;
    int cp; 
    int maxCP;
};

#endif // PLAYER_H
