#include "catch2/catch_all.hpp"
#include "../headers/CyclingTransformationsDecorator.h"
#include "../headers/SimpleLabel.h"

//Mock

class MockSuffixTransform : public TextTransformation {
    std::string suffix;
public:
    MockSuffixTransform(std::string s) : suffix(std::move(s)) {}
    std::string transform(const std::string& input) const override { return input + suffix; }
    std::unique_ptr<TextTransformation> clone() const override { return std::make_unique<MockSuffixTransform>(suffix); }
};

TEST_CASE("CyclingTransformationsDecorator Mechanics", "[decorator]") {
    std::string baseText = "hello";
    auto label = std::make_unique<SimpleLabel>(baseText);

    SECTION("Cycles through multiple transformations correctly") {
        // Prepare transformations: +A, +B, +C
        std::vector<std::unique_ptr<TextTransformation>> transforms;
        transforms.push_back(std::make_unique<MockSuffixTransform>("A"));
        transforms.push_back(std::make_unique<MockSuffixTransform>("B"));
        transforms.push_back(std::make_unique<MockSuffixTransform>("C"));

        CyclingTransformationsDecorator decorator(std::move(label), transforms);

        REQUIRE(decorator.getText() == "helloA");
        REQUIRE(decorator.getText() == "helloB");
        REQUIRE(decorator.getText() == "helloC");
        REQUIRE(decorator.getText() == "helloA");
    }

    SECTION("Handles empty transformation vector") {
        std::vector<std::unique_ptr<TextTransformation>> emptyTransforms;

        CyclingTransformationsDecorator decorator(std::move(label), emptyTransforms);

        REQUIRE(decorator.getText() == "hello");
        REQUIRE(decorator.getText() == "hello");
    }

    SECTION("Handles single transformation") {
        std::vector<std::unique_ptr<TextTransformation>> transforms;
        transforms.push_back(std::make_unique<MockSuffixTransform>("!"));

        CyclingTransformationsDecorator decorator(std::move(label), transforms);

        REQUIRE(decorator.getText() == "hello!");
        REQUIRE(decorator.getText() == "hello!");
    }
}

TEST_CASE("CyclingTransformationsDecorator Copying and Cloning", "[decorator]") {

    auto label = std::make_unique<SimpleLabel>("test");
    std::vector<std::unique_ptr<TextTransformation>> transforms;
    transforms.push_back(std::make_unique<MockSuffixTransform>("1"));
    transforms.push_back(std::make_unique<MockSuffixTransform>("2"));

    CyclingTransformationsDecorator original(std::move(label), transforms);

    original.getText();

    SECTION("Copy Constructor resets index") {
        CyclingTransformationsDecorator copy(original);

        REQUIRE(copy.getText() == "test1");

        REQUIRE(original.getText() == "test2");
    }

    SECTION("Clone method creates independent copy") {
        std::unique_ptr<Label> clonedPtr = original.clone();

        REQUIRE(clonedPtr->getText() == "test1");
        REQUIRE(original.getText() == "test2");
    }
}