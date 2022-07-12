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

class RegularItem : public Item
{
public:
    RegularItem(std::string name, int sellIn, int quality)
        : Item(name, sellIn, quality)
    {}
    virtual void update()
    {
        quality -= (sellIn > 0) ? 1 : 2;
        quality = std::min(std::max(quality, 0), 50); // std::clamp in C++17
        sellIn -= 1;
    }
};

using ItemPtr = std::shared_ptr<RegularItem>;

class GildedRose
{
public:
    std::vector<ItemPtr>& items;
    GildedRose(std::vector<ItemPtr>& items);
    
    void updateQuality();
};
