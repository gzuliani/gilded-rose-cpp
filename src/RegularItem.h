#ifndef REGULAR_ITEM_H
#define REGULAR_ITEM_H

#include "Item.h"
#include <memory>

class RegularItem : public Item
{
public:
    RegularItem(std::string name, int sellIn, int quality)
        : Item(name, sellIn, quality)
    {}
    virtual void update()
    {
        quality -= (sellIn > 0) ? 1 : 2;
        quality = std::min(std::max(quality, 0), 50); // std::clamp in C++17
        sellIn -= 1;
    }
};

using ItemPtr = std::shared_ptr<RegularItem>;

#endif // REGULAR_ITEM_H
