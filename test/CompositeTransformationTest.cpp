#include "catch2/catch_all.hpp"
#include "../headers/CompositeTransformation.h"

// Mock
class SuffixTransformation : public TextTransformation {
    std::string suffix;
public:
    SuffixTransformation(const std::string& s) : suffix(s) {}

    std::string transform(const std::string& input) const override {
        return input + suffix;
    }

    std::unique_ptr<TextTransformation> clone() const override {
        return std::make_unique<SuffixTransformation>(suffix);
    }
};

TEST_CASE("CompositeTransformation: Empty Composition", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> empty_vec;
    CompositeTransformation composite(empty_vec);

    SECTION("Returns original string unchanged") {
        std::string input = "Hello";
        REQUIRE(composite.transform(input) == "Hello");
    }
}

TEST_CASE("CompositeTransformation: Single Transformation", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> vec;
    vec.push_back(std::make_unique<SuffixTransformation>("_A"));

    CompositeTransformation composite(vec);

    SECTION("Applies single transformation correctly") {
        REQUIRE(composite.transform("Test") == "Test_A");
    }
}

TEST_CASE("CompositeTransformation: Chaining Transformations", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> vec;
    vec.push_back(std::make_unique<SuffixTransformation>("_A"));
    vec.push_back(std::make_unique<SuffixTransformation>("_B"));
    vec.push_back(std::make_unique<SuffixTransformation>("_C"));

    CompositeTransformation composite(vec);

    SECTION("Applies transformations in the order they were added") {
        REQUIRE(composite.transform("Start") == "Start_A_B_C");
    }
}

TEST_CASE("CompositeTransformation: Copy Semantics and Deep Copy", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> vec;
    vec.push_back(std::make_unique<SuffixTransformation>("_1"));

    CompositeTransformation original(vec);

    SECTION("Copy Constructor creates independent copy") {
        CompositeTransformation copy = original;

        REQUIRE(original.transform("X") == "X_1");
        REQUIRE(copy.transform("X") == "X_1");
    }
}

TEST_CASE("CompositeTransformation: Cloning", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> vec;
    vec.push_back(std::make_unique<SuffixTransformation>("_Clone"));
    vec.push_back(std::make_unique<SuffixTransformation>("_Me"));

    CompositeTransformation original(vec);

    std::unique_ptr<TextTransformation> clonedPtr = original.clone();

    SECTION("Cloned object performs same transformations") {
        REQUIRE(clonedPtr->transform("Input") == "Input_Clone_Me");
    }

    SECTION("Cloned object is distinct from original") {
        REQUIRE(clonedPtr.get() != &original);

        auto casted = dynamic_cast<CompositeTransformation*>(clonedPtr.get());
        REQUIRE(casted != nullptr);
    }
}

TEST_CASE("CompositeTransformation: Nested Composites", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> group1_vec;
    group1_vec.push_back(std::make_unique<SuffixTransformation>("_A"));
    group1_vec.push_back(std::make_unique<SuffixTransformation>("_B"));
    auto composite1 = std::make_unique<CompositeTransformation>(group1_vec);

    std::vector<std::unique_ptr<TextTransformation>> group2_vec;
    group2_vec.push_back(std::move(composite1));
    group2_vec.push_back(std::make_unique<SuffixTransformation>("_C"));

    CompositeTransformation finalComposite(group2_vec);

    SECTION("Correctly flattens or chains nested composites") {
        REQUIRE(finalComposite.transform("Init") == "Init_A_B_C");
    }
}