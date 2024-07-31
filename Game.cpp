#include "Game.h"
#include "MainData.h"
#include "Event.h"
#include "Player.h"
#include <iostream>
#include <ctime> // time() 사용을 위한 헤더

using namespace std;

void Game::gamemenu() const {
    cout << "1. 나아간다" << endl;
    cout << "2. 캐릭터 정보보기" << endl;
    cout << "3. 현재 층 보기" << endl;
    cout << "4. 저장하기" << endl;
    cout << "5. 레벨업" << endl;
    cout << "6. 카드 덱 보기" << endl;
    cout << "9. 종료하기" << endl;
}

void Game::game() const {
    // 기존 코드 유지
    while (true) {
        int choice;
        gamemenu();
        cout << "입력: "; cin >> choice;

        if (choice == 1) {
            cout << "캐릭터가 나아갑니다..." << endl;
            ingame->SetCurrentFloor(ingame->GetCurrentFloor() + 1);

            // 스태미너 감소
            Player* player = ingame->GetPlayer();
            player->DecreaseStamina(5);
            cout << "플레이어의 스태미너가 감소합니다. 남은 스태미너: " << player->GetStamina() << endl;

            // 이벤트 발생
            Event event = Event::GenerateRandomEvent(ingame->GetCurrentFloor()); // 현재 층수를 인자로 전달
            cout << event.GetDescription() << endl;
            event.HandleEvent(*player);
            
            cout << "탑을 올라서 경험치가 10 증가하였습니다." << endl;
            ingame->GainPlayerExperience(10);

        } else if (choice == 2) {
            cout << "[캐릭터 정보]" << endl;
            ingame->PlayerInfo();
        } else if (choice == 3) {
            cout << "현재 층은 " << ingame->GetCurrentFloor() << "F입니다." << endl;
        } else if (choice == 4) {
            char saveChoice;
            cout << "게임을 저장하시겠습니까? (y/n): ";
            cin >> saveChoice;
            if (saveChoice == 'y' || saveChoice == 'Y') 
                MainData::SaveData(*ingame->GetPlayer()); // 포인터를 참조로 변환하여 전달
        } else if (choice == 5) {
            Player* player = ingame->GetPlayer();
            int levelUpPoints = player->GetLevelUpPoints();
            cout << "현재 레벨업 포인트: " << levelUpPoints << endl;

            if (levelUpPoints <= 0) {
                cout << "레벨업 포인트가 부족합니다." << endl;
                continue;
            }

            int pointChoice;
            cout << "어떤 능력치를 올리겠습니까? (1. 공격력 2. 방어력 3. 마법 공격력 4. 민첩도)" << endl;
            cout << "입력: "; cin >> pointChoice;

            int increaseAmount;
            cout << "몇 포인트를 사용할까요? "; cin >> increaseAmount;

            if (increaseAmount <= 0 || increaseAmount > levelUpPoints) {
                cout << "유효하지 않은 포인트 입력입니다." << endl;
                continue;
            }

            bool success = false;

            switch (pointChoice) {
                case 1:
                    success = player->UseLevelUpPoints(increaseAmount, 0, 0, 0);
                    if (success) {
                        player->SetAttack(player->GetAttack() + increaseAmount);
                    }
                    break;
                case 2:
                    success = player->UseLevelUpPoints(0, increaseAmount, 0, 0);
                    if (success) {
                        player->SetDefense(player->GetDefense() + increaseAmount);
                    }
                    break;
                case 3:
                    success = player->UseLevelUpPoints(0, 0, increaseAmount, 0);
                    if (success) {
                        player->SetMagicAttack(player->GetMagicAttack() + increaseAmount);
                    }
                    break;
                case 4:
                    success = player->UseLevelUpPoints(0, 0, 0, increaseAmount);
                    if (success) {
                        player->SetAgility(player->GetAgility() + increaseAmount);
                    }
                    break;
                default:
                    cout << "잘못된 선택입니다." << endl;
                    continue;
            }

            if (success) {
                cout << "능력치가 성공적으로 증가되었습니다!" << endl;
            } else {
                cout << "능력치 증가 실패." << endl;
            }
        } else if (choice == 6) {
            ingame->PrintCardDeck();
        }
         else if (choice == 9) {
            char exitChoice;
            cout << "게임을 종료하시겠습니까? (y/n): ";
            cin >> exitChoice;
            if (exitChoice == 'y' || exitChoice == 'Y') {
                exit(0);
            }
        } else {
            cout << "잘못 입력하셨습니다." << endl;
            continue;
        }
    }
}
