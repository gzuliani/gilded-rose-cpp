#ifndef AGEDBRIE_H
#define AGEDBRIE_H

#include "RegularItem.h"

class AgedBrie : public RegularItem
{
public:
    AgedBrie(int sellIn, int quality)
        : RegularItem("Aged Brie", sellIn, quality)
    {}
    void update() override
    {
        quality += (sellIn > 0) ? 1 : 2;
        quality = std::min(std::max(quality, 0), 50);
        sellIn -= 1;
    }
};

#endif // AGEDBRIE_H
