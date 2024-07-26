#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Item; // Forward declaration

using namespace std;

using std::string;
using std::vector;

class Player {
public:
    // 기본 생성자
    Player();

    // 파라미터를 받는 생성자
    Player(string playername, int playerhealth, int playermana, int playerstemina, 
           int playergold, int playerlevel, int playerexp, int floor, 
           string clsName);

    // 소멸자
    ~Player();

    // 플레이어 정보 출력
    void PlayerInfo() const;

    // 인벤토리에 아이템 추가 및 제거
    void AddItem(Item* item);
    void RemoveItem(Item* item);

    // 능력치 설정 및 반환
    void SetAttack(int attack);
    void SetDefense(int defense);
    void SetMagicAttack(int magicAttack);
    void SetAgility(int agility);

    int GetAttack() const;
    int GetDefense() const;
    int GetMagicAttack() const;
    int GetAgility() const;

    // 경험치 및 레벨 관리
    void GainExperience(int amount);
    void LevelUp(); // 레벨업 시 경험치 증가 배수 처리

    // 플레이어의 상태 정보 반환
    vector<Item*> GetPlayerInventory() const;
    string getName() const;

    void SetCurrentFloor(int floor);
    int GetCurrentFloor() const;

    int GetLevel() const;
    int GetExp() const;
    int GetHealth() const;
    int GetMana() const;
    int GetStamina() const;
    int GetGold() const;

    void SetClassName(const string& name);
    string GetClassName() const;

    // 현재 레벨업까지 남은 경험치 반환
    int GetRemainingExpForLevelUp() const;

private:
    // 플레이어 정보
    string name;
    int health;
    int mana;
    int stemina;
    int Gold;
    int level;
    int exp;
    int currentFloor;
    string className;
    int atk;    // 공격력
    int def;    // 방어력
    int mtk;    // 마법력
    int agi;    // 민첩

    // 인벤토리
    vector<Item*> inventory;

    // 초기 경험치
    int startExp;

    // 레벨업에 필요한 경험치 계산
    int ExperienceNeededForLevel(int level) const;
};

#endif // PLAYER_H
