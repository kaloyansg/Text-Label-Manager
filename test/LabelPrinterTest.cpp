#include "catch2/catch_all.hpp"
#include "../headers/LabelPrinter.h"
#include "../headers/SimpleLabel.h"
#include "../headers/HelpLabel.h"
#include <iostream>

TEST_CASE("LabelPrinter: Output Verification", "[LabelPrinter]") {
    std::stringstream buffer;

    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

    SECTION("print() outputs correctly formatted text") {
        SimpleLabel label("Login Button");

        LabelPrinter::print(label);

        REQUIRE(buffer.str() == "Here is a label: Login Button\n");
    }

    SECTION("printWithHelpText() outputs label + help text") {
        SimpleLabel label("Password Field");
        HelpLabel helpLabel(label.clone(), "Must be 8 chars");

        LabelPrinter::printWithHelpText(helpLabel);

        std::string expected =
            "Here is a label: Password Field\n"
            "Some help information about this label: Must be 8 chars\n";

        REQUIRE(buffer.str() == expected);
    }

    std::cout.rdbuf(oldCoutBuffer);
}