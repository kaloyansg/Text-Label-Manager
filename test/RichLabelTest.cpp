#include "catch2/catch_all.hpp"
#include "../headers/RichLabel.h"

TEST_CASE("RichLabel: Polymorphism and Inheritance", "[RichLabel]") {

    std::string text = "Warning Message";
    std::string color = "#FF0000";
    size_t fontSize = 14;
    std::string font = "Arial";

    SECTION("Construction and Basic Inheritance") {
        RichLabel richLabel(text, color, fontSize, font);

        REQUIRE(richLabel.getText() == text);

        richLabel.setValue("New Text");
        REQUIRE(richLabel.getText() == "New Text");
    }

    SECTION("Cloning Polymorphism (The Slicing Check)") {
        RichLabel original(text, color, fontSize, font);

        std::unique_ptr<Label> copy = original.clone();

        REQUIRE(copy != nullptr);

        REQUIRE(copy->getText() == text);

        RichLabel* rawPtr = dynamic_cast<RichLabel*>(copy.get());

        REQUIRE(rawPtr != nullptr);
    }

    SECTION("Deep Copy Independence") {
        RichLabel original("Original", color, fontSize, font);
        std::unique_ptr<Label> copy = original.clone();

        original.setValue("Modified");

        REQUIRE(copy->getText() == "Original");
    }
}