#ifndef SULFURAS_H
#define SULFURAS_H

#include "RegularItem.h"

class Sulfuras : public RegularItem
{
public:
    Sulfuras(int sellIn)
        : RegularItem("Sulfuras, Hand of Ragnaros", sellIn, 80)
    {}
    void update() override
    {}
};

#endif // SULFURAS_H
