#ifndef CONJUREDITEM_H
#define CONJUREDITEM_H

#include "RegularItem.h"

class ConjuredItem : public RegularItem
{
public:
    ConjuredItem(std::string name, int sellIn, int quality)
        : RegularItem(name, sellIn, quality)
    {}
    void update_quality() override
    {
        quality -= (sellIn > 0) ? 2 : 4;
    }
};

#endif // CONJUREDITEM_H
