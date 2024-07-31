#include "Event.h"
#include "Player.h"
#include "MonsterFight.h"
#include <iostream>
#include <cstdlib> // rand()
#include <ctime>   // time()

using namespace std;

Event::Event(EventType type, const string& description)
    : type(type), description(description) {}

EventType Event::GetType() const {
    return type;
}

string Event::GetDescription() const {
    return description;
}

void Event::HandleEvent(const Player& player) const { // const Player&로 수정
    switch (type) {
        case EventType::MONSTER_ENCOUNTER:
            cout << "전투가 시작되었습니다!" << endl;
            MonsterFight::StartFight(player); // const Player&로 수정
            break;
        case EventType::TREASURE_FOUND:
            cout << "아이템을 얻었습니다!" << endl;
            // 아이템 획득 로직 추가 가능
            break;
        case EventType::TRAP_TRIGGERED:
            cout << "데미지를 받았습니다!" << endl;
            // 트랩 처리 로직 추가 가능
            break;
        default:
            cout << "특별한 일이 발생하지 않았습니다." << endl;
            break;
    }
}

Event Event::GenerateRandomEvent(int currentFloor) {
    int random = rand() % 100; // 0부터 99까지의 랜덤 숫자 생성

    EventType type;
    if (currentFloor <= 30) {
        if (random < 40) { // 40% 확률로 슬라임 또는 고블린
            // 슬라임과 고블린 처리 로직
            type = EventType::MONSTER_ENCOUNTER;
        } else if (random < 55) { // 30% 확률로 보물 이벤트
            type = EventType::TREASURE_FOUND;
        } else if (random < 70) { // 20% 확률로 함정 이벤트
            type = EventType::TRAP_TRIGGERED;
        } else { // 10% 확률로 아무 일도 발생하지 않음
            type = EventType::NONE;
        }
    } else {
        // 30층 초과일 경우
        if (random < 30) { // 30% 확률로 보물 이벤트
            type = EventType::TREASURE_FOUND;
        } else if (random < 60) { // 30% 확률로 함정 이벤트
            type = EventType::TRAP_TRIGGERED;
        } else { // 40% 확률로 아무 일도 발생하지 않음
            type = EventType::NONE;
        }
    }

    std::string description;
    switch (type) {
        case EventType::MONSTER_ENCOUNTER: description = "몬스터가 나타났습니다!"; break;
        case EventType::TREASURE_FOUND: description = "보물을 발견했습니다!"; break;
        case EventType::TRAP_TRIGGERED: description = "함정이 발동되었습니다!"; break;
        default: description = "아무 일도 일어나지 않았습니다."; break;
    }

    return Event(type, description);
}
