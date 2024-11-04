#include "Location.h"

Location::Location(std::string name) :Node(name) {}

std::string Location::Node_type() const
{
    return "Location";
}

std::string Location::Node_name() const
{
    return this->Node::Node_name();
}

std::string Location::print() const
{
    std::string result;
    result = this->Node_type();
    result += " ";
    result += this->Node_name();
    return result;
}
