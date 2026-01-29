#include "catch2/catch_all.hpp"
#include "../headers/ProxyLabel.h"
#include <iostream>

TEST_CASE("ProxyLabel: User Interaction Logic", "[ProxyLabel]") {

    std::stringstream outputBuffer;
    std::streambuf* oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

    std::stringstream inputBuffer;
    std::streambuf* oldCin = std::cin.rdbuf(inputBuffer.rdbuf());

    auto baseLabel = std::make_unique<SimpleLabel>("Original");
    ProxyLabel proxy(std::move(baseLabel));

    SECTION("First call forces user input (Initial State)") {
        inputBuffer.str("NewValue");

        std::string result = proxy.getText();

        REQUIRE(outputBuffer.str().find("Enter label's text:") != std::string::npos);
        REQUIRE(result == "NewValue");
    }

    SECTION("Subsequent calls return cached value") {
        inputBuffer.str("First");
        proxy.getText();

        inputBuffer.str("");
        outputBuffer.str("");
        std::cin.clear();

        std::string result = proxy.getText();

        REQUIRE(outputBuffer.str().empty());
        REQUIRE(result == "First");
    }

    SECTION("TimeOut triggers re-prompt (User says No)") {
        inputBuffer.str("First");
        proxy.getText();

        inputBuffer.str("");
        outputBuffer.str("");
        std::cin.clear();

        proxy.timeOut();

        inputBuffer.str("n");

        std::string result = proxy.getText();

        REQUIRE(outputBuffer.str().find("Do you want to change") != std::string::npos);
        REQUIRE(result == "First");
    }

    SECTION("TimeOut triggers re-prompt (User says Yes)") {
        inputBuffer.str("First");
        proxy.getText();

        inputBuffer.str("");
        outputBuffer.str("");
        std::cin.clear();

        proxy.timeOut();

        inputBuffer.str("y\nUpdated");

        std::string result = proxy.getText();

        REQUIRE(outputBuffer.str().find("Do you want to change") != std::string::npos);
        REQUIRE(outputBuffer.str().find("Enter label's text:") != std::string::npos);
        REQUIRE(result == "Updated");
    }

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
}

TEST_CASE("ProxyLabel: Structure and Copying", "[ProxyLabel]") {

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    std::stringstream input;
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

    auto base = std::make_unique<SimpleLabel>("Data");
    ProxyLabel original(std::move(base));

    input.str("InitData");
    original.getText();

    SECTION("Copy Constructor resets state") {

        ProxyLabel copy(original);

        input.str("");
        std::cin.clear();

        input.str("CopyData");

        std::string res = copy.getText();

        REQUIRE(res == "CopyData");
    }

    SECTION("setValue returns false") {
        REQUIRE(original.setValue("Anything") == false);
    }

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
}