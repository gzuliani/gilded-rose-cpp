#ifndef SULFURAS_H
#define SULFURAS_H

#include "RegularItem.h"

class Sulfuras : public RegularItem
{
public:
    Sulfuras(int sellIn)
        : RegularItem("Sulfuras, Hand of Ragnaros", sellIn, 80)
    {}
protected:
    void update_quality() override {}
    void clamp_quality() override {}
    void update_sellIn() override {}
};

#endif // SULFURAS_H
