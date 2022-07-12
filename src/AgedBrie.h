#ifndef AGEDBRIE_H
#define AGEDBRIE_H

#include "RegularItem.h"

class AgedBrie : public RegularItem
{
public:
    AgedBrie(int sellIn, int quality)
        : RegularItem("Aged Brie", sellIn, quality)
    {}
protected:
    void update_quality() override
    {
        quality += (sellIn > 0) ? 1 : 2;
    }
};

#endif // AGEDBRIE_H
