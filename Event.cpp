#include "Event.h"
#include <iostream>

using namespace std;

Event::Event(EventType type, const string& description)
    : type(type), description(description) {}

EventType Event::GetType() const {
    return type;
}

string Event::GetDescription() const {
    return description;
}

void Event::HandleEvent() const {
    // 간단한 이벤트 처리 로직
    switch (type) {
        case EventType::MONSTER_ENCOUNTER:
            cout << "전투가 시작되었습니다!" << endl;
            break;
        case EventType::TREASURE_FOUND:
            cout << "아이템을 얻었습니다!" << endl;
            break;
        case EventType::TRAP_TRIGGERED:
            cout << "데미지를 받았습니다!" << endl;
            break;
        default:
            cout << "특별한 일이 발생하지 않았습니다." << endl;
            break;
    }
}

Event Event::GenerateRandomEvent() {
    int random = rand() % 4; // 0, 1, 2, 3 중 하나
    EventType type;

    switch (random) {
        case 0: type = EventType::MONSTER_ENCOUNTER; break;
        case 1: type = EventType::TREASURE_FOUND; break;
        case 2: type = EventType::TRAP_TRIGGERED; break;
        default: type = EventType::NONE; break;
    }

    string description;
    switch (type) {
        case EventType::MONSTER_ENCOUNTER: description = "몬스터가 나타났습니다!"; break;
        case EventType::TREASURE_FOUND: description = "보물을 발견했습니다!"; break;
        case EventType::TRAP_TRIGGERED: description = "함정이 발동되었습니다!"; break;
        default: description = "아무 일도 일어나지 않았습니다."; break;
    }

    return Event(type, description);
}
