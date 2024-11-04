#pragma once 
#include "Node.h"
#include "Intersection_transit.h"
#include <string>
#include <list>
#include <set>
#include <vector>
#include <iostream>
#include <map>

class Intersection: public Node
{
private:
    int veh_limit;
    int speed;
    std::vector<Intersection_transit> transit;
    std::list<int> outputs;
    std::list<int> inputs;
    std::map<int, std::vector<int> > maps;

public:
    Intersection(std::string name, int veh_limit, int speed);
    void add_input(int other);
    virtual std::string Node_type()const override;
    virtual std::string Node_name() const override;
    void add_output(int other);
    virtual std::string  print() const override;
    void printt(std::ostream&);
    void add_transition(int in, int out, int dist);
    int size_ul()const;
    int size_iz()const;
    void ispisi();
    int size_vec() const;
    int average_speed(Intersection_transit);
    std::vector<Intersection_transit> getTransit();
    int getSpeed();
};