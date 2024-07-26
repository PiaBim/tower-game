#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"

class Weapon : public Item {
public:
    Weapon(const std::string& weaponInfo) : Item(weaponInfo) {}

    std::string GetInfo() const override {
        return "Weapon: " + info;
    }
};

#endif
