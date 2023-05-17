#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <map>
#include <vector>
#include <iterator>
#include <functional>
#include <queue>
#include<unordered_set>
#include <algorithm>
using namespace std;
template<typename vertex_type, typename Distance = double>
struct Edge
{
    vertex_type id1;
    vertex_type id2;
    Distance dist;
    Edge(vertex_type id1_ = 0, vertex_type id_2 = 0, Distance distance_ = 0) : id1(id1_), id2(id_2), dist(distance_) {}
    friend std::ostream& operator<< (std::ostream& out, const Edge<vertex_type>& e)
    {
        out << "(" << e.id1 << ", " << e.id2 << "; " << e.dist << ')';
        return out;
    }
    friend std::ostream& operator<< (std::ostream& out, const std::map<int, Edge<vertex_type>>& map)
    {
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            out << it->second;
        }
        return out;
    }
};
template<>
struct Edge <std::string, double>
{
    std::string id1;
    std::string id2;
    double dist;
    Edge(std::string id1_ = "", std::string id_2 = "", double distance_ = 0) : id1(id1_), id2(id_2), dist(distance_) {}
    friend std::ostream& operator<< (std::ostream& out, const Edge<std::string>& e)
    {
        out << "(" << e.id1 << ", " << e.id2 << "; " << e.dist << ')';
        return out;
    }
    friend std::ostream& operator<< (std::ostream& out, const std::map<int, Edge<std::string>>& map)
    {
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            out << it->second;
        }
        return out;
    }
};
template<typename vertex_type, typename Distance = double>
class Graph {
private:
    
    int n;
    std::map<vertex_type, std::map<int,Edge<vertex_type>>> map_v;
    std::map<vertex_type, bool>visited;
    void walk_(const vertex_type& start_vertex, std::function<void(const vertex_type&)> action)
    {
        visited[start_vertex] = true;
        action(start_vertex);
        for (auto it1 : edges(start_vertex)) {
            vertex_type next_node = it1.id2;
            if (!visited[next_node]) {
                walk_(next_node, action);
            }
        }

    }
public:
    Graph(int n_vert = 0) : n(n_vert) {}
    friend std::ostream& operator<< (std::ostream& out, Graph<vertex_type>graph)
    {
        for (auto it = graph.map_v.begin(); it != graph.map_v.end(); ++it)
        {
            out << endl << '[' << it->first << ']' << '-' << it->second;
        }
        return out;
    }
    bool has_vertex(const vertex_type& v) const
    {
        if (n == 0) return false;
        if (map_v.count(v) != 0) return true;
        return false;
    }
    bool add_vertex(const vertex_type& v)
    {
        if (!has_vertex(v))
        {
            std::map<int, Edge<vertex_type>> mass;
            map_v[v] = mass;
            n++;
            return true;
        }
        return false;
    }
    bool remove_vertex(const vertex_type& v)
    {
        if (has_vertex(v))
        {
            map_v.erase(v);
            n--;
            for (auto it1 = map_v.begin(); it1 != map_v.end(); ++it1)
            {
                for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
                {
                    if (it2->second.id2 == v)
                    {
                        map_v[it1->first].erase(it2);
                        break;
                    }
                }
            }
            return true;
        }
        return false;
    }
    bool has_edge(const vertex_type& from, const vertex_type& to)
    {
        if (has_vertex(from) && has_vertex(to))
        {
            for (auto it : edges(from))
            {
                if (it.id2 == to) return true;
            }
        }
        return false;
    }
    bool has_edge(const Edge<vertex_type> &e)
    {
        if (has_vertex(e.id1) && has_vertex(e.id2))
        {
            for (auto it : edges(e.id1))
            {
                if (it.id2 == e.id2 && it.dist == e.dist) return true;
            }
        }
        return false;
    }
    bool add_edge(const vertex_type& from, const vertex_type& to, const Distance& d)
    {
        Edge<vertex_type> tmp(from, to, d);
        if (!has_edge(tmp))
        {
            if (has_vertex(from) && has_vertex(to))
            {
                map_v[from][map_v[from].size()] = tmp;
                return true;
            }
        }
        return false;
    }

