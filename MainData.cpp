#include "MainData.h"
#include "Weapon.h"
#include "Armor.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void MainData::SaveData(const Player& player) {
    string fileName = player.GetName() + ".txt";
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "파일 열기에 실패했습니다: " << fileName << endl;
        return;
    }

    // 기본 정보 저장
    outFile << player.GetName() << endl;
    outFile << player.GetCurrentFloor() << endl;
    outFile << player.GetClassName() << endl;
    outFile << player.GetHealth() << endl;
    outFile << player.GetStamina() << endl;
    outFile << player.GetMana() << endl;
    outFile << player.GetLevel() << endl;
    outFile << player.GetExp() << endl;
    outFile << player.GetGold() << endl;
    outFile << player.GetPlayerInventory().size() << endl; // 인벤토리 크기 저장

    // 각 아이템 정보를 저장
    for (auto item : player.GetPlayerInventory()) {
        if (item) {
            outFile << item->GetInfo() << endl;
        }
    }

    outFile.close();
}

bool MainData::CharacterExists(const std::string& playerName) {
    string fileName = playerName + ".txt";
    ifstream inFile(fileName);
    bool exists = inFile.good(); // 파일이 존재하면 true 반환
    inFile.close();
    return exists;
}

Player* MainData::LoadData(const std::string& playerName) {
    string fileName = playerName + ".txt";

    // 파일 존재 여부 확인
    if (!CharacterExists(playerName)) {
        cerr << "캐릭터 파일이 존재하지 않습니다: " << fileName << endl;
        return nullptr;
    }

    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "파일 열기에 실패했습니다: " << fileName << endl;
        return nullptr;
    }

    string name;
    int floor;
    string className;
    int health, stamina, mana, level, exp, gold, inventorySize;

    // 파일에서 기본 데이터 읽어옴
    getline(inFile, name);
    inFile >> floor;
    inFile.ignore(); // 줄바꿈 문자 무시
    getline(inFile, className);
    inFile >> health >> stamina >> mana >> level >> exp >> gold >> inventorySize;
    inFile.ignore(); // 줄바꿈 문자 무시

    // 데이터 유효성 검사
    if (name.empty() || className.empty() || inventorySize < 0) {
        cerr << "파일 데이터가 유효하지 않습니다: " << fileName << endl;
        return nullptr;
    }

    // 플레이어 객체 생성
    Player* player = new Player(name, health, mana, stamina, gold, level, exp, floor, className);

    // 인벤토리에 아이템 추가
    for (int i = 0; i < inventorySize; ++i) {
        string itemInfo;
        getline(inFile, itemInfo);

        Item* item = nullptr;
        if (itemInfo.find("Weapon") != string::npos) {
            item = new Weapon(itemInfo);
        } else if (itemInfo.find("Armor") != string::npos) {
            item = new Armor(itemInfo);
        }

        if (item) {
            player->AddItem(item); // AddItem 사용하여 아이템 추가
        }
    }

    inFile.close();
    return player;
}
