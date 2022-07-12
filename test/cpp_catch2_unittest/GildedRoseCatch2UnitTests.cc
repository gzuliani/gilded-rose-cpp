#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"
#include "GildedRose.h"

ItemPtr make_item(std::string name, int sellIn, int quality) {
    return std::make_shared<RegularItem>(name, sellIn, quality);
}

TEST_CASE("At the end of each day SellIn and Quality decrease for every item")
{
    std::vector<ItemPtr> items{
        make_item("A Generic Item", 2, 5)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 2);
    REQUIRE(items[0]->quality == 5);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 4);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 0);
    REQUIRE(items[0]->quality == 3);
}

TEST_CASE("Quality decreases twice as fast once the sell by date has passed")
{
    std::vector<ItemPtr> items{
        make_item("A Generic Item", 1, 9)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 9);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 0);
    REQUIRE(items[0]->quality == 8);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == -1);
    REQUIRE(items[0]->quality == 6);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == -2);
    REQUIRE(items[0]->quality == 4);
}

TEST_CASE("The Quality of an item is never negative")
{
    std::vector<ItemPtr> items{
        make_item("A Generic Item", 3, 2)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 3);
    REQUIRE(items[0]->quality == 2);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 2);
    REQUIRE(items[0]->quality == 1);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 0);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 0);
    REQUIRE(items[0]->quality == 0);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == -1);
    REQUIRE(items[0]->quality == 0);
}

TEST_CASE("'Aged Brie' actually increases in Quality the older it gets")
{
    std::vector<ItemPtr> items{
        make_item("Aged Brie", 3, 2)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 3);
    REQUIRE(items[0]->quality == 2);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 2);
    REQUIRE(items[0]->quality == 3);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 4);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 0);
    REQUIRE(items[0]->quality == 5);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == -1);
    REQUIRE(items[0]->quality == 7);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == -2);
    REQUIRE(items[0]->quality == 9);
}

TEST_CASE("The Quality of an item is never more than 50 - 'Aged Brie'")
{
    std::vector<ItemPtr> items{
        make_item("Aged Brie", 3, 48)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->quality == 48);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->quality == 49);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->quality == 50);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->quality == 50);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->quality == 50);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->quality == 50);
}

TEST_CASE("'Sulfuras' never has to be sold or decreases in Quality")
{
    std::vector<ItemPtr> items{
        make_item("Sulfuras, Hand of Ragnaros", 1, 80)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 80);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 80);
}

TEST_CASE("'Backstage passes' increases in Quality as SellIn value approaches")
{
    std::vector<ItemPtr> items{
        make_item("Backstage passes to a TAFKAL80ETC concert", 20, 3)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 20);
    REQUIRE(items[0]->quality == 3);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 19);
    REQUIRE(items[0]->quality == 4);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 18);
    REQUIRE(items[0]->quality == 5);
}

TEST_CASE("'Backstage passes' Quality increases by 2 if SellIn is 10 or less")
{
    std::vector<ItemPtr> items{
        make_item("Backstage passes to a TAFKAL80ETC concert", 11, 3)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 11);
    REQUIRE(items[0]->quality == 3);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 10);
    REQUIRE(items[0]->quality == 4);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 9);
    REQUIRE(items[0]->quality == 6);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 8);
    REQUIRE(items[0]->quality == 8);
}

TEST_CASE("'Backstage passes' Quality increases by 3 if SellIn is 5 or less")
{
    std::vector<ItemPtr> items{
        make_item("Backstage passes to a TAFKAL80ETC concert", 6, 3)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 6);
    REQUIRE(items[0]->quality == 3);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 5);
    REQUIRE(items[0]->quality == 5);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 4);
    REQUIRE(items[0]->quality == 8);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 3);
    REQUIRE(items[0]->quality == 11);
}

TEST_CASE("The Quality of an item is never more than 50 - 'Backstage passes'")
{
    std::vector<ItemPtr> items{
        make_item("Backstage passes to a TAFKAL80ETC concert", 3, 48)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 3);
    REQUIRE(items[0]->quality == 48);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 2);
    REQUIRE(items[0]->quality == 50);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 50);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 0);
    REQUIRE(items[0]->quality == 50);
}

TEST_CASE("'Backstage passes' Quality drops to 0 after the concert")
{
    std::vector<ItemPtr> items{
        make_item("Backstage passes to a TAFKAL80ETC concert", 2, 3)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->sellIn == 2);
    REQUIRE(items[0]->quality == 3);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 1);
    REQUIRE(items[0]->quality == 6);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == 0);
    REQUIRE(items[0]->quality == 9);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->sellIn == -1);
    REQUIRE(items[0]->quality == 0);
}
/*
TEST_CASE("'Sulfuras' Quality is 80 and it never alters.")
{
    std::vector<ItemPtr> items{
        make_item("Sulfuras, Hand of Ragnaros", 1, 5)};
    GildedRose gilded_rose{items};

    REQUIRE(items[0]->quality == 80);

    gilded_rose.updateQuality();
    REQUIRE(items[0]->quality == 80);
}
*/