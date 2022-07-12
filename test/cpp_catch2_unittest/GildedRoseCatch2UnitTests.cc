#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"
#include "GildedRose.h"
#include "AgedBrie.h"
#include "ConjuredItem.h"
#include "BackstagePass.h"
#include "Sulfuras.h"


ItemPtr make_item(std::string name, int sellIn, int quality) {
    return std::make_shared<RegularItem>(name, sellIn, quality);
}

ItemPtr make_sulfuras(int sellIn) {
    return std::make_shared<Sulfuras>(sellIn);
}

ItemPtr make_aged_brie(int sellIn, int quality) {
    return std::make_shared<AgedBrie>(sellIn, quality);
}

ItemPtr make_backstage_pass(int sellIn, int quality) {
    return std::make_shared<BackstagePass>(sellIn, quality);
}

ItemPtr make_conjured(std::string name, int sellIn, int quality) {
    return std::make_shared<ConjuredItem>(name, sellIn, quality);
}

TEST_CASE("At the end of each day SellIn and Quality decrease for every item")
{
    RegularItem item{"A Generic Item", 2, 5};

    REQUIRE(item.sellIn == 2);
    REQUIRE(item.quality == 5);

    item.update();
    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 4);

    item.update();
    REQUIRE(item.sellIn == 0);
    REQUIRE(item.quality == 3);
}

TEST_CASE("Quality decreases twice as fast once the sell by date has passed")
{
    RegularItem item{"A Generic Item", 1, 9};

    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 9);

    item.update();
    REQUIRE(item.sellIn == 0);
    REQUIRE(item.quality == 8);

    item.update();
    REQUIRE(item.sellIn == -1);
    REQUIRE(item.quality == 6);

    item.update();
    REQUIRE(item.sellIn == -2);
    REQUIRE(item.quality == 4);
}

TEST_CASE("The Quality of an item is never negative")
{
    RegularItem item{"A Generic Item", 3, 2};

    REQUIRE(item.sellIn == 3);
    REQUIRE(item.quality == 2);

    item.update();
    REQUIRE(item.sellIn == 2);
    REQUIRE(item.quality == 1);

    item.update();
    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 0);

    item.update();
    REQUIRE(item.sellIn == 0);
    REQUIRE(item.quality == 0);

    item.update();
    REQUIRE(item.sellIn == -1);
    REQUIRE(item.quality == 0);
}

TEST_CASE("'Aged Brie' actually increases in Quality the older it gets")
{
    AgedBrie item{3, 2};

    REQUIRE(item.sellIn == 3);
    REQUIRE(item.quality == 2);

    item.update();
    REQUIRE(item.sellIn == 2);
    REQUIRE(item.quality == 3);

    item.update();
    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 4);

    item.update();
    REQUIRE(item.sellIn == 0);
    REQUIRE(item.quality == 5);

    item.update();
    REQUIRE(item.sellIn == -1);
    REQUIRE(item.quality == 7);

    item.update();
    REQUIRE(item.sellIn == -2);
    REQUIRE(item.quality == 9);
}

TEST_CASE("The Quality of an item is never more than 50 - 'Aged Brie'")
{
    AgedBrie item{3, 48};

    REQUIRE(item.quality == 48);

    item.update();
    REQUIRE(item.quality == 49);

    item.update();
    REQUIRE(item.quality == 50);

    item.update();
    REQUIRE(item.quality == 50);

    item.update();
    REQUIRE(item.quality == 50);

    item.update();
    REQUIRE(item.quality == 50);
}

TEST_CASE("'Sulfuras' never has to be sold or decreases in Quality")
{
    Sulfuras item{1};

    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 80);

    item.update();
    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 80);
}

