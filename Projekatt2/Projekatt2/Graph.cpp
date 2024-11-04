#include "Graph.h"


void Graph::add_Node(Node* trg)
{
    this->nodes.push_back(trg);
    std::list<int> l1;
    this->neighbors.push_back(l1);

}

void Graph::print()
{
    for ( const auto value : nodes)
    {
        std::cout << value->Node_type() << std::endl;
    }
}

void Graph::add_connection(Node* from, Node* to)
{
    if (from->Node_type() != to->Node_type())
    {
        auto iter_from = std::find(nodes.begin(), nodes.end(), from);
        auto iter_to = std::find(nodes.begin(), nodes.end(), to);
        std::ptrdiff_t ito = std::distance(nodes.begin(), iter_to);
        int in_to = static_cast<int>(ito);
        std::ptrdiff_t inf = std::distance(nodes.begin(), iter_from);
        int in_from = static_cast<int>(inf);
        
        neighbors[in_from].push_back(in_to);
        neighbors[in_from].sort();
        if (from->Node_type() == "Intersection")
        {
            ((Intersection*)from)->add_output(in_to);
        }
        else if (to->Node_type() == "Intersection")
        {
            ((Intersection*)to)->add_input(in_from);
        }
    }
    else
    {
        std::cout << "Nema smisla dodati dva cvora tipa " << from->Node_type() << " jedan kraj drugog";
    }
}



/*void Graph::find(Node* trg)
{
    auto it = std::find(nodes.begin(), nodes.end(), trg);
    std::cout << (*it)->Node_name();
}*/

/*void Graph::ispisi()
{
    int i = 0;
    for (std::list<int> value : neighbors)
    {

        std::cout << i << std::endl;
        for (auto val : value)
            std::cout << val;
        std::cout << std::endl;
        i++;
    }
}*/

void Graph::serialize(std::string doc)
{
    std::ofstream file(doc);
    if (file.is_open())
    {

        file << this->nodes.size() << std::endl;
        for (auto value : nodes)
        {
            file << value->print() << std::endl;
        }
        std::vector<std::vector<int> > mat(this->nodes.size(), std::vector<int>(this->nodes.size(), 0));
        for (int nod = 0; nod < nodes.size(); nod++)
            for (auto value : neighbors[nod])
                mat[nod][value] = 1;
        for (int i = 0; i < this->nodes.size(); ++i)
        {
            for (int j = 0; j < this->nodes.size(); ++j) {
                file << mat[i][j] << " ";
            }
            file << std::endl;
        }
        for (auto value : nodes)
        {
            if (value->Node_type() == "Intersection")
            {
                file << value->Node_name()<<" "<<((Intersection*)value)->size_vec() << std::endl;
                ((Intersection*)value)->printt(file);

            }
        }
        file.close();
    }

}

