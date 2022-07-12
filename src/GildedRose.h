#include <memory>
#include <string>
#include <vector>

class Item
{
public:
    std::string name;
    int sellIn;
    int quality;
    Item(std::string name, int sellIn, int quality)
        : name(name), sellIn(sellIn), quality(quality) 
    {}
};

using ItemPtr = std::shared_ptr<Item>;

class GildedRose
{
public:
    std::vector<ItemPtr>& items;
    GildedRose(std::vector<ItemPtr>& items);
    
    void updateQuality();
};
