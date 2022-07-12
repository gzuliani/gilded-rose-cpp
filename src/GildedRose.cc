#include "GildedRose.h"

GildedRose::GildedRose(std::vector<ItemPtr>& items) : items(items)
{}
    
void GildedRose::updateQuality() 
{
    for (auto& item : items)
        item->update();
}