    void Print()
    {
        for (auto it = map_v.begin(); it != map_v.end(); ++it)
        {
            cout << it->first << ':' << it->second << endl;
        }
    }
    bool remove_edge(const vertex_type& from, const vertex_type& to)
    {
        if (has_edge(from, to))
        {
            for (auto it1 = map_v[from].begin(); it1 != map_v[from].end(); ++it1)
            {
                if (it1->second.id2 == to)
                {
                    map_v[from].erase(it1);
                    return true;
                }
            }
        }
        return false;
    }
    bool remove_edge(const Edge<vertex_type>&e)
    {
        if (has_edge(e))
        {
            for (auto it1 = map_v[e.id1].begin(); it1 != map_v[e.id1].end(); ++it1)
            {
                if (it1->second.id2 == e.id2 && it1->second.dist == e.dist)
                {
                    map_v[e.id1].erase(it1);
                    return true;
                }
            }
        }
        return false;
    }
    size_t order() const
    {
        return vertices().size();
    }
    std::vector<vertex_type> vertices() const
    {
        std::vector<vertex_type> vert_mass;
        for (auto i = map_v.begin(); i != map_v.end(); ++i)
        {
            vert_mass.push_back(i->first);
        }
        return vert_mass;
    }
    std::vector<Edge<vertex_type>> edges(const vertex_type& vertex)
    {
        std::vector<Edge<vertex_type>> edge_mass;
        for (auto i = map_v[vertex].begin(); i != map_v[vertex].end(); ++i)
        {
            edge_mass.push_back(i->second);
        }
        return edge_mass;
    }
    size_t degree()
    {
        int max_edge = -1;
        for (auto i : vertices())
        {
            std::vector<Edge<vertex_type>> tmp_edges = edges(i);
            int size = tmp_edges.size();
            if (size > max_edge) 
                max_edge = size;
        }
        return max_edge;
    }
    void init()
    {
        for (auto i : vertices())
        {
            visited[i] = false;
        }
    }
    void walk(const vertex_type& start_vertex, std::function<void(const vertex_type&)> action)
    {
        init();
        walk_(start_vertex, action);
        for (auto& node : visited)
        {
            if (!node.second) 
            {
                walk_(node.first, action);
            }
        }

    }
    bool check(const vertex_type& from, const vertex_type& to)
    {
        unordered_set<vertex_type> visited;
        unordered_set<vertex_type> stack;
        stack.insert(from);
        while (!stack.empty()) {
            vertex_type current_vertex = *stack.begin();
            stack.erase(current_vertex);
            visited.insert(current_vertex);
            if (current_vertex == to) {
                return true;
            }
            for (auto& neighbor : edges(current_vertex)) {
                if (visited.count(neighbor.id2) == 0) {
                    stack.insert(neighbor.id2);
                }
            }
        }
        return false;
    }
    std::vector<vertex_type> shortest_path(const vertex_type& from, const vertex_type& to)
    {
        std::map<vertex_type, Distance> distances;
        std::map<vertex_type, vertex_type> prev;
        for (auto i : vertices()) 
        {
            distances[i] = INT_MAX;
        }
        priority_queue<pair<Distance, vertex_type>, vector<pair<Distance, vertex_type>>, greater<pair<Distance, vertex_type>>> pq;
        distances[from] = 0;
        pq.push({ 0, from });
        while (!pq.empty()) 
        {
            Distance dist = pq.top().first;
            vertex_type vertex = pq.top().second;
            pq.pop();
            if (dist > distances[vertex]) 
            {
                continue;
            }
            for (auto i : edges(vertex))
            {
                double newDist = dist + i.dist;
                if (newDist < distances[i.id2]) 
                {
                    distances[i.id2] = newDist;
                    prev[i.id2] = vertex;
                    pq.push(make_pair(newDist, i.id2));
                }
            }
        }
        vector<vertex_type> path;
        vertex_type current = to;
        while (current != from) 
        {
            path.push_back(current);
            current = prev[current];
        }
        path.push_back(from);
        std::reverse(path.begin(), path.end());
        return path;
    }
    double Get_length_path(const vertex_type&  v1, const vertex_type&  v2) 
    {
        for (auto i : edges(v1))
        {
            if (i.id2 == v2) return i.dist;
        }
    }
    vertex_type findV_task()
    {
        std::map<vertex_type, double>map_path;
        double minim = INT_MAX;
        vertex_type id_ = 0;
        for (auto i : vertices())
        {
            map_path[i] = 0;
            for (auto j : vertices())
            {
                if (i != j && check(i, j))
                {
                    std::vector<vertex_type> tmp = shortest_path(i, j);
                    for (int k = 0; k < tmp.size() - 1; k++)
                    {
                        map_path[i] += Get_length_path(tmp[k], tmp[k + 1]);
                    }
                    
                }
                if(!check(i, j))
                {
                    map_path[i] = INT_MAX;
                }
            }
        }
        for (auto i : map_path)
        {
            if (i.second < minim)
            {
                minim = i.second;
                id_ = i.first;
            }
        }
        return id_;
    }

};
void menu1()
{
    system("cls");
    cout << "1. Create a graph" << endl;
    cout << "2. Task" << endl;
    cout << "3. Finish the program" << endl;
    cout << "choice: ";
}
void menu2_1()
{
    system("cls");
    cout << "Choose data type for the vertices:" << endl;
    cout << "1. int" << endl;
    cout << "2. double" << endl;
    cout << "3. float" << endl;
    cout << "4. string" << endl;
    cout << "5. back main menu " << endl;
    cout << "choice: ";
}
void menu3_1()
{
    system("cls");
    cout << "1. Add vertice" << endl;
    cout << "2. Remove vertice" << endl;
    cout << "3. Add edge" << endl;
    cout << "4. Existence of edge" << endl;
    cout << "5. Remove edge with weight" << endl;
    cout << "6. Remove edge without weight" << endl;
    cout << "7. Degree  of gragh" << endl;
    cout << "8. Order of graph" << endl;
    cout << "9. Find the shortest path" << endl;
    cout << "10. DFS" << endl;
    cout << "11. Print graph" << endl;
    cout << "12. Back menu" << endl;
    cout << "choice: ";
}
template<typename vertex_type, typename Distance = double>
void Print(const vertex_type& val)
{
    cout << val << ' ';
}
//template<typename vertex_type, typename Distance = double>
//void Vertex_vector(const vertex_type& val, std::vector<vertex_type>vec)
//{
//    vec.push_back(val);
//}
int main()
{
    int choice = 0, ch = 0, choi = 0,choose = 0;
    double dist = 0;
    bool flag1 = true, flag2 = true, flag3 = true;
    while (flag1)
    {
        menu1();
        cin >> choice;
        if (choice == 1)
        {
            flag2 = true;
            while (flag2)
            {
                menu2_1();
                cin >> ch;
                if (ch == 1)
                {
                    Graph<int>graph;
                    flag3 = true;
                    while (flag3)
                    {
                        int v1 = 0, v2 = 0;
                        int val = 0;
                        menu3_1();
                        cin >> ch;
                        if (ch == 1)
                        {
                            system("cls");
                            cout << "value: ";
                            cin >> val;
                            if (graph.add_vertex(val)) cout << "vertex added successfully" << endl;
                            else cout << "this vertex is already in the graph" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 2)
                        {
                            system("cls");
                            cout << "value: ";
                            cin >> val;
                            if (graph.remove_vertex(val)) cout << "vertex deleted successfully" << endl;
                            else cout << "there is no such vertex in the graph" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 3)
                        {
                            system("cls");
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            cout << "weight: ";
                            cin >> dist;
                            if (graph.add_edge(v1, v2, dist)) cout << "edge added successfully" << endl;
                            else cout << "this vertex is already in the graph or some of the vertices are not in the graph" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 4)
                        {
                            system("cls");
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            cout << "weight: ";
                            cin >> dist;
                            Edge<int> e(v1, v2, dist);
                            if (graph.has_edge(e)) cout << "edge exists" << endl;
                            else cout << "edge doesn't exists" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 5)
                        {
                            system("cls");
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            cout << "weight: ";
                            cin >> dist;
                            Edge<int> e(v1, v2, dist);
                            if (graph.remove_edge(e)) cout << "edge deleted successfully" << endl;
                            else cout << "this edge doesn't exist in graph" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 6)
                        {
                            system("cls");
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            if (graph.remove_edge(v1, v2)) cout << "edge deleted successfully" << endl;
                            else cout << "this edge doesn't exist in graph" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 7)
                        {
                            system("cls");
                            cout << "degree of graph : " << graph.degree() << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 8)
                        {
                            system("cls");
                            cout << "order of graph : " << graph.order() << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 9)
                        {
                            system("cls");
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            if (graph.check(v1, v2))
                            {
                                std::vector<int> tmp = graph.shortest_path(v1, v2);
                                for (auto& i : tmp)
                                {
                                    cout << i << ' ';
                                }
                            }
                            else
                            {
                                cout << "unpossibly to go from vertex1 to vertex2" << endl;
                            }
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 10)
                        {
                            system("cls");
                            cout << "start vertex : ";
                            cin >> val;
                            graph.walk(val, Print<int>);
                            /*graph.walk(val, Vertex_vector<int>);*/
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 11)
                        {
                            system("cls");
                            cout << graph << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 12)
                        {
                            flag3 = false;
                        }
                        else
                        {
                            system("cls");
                            cout << "invalid character entered!!!!!!!    try again" << endl;
                            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                    }
                }
                else if (ch == 2)
                {
                Graph<double>graph;
                flag3 = true;
                while (flag3)
                {
                    double v1 = 0, v2 = 0;
                    double val = 0;
                    menu3_1();
                    cin >> ch;
                    if (ch == 1)
                    {
                        system("cls");
                        cout << "value: ";
                        cin >> val;
                        if (graph.add_vertex(val)) cout << "vertex added successfully" << endl;
                        else cout << "this vertex is already in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 2)
                    {
                        system("cls");
                        cout << "value: ";
                        cin >> val;
                        if (graph.remove_vertex(val)) cout << "vertex deleted successfully" << endl;
                        else cout << "there is no such vertex in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 3)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        if (graph.add_edge(v1, v2, dist)) cout << "edge added successfully" << endl;
                        else cout << "this vertex is already in the graph or some of the vertices are not in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 4)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        Edge<double> e(v1, v2, dist);
                        if (graph.has_edge(e)) cout << "edge exists" << endl;
                        else cout << "edge doesn't exists" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 5)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        Edge<double> e(v1, v2, dist);
                        if (graph.remove_edge(e)) cout << "edge deleted successfully" << endl;
                        else cout << "this edge doesn't exist in graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 6)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        if (graph.remove_edge(v1, v2)) cout << "edge deleted successfully" << endl;
                        else cout << "this edge doesn't exist in graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 7)
                    {
                        system("cls");
                        cout << "degree of graph : " << graph.degree() << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 8)
                    {
                        system("cls");
                        cout << "order of graph : " << graph.order() << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 9)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        if (graph.check(v1, v2))
                        {
                            std::vector<double> tmp = graph.shortest_path(v1, v2);
                            for (auto& i : tmp)
                            {
                                cout << i << ' ';
                            }
                        }
                        else
                        {
                            cout << "unpossibly to go from vertex1 to vertex2" << endl;
                        }
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 10)
                    {
                        system("cls");
                        cout << "start vertex : ";
                        cin >> val;
                        graph.walk(val, Print <double> );
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 11)
                    {
                        system("cls");
                        cout << graph << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 12)
                    {
                        flag3 = false;
                    }
                    else
                    {
                        system("cls");
                        cout << "invalid character entered!!!!!!!    try again" << endl;
                        cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                }
                }
                else if (ch == 3)
                {
                Graph<float>graph;
                flag3 = true;
                while (flag3)
                {
                    float v1 = 0, v2 = 0;
                    float val = 0;
                    menu3_1();
                    cin >> ch;
                    if (ch == 1)
                    {
                        system("cls");
                        cout << "value: ";
                        cin >> val;
                        if (graph.add_vertex(val)) cout << "vertex added successfully" << endl;
                        else cout << "this vertex is already in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 2)
                    {
                        system("cls");
                        cout << "value: ";
                        cin >> val;
                        if (graph.remove_vertex(val)) cout << "vertex deleted successfully" << endl;
                        else cout << "there is no such vertex in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 3)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        if (graph.add_edge(v1, v2, dist)) cout << "edge added successfully" << endl;
                        else cout << "this vertex is already in the graph or some of the vertices are not in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 4)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        Edge<float> e(v1, v2, dist);
                        if (graph.has_edge(e)) cout << "edge exists" << endl;
                        else cout << "edge doesn't exists" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 5)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        Edge<float> e(v1, v2, dist);
                        if (graph.remove_edge(e)) cout << "edge deleted successfully" << endl;
                        else cout << "this edge doesn't exist in graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 6)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        if (graph.remove_edge(v1, v2)) cout << "edge deleted successfully" << endl;
                        else cout << "this edge doesn't exist in graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 7)
                    {
                        system("cls");
                        cout << "degree of graph : " << graph.degree() << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 8)
                    {
                        system("cls");
                        cout << "order of graph : " << graph.order() << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 9)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        if (graph.check(v1, v2))
                        {
                            std::vector<float> tmp = graph.shortest_path(v1, v2);
                            for (auto& i : tmp)
                            {
                                cout << i << ' ';
                            }
                        }
                        else
                        {
                            cout << "unpossibly to go from vertex1 to vertex2" << endl;
                        }
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 10)
                    {
                        system("cls");
                        cout << "start vertex : ";
                        cin >> val;
                        graph.walk(val, Print<float>);
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 11)
                    {
                        system("cls");
                        cout << graph << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 12)
                    {
                        flag3 = false;
                    }
                    else
                    {
                        system("cls");
                        cout << "invalid character entered!!!!!!!    try again" << endl;
                        cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                }
                }
                else if (ch == 4)
                {
                Graph<std::string>graph;
                flag3 = true;
                while (flag3)
                {
                    std::string v1 = "", v2 = "";
                    std::string val = "";
                    menu3_1();
                    cin >> ch;
                    if (ch == 1)
                    {
                        system("cls");
                        cout << "value: ";
                        cin >> val;
                        if (graph.add_vertex(val)) cout << "vertex added successfully" << endl;
                        else cout << "this vertex is already in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 2)
                    {
                        system("cls");
                        cout << "value: ";
                        cin >> val;
                        if (graph.remove_vertex(val)) cout << "vertex deleted successfully" << endl;
                        else cout << "there is no such vertex in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 3)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        if (graph.add_edge(v1, v2, dist)) cout << "edge added successfully" << endl;
                        else cout << "this vertex is already in the graph or some of the vertices are not in the graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 4)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        Edge<std::string> e(v1, v2, dist);
                        if (graph.has_edge(e)) cout << "edge exists" << endl;
                        else cout << "edge doesn't exists" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 5)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        cout << "weight: ";
                        cin >> dist;
                        Edge<std::string> e(v1, v2, dist);
                        if (graph.remove_edge(e)) cout << "edge deleted successfully" << endl;
                        else cout << "this edge doesn't exist in graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 6)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        if (graph.remove_edge(v1, v2)) cout << "edge deleted successfully" << endl;
                        else cout << "this edge doesn't exist in graph" << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 7)
                    {
                        system("cls");
                        cout << "degree of graph : " << graph.degree() << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 8)
                    {
                        system("cls");
                        cout << "order of graph : " << graph.order() << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 9)
                    {
                        system("cls");
                        cout << "vertex1 : ";
                        cin >> v1;
                        cout << "vertex2 : ";
                        cin >> v2;
                        if (graph.check(v1, v2))
                        {
                            std::vector<std::string> tmp = graph.shortest_path(v1, v2);
                            for (auto& i : tmp)
                            {
                                cout << i << ' ';
                            }
                        }
                        else
                        {
                            cout << "unpossibly to go from vertex1 to vertex2" << endl;
                        }
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 10)
                    {
                        system("cls");
                        cout << "start vertex : ";
                        cin >> val;
                        graph.walk(val, Print<std::string>);
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 11)
                    {
                        system("cls");
                        cout << graph << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                    else if (ch == 12)
                    {
                        flag3 = false;
                    }
                    else
                    {
                        system("cls");
                        cout << "invalid character entered!!!!!!!    try again" << endl;
                        cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                    }
                }
                }
                else if (ch == 5)
                {
                    flag2 = false;
                }
                else
                {
                    system("cls");
                    cout << "invalid character entered!!!!!!!    try again" << endl;
                    cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag3 = true;
                }
            }
        }
        if (choice == 2)
        {
            Graph<int>graph;
            graph.add_vertex(1);
            graph.add_vertex(2);
            graph.add_vertex(3);
            graph.add_vertex(4);
            graph.add_vertex(5);
            graph.add_vertex(6);
            graph.add_edge(1, 2, 3);
            graph.add_edge(1, 4, 8);
            graph.add_edge(2, 1, 2);
            graph.add_edge(2, 5, 5);
            graph.add_edge(2, 3, 6);
            graph.add_edge(4, 6, 7);
            graph.add_edge(5, 4, 5);
            graph.add_edge(5, 3, 9);
            graph.add_edge(6, 5, 1);
            graph.add_edge(6, 2, 7);
            cout << "Point: " << graph.findV_task() << endl;
            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;
        }
        if (choice == 3) return 0;
        else if (choice != 1 && choice != 2 && choice != 3)
        {
            system("cls");
            cout << "invalid character entered!!!!!!!    try again" << endl;
            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;
        }
    }
}