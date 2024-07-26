#include "Monster.h"
#include "Player.h"
#include <iostream>

void Monster::Attack(const Player& player) const {
    std::cout << GetName() << "이(가) 플레이어를 공격합니다!" << std::endl;
    // 공격 로직은 이곳에 구현
}
