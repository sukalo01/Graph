#include "Intersection.h"




Intersection::Intersection(std::string name, int veh_limit, int speed) :Node(name),veh_limit(veh_limit),speed(speed)
{
}

void Intersection::add_input(int other)
{
    this->inputs.push_back(other);
    std::vector<int> a;
    this->maps[other] = a;
}

std::string Intersection::Node_type() const
{
    return "Intersection";
}

std::string Intersection::Node_name() const
{
    return this->Node::Node_name();
}

void Intersection::add_output(int other)
{
    this->outputs.push_back(other);
}

std::string Intersection::print() const
{
    std::string result;
    result = this->Node_type();
    result += " ";
    result += this->Node_name();
    result += " ";
    result += std::to_string(veh_limit);
    result += " ";
    result += std::to_string(speed);
    return result;
}

void Intersection::printt(std::ostream& os)
{
    for (auto& value : transit)
    {
        os << value.in << " " << value.out << " " << value.dist << std::endl;
    }

}


void Intersection::add_transition(int in, int out, int dist)
{
    auto it_in = std::find(inputs.begin(), inputs.end(), in);
    auto it_out = std::find(outputs.begin(), outputs.end(), out);
    if (it_in == inputs.end())
    {
        std::cout << "NEMA ulaza";

    }
    else if (it_out == outputs.end())
    {
        std::cout << "NEMA izlaza";
    }
    else
    {
        this->maps[in].push_back(out);
        std::set<int> uniqueSet(maps[in].begin(), maps[in].end());

        maps[in].assign(uniqueSet.begin(), uniqueSet.end());
        transit.push_back(Intersection_transit(in, out, dist));
    }
}

int Intersection::size_ul() const
{
    return this->inputs.size();
}

int Intersection::size_iz() const
{
    return this->outputs.size();
}

void Intersection::ispisi()
{
    for (const auto& value : transit)
    {
        std::cout << value.in << " " << value.out << " " << value.dist << std::endl;
    }
}

int Intersection::size_vec() const
{
    return this->transit.size();
}

int Intersection::average_speed(Intersection_transit tr)
{
    return speed * (1 - (tr.vehicle_now / veh_limit));
}

std::vector<Intersection_transit> Intersection::getTransit()
{
    return this->transit;
}

int Intersection::getSpeed()
{
    return this->speed;
}
