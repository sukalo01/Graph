#include "Vehicle.h"

Vehicle::Vehicle(std::string name, int speed):name(name),speed(speed)
{
}

std::string Vehicle::veh_name()
{
	return this->name;
}

int Vehicle::getspeed()
{
	return this->speed;
}