void Graph::deserialize(std::string doc)
{
    std::ifstream file(doc);
    if (file.is_open())
    {
        std::string linija;
        std::getline(file, linija);
        int n;
        n = stoi(linija);
        
        for (int j = 0; j < n; j++)
        {
            char name[20] = "";

            file.get(name, 20, ' ');
            std::string st(name);
            
            if (st == "Location")
            {
                char c;
                file.get(c);
                std::getline(file, linija);
                
                Location* loc = new Location(linija);
                this->add_Node(loc);
                loc = nullptr;
            }
            else if (st == "Path")
            {
                char c;
                file.get(c);
                file.get(name, 15, ' ');
                std::string a(name);
                file.get(c);
                int duz;
                file >> duz;
                file.get(c);
                int speed;
                file >> speed;
                file.get(c);
                int veh;
                file >> veh;
                Path* p = new Path(a, duz, speed, veh);
                this->add_Node(p);
                std::getline(file, linija);

            }
            else if (st == "Intersection")
            {
                char c;
                file.get(c);
                file.get(name, 15, ' ');
                std::string a(name);
                file.get(c);
                int veh_limit;
                file >> veh_limit;
                file.get(c);
                int speed;
                file >> speed;
                Intersection* p = new Intersection(a, veh_limit, speed);
                this->add_Node(p);
                std::getline(file, linija);

            }

        }
        std::vector<std::vector<int> > mat(n, std::vector<int>(n, 0));
        
        char c;
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                file >> mat[i][j];
                file.get(c);
            }
            std::getline(file, linija);
        }
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == 1)
                    this->neighbors[i].push_back(j);
            }
        }
        int br_inter = 0;
        for (auto value : nodes)
        {
            if (value->Node_type() == "Intersection")
            {
                br_inter++;
                auto iter = std::find(nodes.begin(), nodes.end(), value);
                std::ptrdiff_t itt = std::distance(nodes.begin(), iter);
                int it = static_cast<int> (itt);
                for (int j = 0; j < n; j++)
                {
                    if (mat[it][j] == 1) ((Intersection*)value)->add_output(j);
                    if (mat[j][it] == 1) ((Intersection*)value)->add_input(j);
                }

            }
        }
        for (int i = 0; i < br_inter; i++)
        {

            char name[20] = "";

            file.get(name, 20, ' ');
            std::string st(name);
            file.get(c);
            int lim;
            file >> lim;
            std::getline(file, linija);
            for (auto value : nodes)
            {
                if (value->Node_name() == st)
                {
                    
                    for(int j=0;j<lim;j++)
                    {
                        int in;
                        int out;
                        int dist;
                        file >> in;
                        file.get(c);
                        file >> out;
                        file.get(c);
                        file >> dist;
                        ((Intersection*)value)->add_transition(in,out, dist);
                        std::getline(file, linija);
                        
                    }
                }
            }
        }
        file.close();
    }

}

void Graph::add_connection(std::string fr, Node* to)
{
    int from;

    for (auto value : nodes)
    {
        if (value->Node_name() == fr)
        {
            auto iter_from = std::find(nodes.begin(), nodes.end(), value);
            std::ptrdiff_t frr = std::distance(nodes.begin(), iter_from);
            from = static_cast<int>(frr);


            auto iter_to = std::find(nodes.begin(), nodes.end(), to);
            std::ptrdiff_t inet = std::distance(nodes.begin(), iter_to);
            int in_to = static_cast<int>(inet);
            
            neighbors[from].push_back(in_to);
            neighbors[from].sort();
            if (value->Node_type() == "Intersection")
            {
                ((Intersection*)value)->add_output(in_to);
            }
            else if (to->Node_type() == "Intersection")
            {
                ((Intersection*)to)->add_input(from);
            }
        }
    }

}

void Graph::add_connection(Node* from, std::string to)
{
    int in_to;

    for (auto value : nodes)
    {
        if (value->Node_name() == to)
        {
            auto iter_to = std::find(nodes.begin(), nodes.end(), value);
            std::ptrdiff_t itt = std::distance(nodes.begin(), iter_to);
            in_to = static_cast<int>(itt);


            auto iter_from = std::find(nodes.begin(), nodes.end(), from);
            std::ptrdiff_t inf = std::distance(nodes.begin(), iter_from);
            int in_from = static_cast<int>(inf);

            //std::cout << in_from;
            neighbors[in_from].push_back(in_to);
            neighbors[in_from].sort();
            if (from->Node_type() == "Intersection")
            {
                ((Intersection*)from)->add_output(in_to);
            }
            else if (value->Node_type() == "Intersection")
            {
                ((Intersection*)value)->add_input(in_from);
            }
        }
    }

}

void Graph::add_connection(std::string from, std::string to)
{
    for (auto value_from : nodes)
    {
        if (value_from->Node_name() == from)
        {
            for (auto value_to : nodes)
            {
                if (value_to->Node_name() == to)
                {
                    auto iter_to = std::find(nodes.begin(), nodes.end(), value_to);
                    std::ptrdiff_t ine = std::distance(nodes.begin(), iter_to);
                    int in_to = static_cast<int>(ine);
                    auto iter_from = std::find(nodes.begin(), nodes.end(), value_from);
                    std::ptrdiff_t ife = std::distance(nodes.begin(), iter_from);
                    int in_from = static_cast<int>(ife);
                    neighbors[in_from].push_back(in_to);
                    neighbors[in_from].sort();
                    if (value_from->Node_type() == "Intersection")
                    {
                        ((Intersection*)value_from)->add_output(in_to);
                    }
                    else if (value_to->Node_type() == "Intersection")
                    {
                        ((Intersection*)value_to)->add_input(in_from);
                    }
                }
            }
        }
    }

}

