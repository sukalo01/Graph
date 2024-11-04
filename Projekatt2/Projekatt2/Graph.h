#include "Node.h"
#include "Intersection.h"
#include "Location.h"
#include "Path.h"
#include "Vehicle.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include<climits>
#include<stack>
#include <iomanip>
#include<sstream>


class Graph
{
private:
    std::vector<Node*> nodes;
    std::vector<std::list<int> > neighbors;
    std::vector<Vehicle> vozila;
public:
    Graph() = default;
    void add_Node(Node* trg);
    void print();
    void add_connection(Node* from, Node* to);
    //void find(Node* trg);
    //void ispisi();
    void serialize(std::string doc);
    void deserialize(std::string doc);
    void add_connection(std::string fr, Node* to);
    void add_connection(Node* from, std::string to);
    void add_connection(std::string from, std::string to);
    void min_dist(Vehicle v, std::string from, std::string to);
    void min_time(Vehicle v, std::string from, std::string to);
    void add_vehicle(Vehicle trg);
    void print_veh();
    void list_ser(std::string doc);
    void list_deser(std::string doc);

};


void make_dis_mat(std::vector<std::vector<int> >& mat, std::vector<Node*>& temp, std::vector<std::list<int> >& neighbors, std::vector<Node*> cvorovi);
void make_time_mat(std::vector<std::vector<double> >& mat, std::vector<Node*>& temp, std::vector<std::list<int> >& neighbors,int veh_speed, std::vector<Node*> cvorovi);
template <typename T> 
std::vector<T> bellmanFord(std::vector<std::vector<T>>& graph, int src, int dest, std::vector<int>& predecessors, std::vector<Node*> temp, std::stack<int>& pathStack);