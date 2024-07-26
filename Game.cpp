#include "Game.h"
#include "MainData.h"
#include "Event.h"
#include <iostream>
#include <ctime> // time() 사용을 위한 헤더

using namespace std;

void Game::gamemenu() const {
    cout << "1. 나아간다" << endl;
    cout << "2. 캐릭터 정보보기" << endl;
    cout << "3. 현재 층 보기" << endl;
    cout << "4. 저장하기" << endl;
    cout << "9. 종료하기" << endl;
}

void Game::game() const {
    srand(static_cast<unsigned int>(time(nullptr))); // 랜덤 시드 초기화

    while (true) {
        int choice;
        gamemenu();
        cout << "입력: "; cin >> choice;

        if (choice == 1) {
            cout << "캐릭터가 나아갑니다..." << endl;
            ingame->SetCurrentFloor(ingame->GetCurrentFloor() + 1);

            
            // 이벤트 발생
            Event event = Event::GenerateRandomEvent();
            cout << event.GetDescription() << endl; //이벤트설명
            event.HandleEvent(); //이벤트 처리

            cout<<"탑을 올라서 경험치가 10증가하였습니다."<<endl;
            ingame->GainPlayerExperience(10); // 경험치 증가
            

        } else if (choice == 2) {
            cout << "[캐릭터 정보]" << endl;
            ingame->PlayerInfo(); // PlayerInfo() 메서드를 통해 캐릭터 정보 출력
        } else if (choice == 3) {
            cout << "현재 층은 " << ingame->GetCurrentFloor() << "F입니다." << endl;
        } else if (choice == 4) {
            char saveChoice;
            cout << "게임을 저장하시겠습니까? (y/n): ";
            cin >> saveChoice;
            if (saveChoice == 'y' || saveChoice == 'Y') {
                MainData::SaveData(ingame->GetPlayer());
            }
        } else if (choice == 9) {
            char exitChoice;
            cout << "게임을 종료하시겠습니까? (y/n): ";
            cin >> exitChoice;
            if (exitChoice == 'y' || exitChoice == 'Y') {
                exit(0);
            }
        }else{
            cout<<"잘못입력하셧습니다."<<endl;
            continue;
        }
    }
}
