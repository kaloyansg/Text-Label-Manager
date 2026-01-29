#include "catch2/catch_all.hpp"
#include "../headers/ReplaceTransformation.h"

TEST_CASE("ReplaceTransformation: Core Logic", "[ReplaceTransformation]") {

    SECTION("Single occurrence replacement") {
        ReplaceTransformation replacer("World", "Universe");
        REQUIRE(replacer.transform("Hello World") == "Hello Universe");
    }

    SECTION("Multiple occurrence replacement") {
        ReplaceTransformation replacer("is", "was");
        REQUIRE(replacer.transform("This is it") == "Thwas was it");
    }

    SECTION("Replacement is longer than original") {
        ReplaceTransformation replacer("a", "aaa");
        REQUIRE(replacer.transform("ban") == "baaan");
    }

    SECTION("Replacement is shorter than original") {
        ReplaceTransformation replacer("long", "s");
        REQUIRE(replacer.transform("longword") == "sword");
    }

    SECTION("Replacement is empty (Deletion)") {
        ReplaceTransformation replacer("delete", "");
        REQUIRE(replacer.transform("delete this") == " this");
    }
}

TEST_CASE("ReplaceTransformation: Edge Cases (Bug Detection)", "[ReplaceTransformation]") {

    ReplaceTransformation replacer("test", "pass");

    SECTION("Target word at the very end") {
        REQUIRE(replacer.transform("end test") == "end pass");
    }

    SECTION("Target word is the entire string") {
        REQUIRE(replacer.transform("test") == "pass");
    }

    SECTION("Target word not found") {
        REQUIRE(replacer.transform("nothing here") == "nothing here");
    }

    SECTION("Target word is larger than input string") {
        ReplaceTransformation big("massive", "small");

        REQUIRE(replacer.transform("tiny") == "tiny");
    }

    SECTION("Empty Input String") {
        REQUIRE(replacer.transform("") == "");
    }
}

TEST_CASE("ReplaceTransformation: Cloning", "[ReplaceTransformation]") {
    ReplaceTransformation original("foo", "bar");
    std::unique_ptr<TextTransformation> clone = original.clone();

    SECTION("Clone exists and works") {
        REQUIRE(clone != nullptr);
        REQUIRE(clone->transform("foo fighter") == "bar fighter");
    }

    SECTION("Clone preserves state") {
        REQUIRE(clone->transform("foo") == "bar");
    }
}