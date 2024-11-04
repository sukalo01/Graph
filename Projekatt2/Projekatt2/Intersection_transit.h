#pragma once



class Intersection_transit
{
public:
	int vehicle_now;
	int in;
	int out;
	int dist;
	Intersection_transit(int in, int out, int dist,int veh=0);
};