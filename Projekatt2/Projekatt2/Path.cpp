#include "Path.h"

Path::Path(const std::string& name, int dist, int speed, int num) :Node(name), distance(dist), speed(speed), num_vehicles(num) {}

std::string Path::Node_type() const
{
    return "Path";
}

std::string Path::Node_name() const
{
    return this->Node::Node_name();
}

std::string Path::print() const
{
    std::string result;
    result = this->Node_type();
    result += " ";
    result += this->Node_name();
    result += " ";
    result += std::to_string(distance);
    result += " ";
    result += std::to_string(speed);
    result += " ";
    result += std::to_string(num_vehicles);
    return result;
}

int Path::get_dis()
{
    return this->distance;
}

int Path::get_speed()
{
    return this->speed;
}
