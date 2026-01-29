#include "catch2/catch_all.hpp"
#include "../headers/SimpleLabel.h"

TEST_CASE("SimpleLabel: Core Functionality", "[SimpleLabel]") {

    SECTION("Initialization sets correct value") {
        SimpleLabel label("Hello World");

        REQUIRE(label.getText() == "Hello World");
        REQUIRE_FALSE(label.getText().empty());
    }

    SECTION("Setting a new value updates the label") {
        SimpleLabel label("Initial");

        bool result = label.setValue("Updated");

        CHECK(result == true);
        REQUIRE(label.getText() == "Updated");
    }

    SECTION("Handling edge cases with strings") {
        SimpleLabel label("Normal");

        SECTION("Empty string") {
            label.setValue("");
            REQUIRE(label.getText() == "");
            REQUIRE(label.getText().empty());
        }

        SECTION("Special characters") {
            std::string weirdText = "Text\nWith\tTabs";
            label.setValue(weirdText);
            REQUIRE(label.getText() == weirdText);
        }
    }

    SECTION("Cloning creates an independent copy") {
        SimpleLabel original("Original Text");

        std::unique_ptr<Label> copy = original.clone();

        REQUIRE(copy != nullptr);
        REQUIRE(copy->getText() == "Original Text");

        original.setValue("Changed Original");

        CHECK(original.getText() == "Changed Original");
        REQUIRE(copy->getText() == "Original Text");

        copy->setValue("Changed Copy");
        REQUIRE(original.getText() == "Changed Original");
    }
}