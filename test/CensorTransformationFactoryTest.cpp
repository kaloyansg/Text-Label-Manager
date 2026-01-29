#include "catch2/catch_all.hpp"
#include "../headers/CensorTransformationFactory.h"

TEST_CASE("CensorTransformationFactory: Flyweight Logic", "[Factory]") {

    SECTION("Short strings (<= 4 chars) are cached") {
        std::string word = "bad"; // Length 3

        std::shared_ptr<CensorTransformation> ptr1 =
            CensorTransformationFactory::createCensorTransformation(word);

        std::shared_ptr<CensorTransformation> ptr2 =
            CensorTransformationFactory::createCensorTransformation(word);

        REQUIRE(ptr1.get() == ptr2.get());
        REQUIRE(ptr1->getWordCensor() == "bad");
    }

    SECTION("Long strings (> 4 chars) are NOT cached") {
        std::string word = "terrible"; // Length 8

        std::shared_ptr<CensorTransformation> ptr1 =
            CensorTransformationFactory::createCensorTransformation(word);

        std::shared_ptr<CensorTransformation> ptr2 =
            CensorTransformationFactory::createCensorTransformation(word);

        REQUIRE(ptr1.get() != ptr2.get());

        REQUIRE(ptr1->getWordCensor() == "terrible");
        REQUIRE(ptr2->getWordCensor() == "terrible");
    }

    SECTION("Boundary Check (Length 4)") {
        std::string word = "four"; //4
        auto ptr1 = CensorTransformationFactory::createCensorTransformation(word);
        auto ptr2 = CensorTransformationFactory::createCensorTransformation(word);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    SECTION("Boundary Check (Length 5)") {
        std::string word = "fives"; //5

        auto ptr1 = CensorTransformationFactory::createCensorTransformation(word);
        auto ptr2 = CensorTransformationFactory::createCensorTransformation(word);
        REQUIRE(ptr1.get() != ptr2.get());
    }

    SECTION("Different short strings have different cache entries") {
        auto ptrA = CensorTransformationFactory::createCensorTransformation("foo");
        auto ptrB = CensorTransformationFactory::createCensorTransformation("bar");

        REQUIRE(ptrA.get() != ptrB.get());
    }
}