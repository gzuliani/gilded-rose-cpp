#ifndef BACKSTAGEPASS_H
#define BACKSTAGEPASS_H

#include "RegularItem.h"

class BackstagePass : public RegularItem
{
public:
    BackstagePass(int sellIn, int quality)
        : RegularItem("Backstage passes to a TAFKAL80ETC concert", sellIn, quality)
    {}
    void update() override
    {
        if (sellIn > 10)
            quality += 1;
        else if (sellIn > 5)
            quality += 2;
        else if (sellIn > 0)
            quality += 3;
        else
            quality = 0;
        quality = std::min(std::max(quality, 0), 50);
        sellIn -= 1;
    }
};

#endif // BACKSTAGEPASS_H
