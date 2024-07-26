#ifndef __MAINDATA_H__
#define __MAINDATA_H__

#include <string>
#include "Player.h"

class MainData {
public:
    static void SaveData(const Player& player);
    static bool CharacterExists(const std::string& playerName);
    static Player* LoadData(const std::string& playerName);
};

#endif
