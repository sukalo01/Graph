#pragma once
#include <string>

class Vehicle
{
private:
	std::string name;
	int speed;

public:
	Vehicle(std::string name, int speed);
	std::string veh_name();
	int getspeed();
};