TEST_CASE("'Backstage passes' increases in Quality as SellIn value approaches")
{
    BackstagePass item{20, 3};

    REQUIRE(item.sellIn == 20);
    REQUIRE(item.quality == 3);

    item.update();
    REQUIRE(item.sellIn == 19);
    REQUIRE(item.quality == 4);

    item.update();
    REQUIRE(item.sellIn == 18);
    REQUIRE(item.quality == 5);
}

TEST_CASE("'Backstage passes' Quality increases by 2 if SellIn is 10 or less")
{
    BackstagePass item{11, 3};

    REQUIRE(item.sellIn == 11);
    REQUIRE(item.quality == 3);

    item.update();
    REQUIRE(item.sellIn == 10);
    REQUIRE(item.quality == 4);

    item.update();
    REQUIRE(item.sellIn == 9);
    REQUIRE(item.quality == 6);

    item.update();
    REQUIRE(item.sellIn == 8);
    REQUIRE(item.quality == 8);
}

TEST_CASE("'Backstage passes' Quality increases by 3 if SellIn is 5 or less")
{
    BackstagePass item{6, 3};

    REQUIRE(item.sellIn == 6);
    REQUIRE(item.quality == 3);

    item.update();
    REQUIRE(item.sellIn == 5);
    REQUIRE(item.quality == 5);

    item.update();
    REQUIRE(item.sellIn == 4);
    REQUIRE(item.quality == 8);

    item.update();
    REQUIRE(item.sellIn == 3);
    REQUIRE(item.quality == 11);
}

TEST_CASE("The Quality of an item is never more than 50 - 'Backstage passes'")
{
    BackstagePass item{3, 48};

    REQUIRE(item.sellIn == 3);
    REQUIRE(item.quality == 48);

    item.update();
    REQUIRE(item.sellIn == 2);
    REQUIRE(item.quality == 50);

    item.update();
    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 50);

    item.update();
    REQUIRE(item.sellIn == 0);
    REQUIRE(item.quality == 50);
}

TEST_CASE("'Backstage passes' Quality drops to 0 after the concert")
{
    BackstagePass item{2, 3};

    REQUIRE(item.sellIn == 2);
    REQUIRE(item.quality == 3);

    item.update();
    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 6);

    item.update();
    REQUIRE(item.sellIn == 0);
    REQUIRE(item.quality == 9);

    item.update();
    REQUIRE(item.sellIn == -1);
    REQUIRE(item.quality == 0);
}

TEST_CASE("'Sulfuras' Quality is 80 and it never alters.")
{
    Sulfuras item{1};

    REQUIRE(item.quality == 80);

    item.update();
    REQUIRE(item.quality == 80);
}

TEST_CASE("All items are updated at once")
{
    std::vector<ItemPtr> items {
        make_item("A generic Item", 5, 3),
        make_aged_brie(2, 6),
        make_sulfuras(5),
        make_backstage_pass(0, 9)
    };
    GildedRose{items}.updateQuality();

    REQUIRE(items[0]->sellIn == 4);
    REQUIRE(items[0]->quality == 2);
    REQUIRE(items[1]->sellIn == 1);
    REQUIRE(items[1]->quality == 7);
    REQUIRE(items[2]->sellIn == 5);
    REQUIRE(items[2]->quality == 80);
    REQUIRE(items[3]->sellIn == -1);
    REQUIRE(items[3]->quality == 0);
}

TEST_CASE("'Conjured' items degrade in Quality twice as fast as normal items")
{
    ConjuredItem item{"A Conjured Item", 2, 9};

    REQUIRE(item.sellIn == 2);
    REQUIRE(item.quality == 9);

    item.update();
    REQUIRE(item.sellIn == 1);
    REQUIRE(item.quality == 7);

    item.update();
    REQUIRE(item.sellIn == 0);
    REQUIRE(item.quality == 5);

    item.update();
    REQUIRE(item.sellIn == -1);
    REQUIRE(item.quality == 1);

    item.update();
    REQUIRE(item.sellIn == -2);
    REQUIRE(item.quality == 0);
}
