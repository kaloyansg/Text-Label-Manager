#include "catch2/catch_all.hpp"
#include "../headers/CensorTransformation.h"

TEST_CASE("CensorTransformation: Core Logic", "[CensorTransformation]") {

    SECTION("Basic Censorship") {
        CensorTransformation censor("bad"); //***

        REQUIRE(censor.transform("This is bad behavior") == "This is *** behavior");
        REQUIRE(censor.transform("bad boys bad boys") == "*** boys *** boys");
    }

    SECTION("Partial Word Matching (Substring)") {
        CensorTransformation censor("cat");

        REQUIRE(censor.transform("scatter") == "s***ter");
        REQUIRE(censor.transform("concatenation") == "con***enation");
    }

    SECTION("No Censorship Needed") {
        CensorTransformation censor("bad");
        std::string safeText = "This is good text";

        REQUIRE(censor.transform(safeText) == safeText);
    }

    SECTION("Getter Validation") {
        CensorTransformation censor("secret");
        REQUIRE(censor.getWordCensor() == "secret");
    }
}

TEST_CASE("CensorTransformation: Edge Cases", "[CensorTransformation]") {

    CensorTransformation censor("word");

    SECTION("Word at the very beginning") {
        REQUIRE(censor.transform("word up") == "**** up");
    }

    SECTION("Word at the very end") {
        REQUIRE(censor.transform("last word") == "last ****");
    }

    SECTION("String is exactly the censored word") {
        REQUIRE(censor.transform("word") == "****");
    }

    SECTION("Empty Input String") {
        REQUIRE(censor.transform("") == "");
    }
}

TEST_CASE("CensorTransformation: Cloning", "[CensorTransformation]") {
    CensorTransformation original("blockme");
    std::unique_ptr<TextTransformation> clone = original.clone();

    SECTION("Clone is not null") {
        REQUIRE(clone != nullptr);
    }

    SECTION("Clone preserves logic") {
        REQUIRE(clone->transform("Please blockme now") == "Please ******* now");
    }

    SECTION("Clone preserves state (censored word)") {
        auto* castedClone = dynamic_cast<CensorTransformation*>(clone.get());
        REQUIRE(castedClone != nullptr);
        REQUIRE(castedClone->getWordCensor() == "blockme");
    }
}