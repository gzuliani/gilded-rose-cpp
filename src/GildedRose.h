#include "RegularItem.h"

#include <vector>

class GildedRose
{
public:
    std::vector<ItemPtr>& items;
    GildedRose(std::vector<ItemPtr>& items);
    
    void updateQuality();
};
