#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "Item.h"

class Armor : public Item {
public:
    Armor(const std::string& armorInfo) : Item(armorInfo) {}

    std::string GetInfo() const override {
        return "Armor: " + info;
    }
};

#endif
