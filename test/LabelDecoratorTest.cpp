#include "catch2/catch_all.hpp"
#include "../headers/LabelDecorator.h"
#include "../headers/SimpleLabel.h"

//Mocks

class BorderDecorator : public LabelDecorator {
public:
    using LabelDecorator::LabelDecorator; // Inherit constructor
    std::string getText() const override { return "[" + LabelDecorator::getText() + "]"; }
    std::unique_ptr<Label> clone() const override { return std::make_unique<BorderDecorator>(*this); }
};
class ColorDecorator : public LabelDecorator {
public:
    using LabelDecorator::LabelDecorator; // Inherit constructor
    std::string getText() const override { return "Color(" + LabelDecorator::getText() + ")"; }
    std::unique_ptr<Label> clone() const override { return std::make_unique<ColorDecorator>(*this); }
};

///////////////////////////////

TEST_CASE("LabelDecorator: Basic Delegation", "[LabelDecorator]") {
    auto simple = std::make_unique<SimpleLabel>("Text");
    BorderDecorator decorated(std::move(simple));

    SECTION("getText delegates to child") {
        REQUIRE(decorated.getText() == "[Text]");
    }

    SECTION("setValue delegates to child") {
        decorated.setValue("New");
        REQUIRE(decorated.getText() == "[New]");
    }
}

TEST_CASE("LabelDecorator: Static Removal (removeDecoratorFrom)", "[LabelDecorator]") {
    std::unique_ptr<Label> chain = std::make_unique<SimpleLabel>("Text");
    chain = std::make_unique<BorderDecorator>(std::move(chain));
    chain = std::make_unique<ColorDecorator>(std::move(chain));
    chain = std::make_unique<BorderDecorator>(std::move(chain));

    SECTION("Verify Initial State") {
        REQUIRE(chain->getText() == "[Color([Text])]");
    }

    SECTION("Remove Leaf Decorator (Color)") {

        chain = LabelDecorator::removeDecoratorFrom<ColorDecorator>(std::move(chain));

        REQUIRE(chain != nullptr);
        REQUIRE(chain->getText() == "[[Text]]");
    }

    SECTION("Remove Outer Decorator (Border)") {

        chain = LabelDecorator::removeDecoratorFrom<BorderDecorator>(std::move(chain));

        REQUIRE(chain != nullptr);
        REQUIRE(chain->getText() == "Color(Text)");
    }

    SECTION("Remove Non-Existent Decorator") {
        class InvisibleDecorator : public LabelDecorator {
            using LabelDecorator::LabelDecorator;
            std::unique_ptr<Label> clone() const override { return nullptr; }
        };

        chain = LabelDecorator::removeDecoratorFrom<InvisibleDecorator>(std::move(chain));

        REQUIRE(chain->getText() == "[Color([Text])]");
    }

    SECTION("Handling nullptr") {
        std::unique_ptr<Label> empty;
        empty = LabelDecorator::removeDecoratorFrom<BorderDecorator>(std::move(empty));
        REQUIRE(empty == nullptr);
    }
}

TEST_CASE("LabelDecorator: Member Removal (removeDecorator)", "[LabelDecorator]") {

    SECTION("Removes Child Decorator") {
        auto chain = std::make_unique<BorderDecorator>(
            std::make_unique<ColorDecorator>(
                std::make_unique<SimpleLabel>("Text")
            )
        );
        std::shared_ptr<Label> result = chain->removeDecorator<ColorDecorator>();

        REQUIRE(result->getText() == "[Text]");
    }
}