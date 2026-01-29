#include "catch2/catch_all.hpp"
#include "../headers/TextTransformationDecorator.h"

class MockLabel : public Label {
    std::string value;
public:
    MockLabel(std::string v) : value(std::move(v)) {}
    std::string getText() const override { return value; }
    bool setValue(const std::string& v) override { value = v; return true; }
    std::unique_ptr<Label> clone() const override { return std::make_unique<MockLabel>(*this); }
};

class MockSuffixTransform : public TextTransformation {
    std::string suffix;
public:
    MockSuffixTransform(std::string s) : suffix(std::move(s)) {}

    std::string transform(const std::string& input) const override {
        return input + suffix;
    }

    std::unique_ptr<TextTransformation> clone() const override {
        return std::make_unique<MockSuffixTransform>(*this);
    }
};

TEST_CASE("TextTransformationDecorator: Core Logic", "[TextTransformationDecorator]") {

    std::unique_ptr<MockLabel> label = std::make_unique<MockLabel>("Hello");
    std::unique_ptr<MockSuffixTransform> transform = std::make_unique<MockSuffixTransform>(" World");

    SECTION("Decorator applies transformation to label text") {
        TextTransformationDecorator decorator(std::move(label), std::move(transform));

        REQUIRE(decorator.getText() == "Hello World");
    }

    SECTION("Decorator chains correctly") {

        std::unique_ptr<MockLabel> innerLabel = std::make_unique<MockLabel>("Hello");
        std::unique_ptr<MockSuffixTransform> innerTrans = std::make_unique<MockSuffixTransform>(" World");
        std::unique_ptr<TextTransformationDecorator> innerDecorator = std::make_unique<TextTransformationDecorator>(std::move(innerLabel), std::move(innerTrans));

        std::unique_ptr<MockSuffixTransform> outerTrans = std::make_unique<MockSuffixTransform>("!");
        TextTransformationDecorator outerDecorator(std::move(innerDecorator), std::move(outerTrans));

        REQUIRE(outerDecorator.getText() == "Hello World!");
    }
}

TEST_CASE("TextTransformationDecorator: Deep Copying", "[TextTransformationDecorator]") {

    std::unique_ptr<MockLabel> label = std::make_unique<MockLabel>("Base");
    std::unique_ptr<MockSuffixTransform> transform = std::make_unique<MockSuffixTransform>("_Transformed");

    TextTransformationDecorator original(std::move(label), std::move(transform));

    SECTION("Clone creates a valid object") {
        std::unique_ptr<Label> copy = original.clone();
        REQUIRE(copy != nullptr);
        REQUIRE(copy->getText() == "Base_Transformed");
    }

    SECTION("Clone is independent (Deep Copy)") {
        std::unique_ptr<Label> copy = original.clone();

        original.setValue("Changed");

        CHECK(original.getText() == "Changed_Transformed");

        REQUIRE(copy->getText() == "Base_Transformed");
    }
}