void Graph::min_dist(Vehicle v, std::string from, std::string to)
{
    std::vector<Node*> temp = nodes;
    std::vector<std::vector<int> > mat(this->nodes.size(), std::vector<int>(this->nodes.size(), 0));
    make_dis_mat(mat, temp, this->neighbors,this->nodes);
    
    int m=0;
    for (auto val : temp)
    {
        if (val->Node_name() == from)
        {
            auto iterr = std::find(temp.begin(), temp.end(), val);
            std::ptrdiff_t me = std::distance(temp.begin(), iterr);
            m = static_cast<int>(me);
        }
    }
    int n=0;
    for (auto val : temp)
    {
        if (val->Node_name() == to)
        {
            auto iterr = std::find(temp.begin(), temp.end(), val);
            std::ptrdiff_t ne = std::distance(temp.begin(), iterr);
            n = static_cast<int>(ne);
        }
    }
    std::vector<int> predecessors(mat.size(),-1);
    std::stack<int> pathStack;
    std::vector<int> najkraca = bellmanFord(mat, m, n, predecessors, temp,pathStack);
    std::vector<int> a = {};
    if (najkraca != a)
    {
        int current = n;
        while (current != m) {
            pathStack.push(current);
            current = predecessors[current];
        }
        pathStack.push(m);

        // Ispis putanje
        std::cout << "Shortest path from node " << temp[m]->Node_name() << " to node " << temp[n]->Node_name() << " is: ";
        while (!pathStack.empty()) {
            std::cout << temp[pathStack.top()]->Node_name() << " ";
            pathStack.pop();
        }
        std::cout << std::endl << "Distance: " << najkraca[n] << "km" << std::endl;
    }
    else
        std::cout << "There is no path from node " << temp[m]->Node_name() << " to node " << temp[n]->Node_name() << "\n";
    
    std::cout << std::endl;
}

void Graph::min_time(Vehicle v, std::string from, std::string to)
{
    std::vector<Node*> temp = nodes;
    std::vector<std::vector<double> > mat(this->nodes.size(), std::vector<double>(this->nodes.size(), 0));
    make_time_mat(mat, temp, this->neighbors,v.getspeed(),this->nodes);

    int m = 0;
    for (auto val : temp)
    {
        if (val->Node_name() == from)
        {
            auto iterr = std::find(temp.begin(), temp.end(), val);
            std::ptrdiff_t me = std::distance(temp.begin(), iterr);
            m = static_cast<int>(me);
        }
    }
    int n = 0;
    for (auto val : temp)
    {
        if (val->Node_name() == to)
        {
            auto iterr = std::find(temp.begin(), temp.end(), val);
            std::ptrdiff_t ne = std::distance(temp.begin(), iterr);
            n = static_cast<int>(ne);
        }
    }
    std::vector<int> predecessors(mat.size(), -1);
    std::stack<int> pathStack;
    std::vector<double> najkraca = bellmanFord(mat, m, n, predecessors, temp, pathStack);
    std::vector<double> a = {};
    if (najkraca != a)
    {
        int current = n;
        while (current != m) {
            pathStack.push(current);
            current = predecessors[current];
        }
        pathStack.push(m);

        // Ispis putanje
        std::cout << "The fastest path from node " << temp[m]->Node_name() << " to node " << temp[n]->Node_name() << " is: ";
        while (!pathStack.empty()) {
            std::cout << temp[pathStack.top()]->Node_name() << " ";
            pathStack.pop();
        }
        
        int sec = (najkraca[n] - (int)najkraca[n])*60;
        std::cout << std::endl << "Time: " << (int)najkraca[n] << " hours and " <<sec <<" minutes"<< std::endl;
        
    }
    else
        std::cout << "There is no path from node " << temp[m]->Node_name() << " to node " << temp[n]->Node_name() << "\n";
    std::cout << std::endl;

}

