#ifndef _EVENT_H
#define _EVENT_H

#include <string>
#include <cstdlib> // rand() 및 srand() 사용을 위한 헤더

using namespace std;

enum class EventType {
    NONE,
    MONSTER_ENCOUNTER,
    TREASURE_FOUND,
    TRAP_TRIGGERED
};

class Event {
public:
    Event(EventType type = EventType::NONE, const string& description = "");

    EventType GetType() const;
    string GetDescription() const;
    void HandleEvent() const;

    static Event GenerateRandomEvent(); // 랜덤 이벤트 생성 메서드 추가

private:
    EventType type;
    string description;
};

#endif // _EVENT_H
