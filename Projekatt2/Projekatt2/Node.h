#pragma once
#include <string>

class Node
{
private:
    const std::string name;
public:
    Node() = default;
    Node(const std::string& names);
    virtual std::string Node_type()const = 0;
    virtual std::string Node_name() const;
    virtual std::string print()const = 0;
};
