#pragma once
#include "Node.h"
#include<string>

class Location : public Node
{

public:
    Location(std::string name);
    virtual std::string Node_type()const override;
    virtual std::string Node_name()const override;
    virtual std::string print() const override;

};
