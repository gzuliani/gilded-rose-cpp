#ifndef BACKSTAGEPASS_H
#define BACKSTAGEPASS_H

#include "RegularItem.h"

class BackstagePass : public RegularItem
{
public:
    BackstagePass(int sellIn, int quality)
        : RegularItem("Backstage passes to a TAFKAL80ETC concert", sellIn, quality)
    {}
protected:
    void update_quality() override
    {
        if (sellIn > 10)
            quality += 1;
        else if (sellIn > 5)
            quality += 2;
        else if (sellIn > 0)
            quality += 3;
        else
            quality = 0;
    }
};

#endif // BACKSTAGEPASS_H
