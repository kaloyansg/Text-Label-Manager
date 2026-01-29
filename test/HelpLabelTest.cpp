#include "catch2/catch_all.hpp"
#include "../headers/HelpLabel.h"
#include "../headers/SimpleLabel.h"
#include "../headers/RichLabel.h"
#include "../headers/ProxyLabel.h"


//insert different labels
TEST_CASE("HelpLabel: Core Functionality", "[HelpLabel]") {

    std::string startText = "Username";
    std::string helpMsg = "Enter your username here";

    auto simple = std::make_unique<SimpleLabel>(startText);
    HelpLabel helpLabel(std::move(simple), helpMsg);

    SECTION("Delegation: getText returns wrapped label's text") {
        REQUIRE(helpLabel.getText() == startText);
    }

    SECTION("Delegation: setValue updates wrapped label") {
        helpLabel.setValue("NewUser");
        REQUIRE(helpLabel.getText() == "NewUser");
    }

    SECTION("Specific Functionality: getHelpText returns help message") {
        REQUIRE(helpLabel.getHelpText() == helpMsg);
    }
}

TEST_CASE("HelpLabel: Deep Copying (Cloning)", "[HelpLabel]") {

    HelpLabel original(std::make_unique<SimpleLabel>("Data"), "Help info");

    SECTION("Clone creates a valid independent copy") {
        std::unique_ptr<Label> copyBase = original.clone();

        REQUIRE(copyBase != nullptr);
        auto* copy = dynamic_cast<HelpLabel*>(copyBase.get());
        REQUIRE(copy != nullptr);

        REQUIRE(copy->getText() == "Data");
        REQUIRE(copy->getHelpText() == "Help info");

        original.setValue("Changed Data");

        REQUIRE(copy->getText() == "Data");
        REQUIRE(original.getText() == "Changed Data");
    }

    SECTION("Copy Constructor works correctly") {
        HelpLabel copyOfOriginal(original);

        REQUIRE(copyOfOriginal.getText() == original.getText());
        REQUIRE(copyOfOriginal.getHelpText() == original.getHelpText());
    }
}

TEST_CASE("HelpLabel: Deep Copying (Cloning) with Rich Label", "[HelpLabel]") {

    HelpLabel original(std::make_unique<RichLabel>("Data", "color", 10, "font"), "Help info");

    SECTION("Clone creates a valid independent copy") {
        std::unique_ptr<Label> copyBase = original.clone();

        REQUIRE(copyBase != nullptr);
        auto* copy = dynamic_cast<HelpLabel*>(copyBase.get());
        REQUIRE(copy != nullptr);

        REQUIRE(copy->getText() == "Data");
        REQUIRE(copy->getHelpText() == "Help info");

        original.setValue("Changed Data");

        REQUIRE(copy->getText() == "Data");
        REQUIRE(original.getText() == "Changed Data");
    }

    SECTION("Copy Constructor works correctly") {
        HelpLabel copyOfOriginal(original);

        REQUIRE(copyOfOriginal.getText() == original.getText());
        REQUIRE(copyOfOriginal.getHelpText() == original.getHelpText());
    }
}
