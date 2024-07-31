#ifndef CARD_H
#define CARD_H

#include <string>
#include "Player.h"
#include "Monster.h"

class Card {
public:
    virtual ~Card() = default;
    virtual void Use(Player& player, Monster& monster) = 0; // 카드 사용 함수
    virtual const std::string& GetName() const = 0; // 카드 이름 반환 함수
    virtual int GetCPCost() const = 0; // 카드 사용 시 필요한 CP
};

class SlashCard : public Card {
public:
    SlashCard();
    void Use(Player& player, Monster& monster) override;
    const std::string& GetName() const override;
    int GetCPCost() const override;

private:
    std::string name;
    int cpCost;
};

class ChargeCard : public Card {
public:
    ChargeCard();
    void Use(Player& player, Monster& monster) override;
    const std::string& GetName() const override;
    int GetCPCost() const override;

private:
    std::string name;
    int cpCost;
};

#endif // CARD_H
