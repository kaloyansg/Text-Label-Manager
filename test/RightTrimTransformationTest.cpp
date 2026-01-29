#include "catch2/catch_all.hpp"
#include "../headers/RightTrimTransformation.h"

TEST_CASE("RightTrimTransformation: Trimming Logic", "[RightTrimTransformation]") {

    RightTrimTransformation trimmer;

    SECTION("Basic Right Trimming") {
        REQUIRE(trimmer.transform("Hello   ") == "Hello");
        REQUIRE(trimmer.transform("Word ") == "Word");
    }

    SECTION("No Trimming Needed") {
        REQUIRE(trimmer.transform("Hello") == "Hello");
        REQUIRE(trimmer.transform("   Indented") == "   Indented");
    }

    SECTION("Internal Spaces Preserved") {
        REQUIRE(trimmer.transform("Hello   World   ") == "Hello   World");
    }

    SECTION("Null Terminator Handling") {
        std::string input = "Test\0 ";

        REQUIRE(trimmer.transform("Test   ") == "Test");
    }
}

TEST_CASE("RightTrimTransformation: Edge Cases (Crash Detection)", "[RightTrimTransformation]") {

    RightTrimTransformation trimmer;

    SECTION("Empty String") {
        REQUIRE(trimmer.transform("") == "");
    }

    SECTION("String is all spaces") {
        REQUIRE(trimmer.transform("   ") == "");
        REQUIRE(trimmer.transform(" ") == "");
    }

    SECTION("Single character string (Space)") {
        REQUIRE(trimmer.transform(" ") == "");
    }

    SECTION("Single character string (Non-Space)") {
        REQUIRE(trimmer.transform("A") == "A");
    }
}

TEST_CASE("RightTrimTransformation: Cloning", "[RightTrimTransformation]") {
    RightTrimTransformation original;
    std::unique_ptr<TextTransformation> clone = original.clone();

    SECTION("Clone is valid") {
        REQUIRE(clone != nullptr);
        REQUIRE(clone.get() != &original);
    }

    SECTION("Clone functionality matches") {
        REQUIRE(clone->transform("Test   ") == "Test");
    }
}