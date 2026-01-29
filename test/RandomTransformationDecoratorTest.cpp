#include "catch2/catch_all.hpp"
#include "../headers/RandomTransformationDecorator.h"
#include <stdexcept>

// Mocks
class MockLabel : public Label {
    std::string val;
public:
    MockLabel(std::string v) : val(std::move(v)) {}
    std::string getText() const override { return val; }
    bool setValue(const std::string& v) override { val = v; return true; }
    std::unique_ptr<Label> clone() const override { return std::make_unique<MockLabel>(*this); }
};

class IDTransformation : public TextTransformation {
    std::string id;
public:
    IDTransformation(std::string i) : id(std::move(i)) {}

    std::string transform(const std::string& in) const override {
        return in + "_" + id;
    }

    std::unique_ptr<TextTransformation> clone() const override {
        return std::make_unique<IDTransformation>(*this);
    }
};

/////////////////////////////////////////////////
//

TEST_CASE("RandomTransformationDecorator: Logic", "[RandomTransformationDecorator]") {

    auto baseLabel = std::make_unique<MockLabel>("Base");

    SECTION("Empty transformation list behaves safely") {
        std::vector<std::unique_ptr<TextTransformation>> emptyList;
        RandomTransformationDecorator decorator(std::move(baseLabel), emptyList);

        REQUIRE(decorator.getText() == "Base");
    }

    SECTION("Single transformation is always chosen") {
        std::vector<std::unique_ptr<TextTransformation>> list;
        list.push_back(std::make_unique<IDTransformation>("ONLY"));

        RandomTransformationDecorator decorator(std::move(baseLabel), list);

        for (int i = 0; i < 10; ++i) {
            REQUIRE(decorator.getText() == "Base_ONLY");
        }
    }

    SECTION("Multiple transformations are chosen roughly randomly") {
        std::vector<std::unique_ptr<TextTransformation>> list;
        list.push_back(std::make_unique<IDTransformation>("A"));
        list.push_back(std::make_unique<IDTransformation>("B"));

        RandomTransformationDecorator decorator(std::move(baseLabel), list);

        bool seenA = false;
        bool seenB = false;

        for (int i = 0; i < 100; ++i) {
            std::string result = decorator.getText();
            if (result == "Base_A") seenA = true;
            if (result == "Base_B") seenB = true;
        }

        REQUIRE(seenA == true);
        REQUIRE(seenB == true);
    }
}

TEST_CASE("RandomTransformationDecorator: Deep Copying", "[RandomTransformationDecorator]") {

    auto base = std::make_unique<MockLabel>("Original");
    std::vector<std::unique_ptr<TextTransformation>> list;
    list.push_back(std::make_unique<IDTransformation>("Trans"));

    RandomTransformationDecorator original(std::move(base), list);

    SECTION("Clone creates valid object") {
        std::unique_ptr<Label> copy = original.clone();
        REQUIRE(copy != nullptr);
        REQUIRE(copy->getText() == "Original_Trans");
    }

    SECTION("Clone is independent") {
        std::unique_ptr<Label> copy = original.clone();

        original.setValue("Changed");

        REQUIRE(copy->getText() == "Original_Trans");

        REQUIRE(original.getText() == "Changed_Trans");
    }
}