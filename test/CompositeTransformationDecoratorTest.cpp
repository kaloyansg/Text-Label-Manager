#include "catch2/catch_all.hpp"
#include "../headers/CompositeTransformationDecorator.h"

//Mocks
class MockLabel : public Label {
    std::string val;
public:
    MockLabel(std::string v) : val(std::move(v)) {}
    std::string getText() const override { return val; }
    bool setValue(const std::string& v) override { val = v; return true; }
    std::unique_ptr<Label> clone() const override { return std::make_unique<MockLabel>(*this); }
};


class AppendTransform : public TextTransformation {
    std::string suffix;
public:
    AppendTransform(std::string s) : suffix(std::move(s)) {}
    std::string transform(const std::string& in) const override { return in + suffix; }
    std::unique_ptr<TextTransformation> clone() const override { return std::make_unique<AppendTransform>(*this); }
};

//////////////////////////////////////

TEST_CASE("CompositeTransformation: Execution Logic", "[CompositeTransformation]") {

    auto baseLabel = std::make_unique<MockLabel>("Start");

    SECTION("Empty transformation list returns original text") {
        std::vector<std::unique_ptr<TextTransformation>> emptyList;
        CompositeTransformationDecorator composite(std::move(baseLabel), emptyList);

        REQUIRE(composite.getText() == "Start");
    }

    SECTION("Correct Chaining Logic (Sequence Preservation)") {
        std::vector<std::unique_ptr<TextTransformation>> list;
        list.push_back(std::make_unique<AppendTransform>(" A"));
        list.push_back(std::make_unique<AppendTransform>(" B"));

        CompositeTransformationDecorator composite(std::move(baseLabel), list);
        REQUIRE(composite.getText() == "Start A B");
    }
}

TEST_CASE("CompositeTransformation: Deep Copying", "[CompositeTransformation]") {

    auto base = std::make_unique<MockLabel>("Original");
    std::vector<std::unique_ptr<TextTransformation>> list;
    list.push_back(std::make_unique<AppendTransform>("_T1"));

    CompositeTransformationDecorator original(std::move(base), list);

    SECTION("Clone creates valid object") {
        std::unique_ptr<Label> copy = original.clone();
        REQUIRE(copy != nullptr);
    }

    SECTION("Clone is independent") {
        std::unique_ptr<Label> copy = original.clone();

        original.setValue("Changed");
    }
}