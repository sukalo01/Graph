#pragma once 
#include "Node.h"

class Path : public Node
{
private:
    int distance;
    int speed;
    int num_vehicles;

public:
    Path(const std::string& name, int dist, int speed, int num);
    virtual std::string Node_type()const override;
    virtual std::string Node_name() const override;
    virtual std::string print()const override;
    int get_dis();
    int get_speed();
};
