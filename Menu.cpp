#include "Menu.h"
#include "InGame.h"
#include "MainData.h"
#include "Game.h"
#include <iostream>
#include <limits> // numeric_limits

using namespace std;

void Menu::ProcessMenu() const {
    cout << "1. 새게임 시작" << endl;
    cout << "2. 게임 불러오기" << endl;
    cout << "3. 게임정보" << endl;
    cout << "9. 종료" << endl;
}

void Menu::ClassMenu() const {
    cout << "1. 전사" << endl;
    cout << "2. 마법사" << endl;
    cout << "3. 도적" << endl;
}

void Menu::GameGuide() const {
    cout << "대충 게임 가이드라는 뜻" << endl;
}

int Menu::GetIntegerInput() const {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); // 입력 스트림 상태를 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼를 비운다
            cout << "잘못된 입력입니다. 정수를 입력해주세요: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼를 비운다
            return choice;
        }
    }
}

void Menu::MainMenu() const {
    while (true) {
        cout << "메인 메뉴:" << endl;
        ProcessMenu();
        cout << "입력: ";
        int choice = GetIntegerInput();

        if (choice == 1) {
            int classChoice;
            cout << "클래스 선택:" << endl;
            ClassMenu();
            cout << "입력: ";
            classChoice = GetIntegerInput();
            InGame* ingame = nullptr;

            if (classChoice == 1) {
                string choiceStr;
                cout << "전사 가이드" << endl;
                ingame->WarriorGuide();
                cout << "입력: "; cin >> choiceStr;
                if (choiceStr == "Y" || choiceStr == "y") {
                    cout << "캐릭터 이름을 입력하세요: ";
                    string characterName;
                    cin >> characterName;
                    ingame = new InGame(InGame::WARRIOR, characterName);
                } else if (choiceStr == "N" || choiceStr == "n") {
                    cout << "다시 골라주세요." << endl;
                    MainMenu();
                } else {
                    cout << "잘못 입력하였습니다." << endl;
                    continue;
                }
            } else if (classChoice == 2) {
                string choiceStr;
                cout << "마법사 가이드" << endl;
                ingame->MageGuide();
                cout << "입력: "; cin >> choiceStr;
                if (choiceStr == "Y" || choiceStr == "y") {
                    cout << "캐릭터 이름을 입력하세요: ";
                    string characterName;
                    cin >> characterName;
                    ingame = new InGame(InGame::MAGE, characterName);
                } else if (choiceStr == "N" || choiceStr == "n") {
                    cout << "다시 골라주세요." << endl;
                    MainMenu();
                } else {
                    cout << "잘못 입력하였습니다." << endl;
                    continue;
                }
            } else if (classChoice == 3) {
                string choiceStr;
                cout << "도적 가이드" << endl;
                ingame->RogueGuide();
                cout << "입력: "; cin >> choiceStr;
                if (choiceStr == "Y" || choiceStr == "y") {
                    cout << "캐릭터 이름을 입력하세요: ";
                    string characterName;
                    cin >> characterName;
                    ingame = new InGame(InGame::ROGUE, characterName);
                } else if (choiceStr == "N" || choiceStr == "n") {
                    cout << "다시 골라주세요." << endl;
                    MainMenu();
                } else {
                    cout << "잘못 입력하였습니다." << endl;
                    continue;
                }
            } else {
                cout << "잘못 입력하였습니다. 다시 입력해주세요." << endl;
                continue;
            }

            if (ingame) {
                Game game(ingame);
                game.game();
                delete ingame;
            }
        } else if (choice == 2) {
            cout << "불러올 캐릭터 이름을 입력하세요: ";
            string characterName;
            cin >> characterName;

            if (MainData::CharacterExists(characterName)) {
                Player* player = MainData::LoadData(characterName);
                if (player != nullptr) {
                    InGame* ingame = new InGame(*player);
                    Game game(ingame);
                    game.game();
                    delete ingame;
                    delete player; // 메모리 해제
                } else {
                    cout << "플레이어 데이터를 로드할 수 없습니다." << endl;
                }
            } else {
                cout << "캐릭터가 존재하지 않습니다." << endl;
            }
        } else if (choice == 3) {
            GameGuide();
        } else if (choice == 9) {
            cout << "종료합니다." << endl;
            return;
        }
    }
}
