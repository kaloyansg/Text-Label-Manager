#include "catch2/catch_all.hpp"
#include "../headers/NormalizeSpaceTransformation.h"


TEST_CASE("NormalizeSpaceTransformation: Logic", "[NormalizeSpaceTransformation]") {

    NormalizeSpaceTransformation normalizer;

    SECTION("Collapsing internal spaces") {
        REQUIRE(normalizer.transform("Hello   World") == "Hello World");

        REQUIRE(normalizer.transform("A  B     C") == "A B C");
    }

    SECTION("Handling leading and trailing spaces") {
        REQUIRE(normalizer.transform("   Start") == " Start");
        REQUIRE(normalizer.transform("End   ") == "End ");
        REQUIRE(normalizer.transform("   Middle   ") == " Middle ");
    }

    SECTION("Strings that don't need changing") {
        REQUIRE(normalizer.transform("Hello World") == "Hello World");
        REQUIRE(normalizer.transform("SingleWord") == "SingleWord");
    }

    SECTION("Strings containing only spaces") {
        REQUIRE(normalizer.transform("     ") == " ");
        REQUIRE(normalizer.transform(" ") == " ");
    }

    SECTION("Edge Case: Empty String") {
        REQUIRE(normalizer.transform("") == "");
    }

    SECTION("Edge Case: Other whitespace characters") {

        std::string input = "Tab\t\tKept";
        REQUIRE(normalizer.transform(input) == input);

        REQUIRE(normalizer.transform("   \t   ") == " \t ");
    }
}

TEST_CASE("NormalizeSpaceTransformation: Cloning", "[NormalizeSpaceTransformation]") {
    NormalizeSpaceTransformation original;
    std::unique_ptr<TextTransformation> clone = original.clone();

    SECTION("Clone creation") {
        REQUIRE(clone != nullptr);
        REQUIRE(clone.get() != &original);
    }

    SECTION("Clone behavior preservation") {
        REQUIRE(clone->transform("A   B") == "A B");
    }
}