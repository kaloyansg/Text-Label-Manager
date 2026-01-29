#include "catch2/catch_all.hpp"
#include "../headers/DecorateTransformation.h"

TEST_CASE("DecorateTransformation: Formatting Logic", "[DecorateTransformation]") {

    DecorateTransformation decorator;

    SECTION("Standard Decoration") {
        std::string input = "Hello World";
        std::string expected = "-={ Hello World }=-";

        REQUIRE(decorator.transform(input) == expected);
    }

    SECTION("Empty String Decoration") {
        std::string input = "";
        std::string expected = "-={  }=-";

        REQUIRE(decorator.transform(input) == expected);
    }

    SECTION("Already Decorated String") {
        std::string input = "-={ Text }=-";
        std::string expected = "-={ -={ Text }=- }=-";

        REQUIRE(decorator.transform(input) == expected);
    }
}

TEST_CASE("DecorateTransformation: Cloning", "[DecorateTransformation]") {

    DecorateTransformation original;
    std::unique_ptr<TextTransformation> clone = original.clone();

    SECTION("Clone is created successfully") {
        REQUIRE(clone != nullptr);
    }

    SECTION("Clone is a distinct object") {
        REQUIRE(clone.get() != &original);
    }

    SECTION("Clone behaves exactly like original") {
        std::string input = "Test";
        REQUIRE(clone->transform(input) == original.transform(input));
        REQUIRE(clone->transform(input) == "-={ Test }=-");
    }

    SECTION("Clone preserves type") {
        auto* casted = dynamic_cast<DecorateTransformation*>(clone.get());
        REQUIRE(casted != nullptr);
    }
}