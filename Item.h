#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>

class Item {
protected:
    std::string info;

public:
    Item(const std::string& itemInfo) : info(itemInfo) {}
    virtual ~Item() {}

    virtual std::string GetInfo() const = 0; // 순수 가상 함수
};

#endif
