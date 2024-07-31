#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <cstdlib> // rand()

using namespace std;

enum class EventType {
    NONE,
    MONSTER_ENCOUNTER,
    TREASURE_FOUND,
    TRAP_TRIGGERED
};

class Player; // Forward declaration of Player class

class Event {
public:
    Event(EventType type = EventType::NONE, const string& description = "");
    static Event GenerateRandomEvent(int currentFloor);
    EventType GetType() const;
    string GetDescription() const;
    void HandleEvent(const Player& player) const; // const Player&로 수정

    static Event GenerateRandomEvent(); // 랜덤 이벤트 생성 메서드

private:
    EventType type;
    string description;
};

#endif // EVENT_H
