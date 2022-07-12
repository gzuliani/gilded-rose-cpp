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
    void update()
    {
        update_quality();
        clamp_quality();
        update_sellIn();
    }
protected:
    virtual void update_quality()
    {
        quality -= (sellIn > 0) ? 1 : 2;
    }
    virtual void clamp_quality()
    {
        quality = std::min(std::max(quality, 0), 50);
    }
    virtual void update_sellIn()
    {
        sellIn -= 1;
    }
};

using ItemPtr = std::shared_ptr<RegularItem>;

#endif // REGULAR_ITEM_H
