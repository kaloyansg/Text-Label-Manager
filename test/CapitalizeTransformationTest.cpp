#include "catch2/catch_all.hpp"
#include "../headers/CapitalizeTransformation.h"

TEST_CASE("CapitalizeTransformation: Logic and Behavior", "[CapitalizeTransformation]") {

    CapitalizeTransformation caps;

    SECTION("Standard usage: Lowercase starts become uppercase") {
        REQUIRE(caps.transform("hello") == "Hello");
        REQUIRE(caps.transform("world") == "World");
        REQUIRE(caps.transform("cpp") == "Cpp");
    }

    SECTION("Existing uppercase remains unchanged") {
        REQUIRE(caps.transform("Hello") == "Hello");
        REQUIRE(caps.transform("ALL CAPS") == "ALL CAPS");
    }

    SECTION("Non-alphabetic starts remain unchanged") {
        REQUIRE(caps.transform("123 test") == "123 test");
        REQUIRE(caps.transform("!warning") == "!warning");
        REQUIRE(caps.transform(" hello") == " hello");
    }

    SECTION("Cloning logic") {
        std::unique_ptr<TextTransformation> original = std::make_unique<CapitalizeTransformation>();

        std::unique_ptr<TextTransformation> clone = original->clone();

        REQUIRE(clone != nullptr);

        REQUIRE(clone->transform("test") == "Test");

        REQUIRE(original.get() != clone.get());

        CapitalizeTransformation* castedPtr = dynamic_cast<CapitalizeTransformation*>(clone.get());
        REQUIRE(castedPtr != nullptr);
    }
}