#include "LabelDecorator.h"

LabelDecorator::LabelDecorator(std::unique_ptr<Label> label) : wrappedLabel(std::move(label)) {}

std::string LabelDecorator::getText() const
{
    return wrappedLabel->getText();
}

bool LabelDecorator::setValue(const std::string& string)
{
    return wrappedLabel->setValue(string);
}

LabelDecorator::LabelDecorator(const LabelDecorator& other)
{
    if (other.wrappedLabel) {
        wrappedLabel = other.wrappedLabel->clone();
    }
}