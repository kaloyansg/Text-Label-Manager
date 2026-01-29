#include "catch2/catch_all.hpp"
#include "../headers/LeftTrimTransformation.h"

TEST_CASE("LeftTrimTransformation: Trimming Logic", "[LeftTrimTransformation]") {

    LeftTrimTransformation trimmer;

    SECTION("Basic Left Trimming") {
        REQUIRE(trimmer.transform("   Hello") == "Hello");
        REQUIRE(trimmer.transform("\tTabStart") == "\tTabStart");
    }

    SECTION("No Trimming Needed") {
        REQUIRE(trimmer.transform("Hello") == "Hello");
        REQUIRE(trimmer.transform("Hello   ") == "Hello   ");
    }

    SECTION("Internal Spaces Preserved") {
        REQUIRE(trimmer.transform("   Hello World   ") == "Hello World   ");
    }

    SECTION("All Spaces") {
        REQUIRE(trimmer.transform("   ") == "");
        REQUIRE(trimmer.transform(" ") == "");
    }

    SECTION("Empty String") {
        REQUIRE(trimmer.transform("") == "");
    }
}

TEST_CASE("LeftTrimTransformation: Cloning", "[LeftTrimTransformation]") {
    LeftTrimTransformation original;
    std::unique_ptr<TextTransformation> clone = original.clone();

    SECTION("Clone is valid") {
        REQUIRE(clone != nullptr);
        REQUIRE(clone.get() != &original);
    }

    SECTION("Clone functionality matches") {
        REQUIRE(clone->transform("   Test") == "Test");
    }
}