void Graph::add_vehicle(Vehicle trg)
{
    vozila.push_back(trg);
}

void Graph::print_veh()
{
    for (Vehicle value : vozila)
    {
        std::cout << value.veh_name() << " " << value.getspeed() << std::endl;
    }
}




template <typename T> std::vector<T> bellmanFord(std::vector<std::vector<T>>& graph, int src, int dest, std::vector<int>& predecessors, std::vector<Node*> temp,std::stack<int>& pathStack) {
    int V = graph.size();
    std::vector<T> distance(V, INT_MAX);
    distance[src] = 0;

    for (int i = 1; i <= V - 1; ++i) 
    {
        for (int u = 0; u < V; ++u) 
        {
            for (int v = 0; v < V; ++v) 
            {
                if (graph[u][v] != INT_MAX && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) 
                {
                    distance[v] = distance[u] + graph[u][v];
                    predecessors[v] = u;  // Cuvamo prethodnika za rekonstrukciju puta
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) 
    {
        for (int v = 0; v < V; ++v) 
        {
            if (graph[u][v] != INT_MAX && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) 
            {
                std::cout << "Graf sadrzi negativan ciklus\n";
                return {};
            }
        }
    }
    if (distance[dest] == INT_MAX) 
    {
        return {};
    }
    
    

    return distance;
}

void make_dis_mat(std::vector<std::vector<int>>& mat, std::vector<Node*>& temp, std::vector<std::list<int> >& neighbors,std::vector<Node*> cvorovi)
{
    for (int nod = 0; nod < temp.size(); nod++)
        for (auto value : neighbors[nod])
            mat[nod][value] = 1;
    
    for (int i=0;i<temp.size();i++)
    {
        auto value = temp[i];
        if (value->Node_type() == "Intersection")
        {
            auto iter = std::find(temp.begin(), temp.end(), value);

            std::ptrdiff_t de = std::distance(temp.begin(), iter);
            int d = static_cast<int>(de);          
            std::vector<Intersection_transit> temp_tr = ((Intersection*)value)->getTransit();
            for (Intersection_transit vvalue : temp_tr)
            {

                auto it_in = std::find(temp.begin(), temp.end(), cvorovi[vvalue.in]);

                auto it_out = std::find(temp.begin(), temp.end(), cvorovi[vvalue.out]);
                int int_it_in = std::distance(temp.begin(), it_in);
                int int_it_out = std::distance(temp.begin(), it_out);
                
                mat[int_it_in][int_it_out] = vvalue.dist;
            }

            auto tt = temp.end();
            if (iter != temp.end() - 1)
            {
                mat.erase(mat.begin() + d);
                for (int i = 0; i < mat.size(); ++i)
                {

                    mat[i].erase(mat[i].begin() + d);

                }
                temp.erase(iter);
                
            }
            else
            {
                mat.pop_back();
                for (int i = 0; i < temp.size() - 1; ++i)
                {

                    mat[i].pop_back();

                }
                temp.pop_back();
                break;
                

            }
            if (temp[d]->Node_type() == "Intersection")
                --i;
            
        }
            
    }
    
    for (auto valuer : temp)
    {
        if (valuer->Node_type() == "Path")
        {
            auto it = std::find(temp.begin(), temp.end(), valuer);
            int d = std::distance(temp.begin(), it);
            for (int i = 0; i < temp.size(); i++)
            {


                if (mat[i][d] > 0)
                {
                    if (mat[i][d] == 1)
                        mat[i][d] = ((Path*)valuer)->get_dis() / 2;
                    else
                        mat[i][d] += ((Path*)valuer)->get_dis() / 2;
                }
                if (mat[d][i] > 0)
                {
                    if (mat[d][i] == 1)
                        mat[d][i] = ((Path*)valuer)->get_dis() / 2;
                    else
                        mat[d][i] += ((Path*)valuer)->get_dis() / 2;
                }
            }
        }
    }
    /*for (int i = 0; i < temp.size(); i++)
    {
        std::cout << i << " " << temp[i]->Node_name() << std::endl;
    }*/
    
    
    for (int j = 0; j < temp.size(); j++)
    {
        for (int k = 0; k < temp.size(); k++)
            if (mat[j][k] == 0) mat[j][k] = INT_MAX;

    }
    
    
}

void make_time_mat(std::vector<std::vector<double>>& mat, std::vector<Node*>& temp, std::vector<std::list<int>>& neighbors, int veh_speed, std::vector<Node*>cvorovi)
{
    for (int nod = 0; nod < temp.size(); nod++)
        for (auto value : neighbors[nod])
            mat[nod][value] = 1;
    for (int i=0;i<temp.size();i++)
    {
        auto value = temp[i];
        if (value->Node_type() == "Intersection")
        {
            auto iter = std::find(temp.begin(), temp.end(), value);

            int d = std::distance(temp.begin(), iter);

            std::vector<Intersection_transit> temp_tr = ((Intersection*)value)->getTransit();
            for (Intersection_transit vvalue : temp_tr)
            {
                auto it_in = std::find(temp.begin(), temp.end(), cvorovi[vvalue.in]);
                auto it_out = std::find(temp.begin(), temp.end(), cvorovi[vvalue.out]);
                int int_it_in = std::distance(temp.begin(), it_in);
                int int_it_out = std::distance(temp.begin(), it_out);
                double k = ((Intersection*)value)->getSpeed();
                if (k < veh_speed)
                {
                    mat[int_it_in][int_it_out] = ((double)vvalue.dist /  k);
                    
                }
                else
                {
                    mat[int_it_in][int_it_out] = ((double)vvalue.dist /  veh_speed);
                    
                }
            }

            
            if (iter != temp.end() - 1)
            {
                mat.erase(mat.begin() + d);
                for (int i = 0; i < mat.size(); ++i)
                {

                    mat[i].erase(mat[i].begin() + d);

                }
                temp.erase(iter);
            }
            else
            {
                mat.pop_back();
                for (int i = 0; i < temp.size() - 1; ++i)
                {

                    mat[i].pop_back();

                }
                temp.pop_back();
                break;

            }
            if (temp[d]->Node_type() == "Intersection")
                --i;


        }
        
        
    }
    
    for (auto valuer : temp)
    {
        if (valuer->Node_type() == "Path")
        {
            auto it = std::find(temp.begin(), temp.end(), valuer);
            std::ptrdiff_t dist = std::distance(temp.begin(), it);
            int d = static_cast<int>(dist);
            double s = ((Path*)valuer)->get_speed();
            double f = ((Path*)valuer)->get_dis();
            for (int i = 0; i < temp.size(); i++)
            {


                if (mat[i][d] > 0)
                {
                    if (mat[i][d] == 1)
                    {
                        if (s < veh_speed)
                            mat[i][d] = ((f/2)/s) ;
                        else
                            mat[i][d] = ((f/2)/(double)veh_speed );
                    }
                    else
                    {
                        if(s<veh_speed)
                            mat[i][d] += ((f / 2) / s);
                        else
                            mat[i][d] += ((f / 2) / (double)veh_speed);

                    }
                }
                if (mat[d][i] > 0)
                {
                    if (mat[d][i] == 1)
                    {
                        if(s<veh_speed)
                            mat[d][i] = ((f / 2) / s);
                        else
                            mat[d][i] = ((f / 2) / (double)veh_speed);
                    }
                    else
                    {
                        if(s<veh_speed)
                            mat[d][i] += ((f / 2) / s);
                        else
                            mat[d][i] += ((f / 2) / (double)veh_speed);

                    }
                }
            }
        }
    }
    /*for (int i = 0; i < temp.size(); i++)
    {
        std::cout << i << " " << temp[i]->Node_name() << std::endl;
    }*/
    
    for (int j = 0; j < temp.size(); j++)
    {
        for (int k = 0; k < temp.size(); k++)
            if (mat[j][k] == 0) mat[j][k] = INT_MAX;

    }
    
}


void Graph::list_ser(std::string doc)
{
    std::ofstream file(doc);
    if (file.is_open())
    {

        file << this->nodes.size() << std::endl;
        for (auto value : nodes)
        {
            file << value->print() << std::endl;
        }
        
        for (int i = 0; i < this->nodes.size(); ++i)
        {
            std::stack<int> temp;
            file << i << " ";
            int k = this->neighbors[i].size();
            for (int j = 0; j < k; ++j) {
                file << neighbors[i].front() << " ";
                temp.push(neighbors[i].front());
                neighbors[i].pop_front();
            }
            while (!temp.empty())
            {
                add_connection(nodes[i]->Node_name(), nodes[temp.top()]);
                temp.pop();
            }
            file << std::endl;
        }
        for (auto value : nodes)
        {
            if (value->Node_type() == "Intersection")
            {
                file << value->Node_name() << " " << ((Intersection*)value)->size_vec() << std::endl;
                ((Intersection*)value)->printt(file);

            }
        }
        file.close();
    }
}

void Graph::list_deser(std::string doc)
{
    std::ifstream file(doc);
    if (file.is_open())
    {
        std::string linija;
        std::getline(file, linija);
        int n;
        n = stoi(linija);

        for (int j = 0; j < n; j++)
        {
            char name[20] = "";

            file.get(name, 20, ' ');
            std::string st(name);

            if (st == "Location")
            {
                char c;
                file.get(c);
                std::getline(file, linija);

                Location* loc = new Location(linija);
                this->add_Node(loc);
                loc = nullptr;
            }
            else if (st == "Path")
            {
                char c;
                file.get(c);
                file.get(name, 15, ' ');
                std::string a(name);
                file.get(c);
                int duz;
                file >> duz;
                file.get(c);
                int speed;
                file >> speed;
                file.get(c);
                int veh;
                file >> veh;
                Path* p = new Path(a, duz, speed, veh);
                this->add_Node(p);
                std::getline(file, linija);

            }
            else if (st == "Intersection")
            {
                char c;
                file.get(c);
                file.get(name, 15, ' ');
                std::string a(name);
                file.get(c);
                int veh_limit;
                file >> veh_limit;
                file.get(c);
                int speed;
                file >> speed;
                Intersection* p = new Intersection(a, veh_limit, speed);
                this->add_Node(p);
                std::getline(file, linija);

            }

        }
        std::vector<std::vector<int> > mat(n, std::vector<int>(n, 0));

        char c;

       

        for (int i = 0; i < n; i++)
        {
            
            int o;
            file >> o;
            //int v;
            std::getline(file, linija);
            std::istringstream iss(linija);
            
            int value;
            while (iss >> value)
            {
                this->add_connection(nodes[o]->Node_name(), nodes[value]->Node_name());
            }
            
            
        }
        int br_inter = 0;
        for (auto value : nodes)
        {
            if (value->Node_type() == "Intersection")
            {
                br_inter++;
                auto iter = std::find(nodes.begin(), nodes.end(), value);
                std::ptrdiff_t itt = std::distance(nodes.begin(), iter);
                int it = static_cast<int> (itt);
                for (int j = 0; j < n; j++)
                {
                    if (mat[it][j] == 1) ((Intersection*)value)->add_output(j);
                    if (mat[j][it] == 1) ((Intersection*)value)->add_input(j);
                }

            }
        }
        for (int i = 0; i < br_inter; i++)
        {

            char name[20] = "";

            file.get(name, 20, ' ');
            std::string st(name);
            file.get(c);
            int lim;
            file >> lim;
            std::getline(file, linija);
            for (auto value : nodes)
            {
                if (value->Node_name() == st)
                {

                    for (int j = 0; j < lim; j++)
                    {
                        int in;
                        int out;
                        int dist;
                        file >> in;
                        file.get(c);
                        file >> out;
                        file.get(c);
                        file >> dist;
                        ((Intersection*)value)->add_transition(in, out, dist);
                        std::getline(file, linija);

                    }
                }
            }
        }
        file.close();
    }

}
