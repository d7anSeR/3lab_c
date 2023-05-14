//проверка вершины +
//добавление вершины +
//удаление вершины +
//2 проверки ребра +
// добаление ребра +
//2удаления ребра +
//дейстры +
//обход в глубину +
//вернуть вершины+
//получение всех ребер выходящих из вершины+
//порядок+
//степень+
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
using namespace std;
template<typename vertex_type, typename Distance = double>
class Graph {
private:
    struct Edge 
    {
        vertex_type id1;
        vertex_type id2;
        Distance dist;
        Edge(vertex_type id1_ = 0,vertex_type id_2 = 0, Distance distance_ = 0) : id1(id1_), id2(id_2), dist(distance_){}
    };
    int n;
    std::map<vertex_type, std::map<int,Edge>> map_v;
    std::map<vertex_type, bool>visited;
    void walk_(const vertex_type& start_vertex, std::function<void(const vertex_type&)> action)
    {
        visited[start_vertex] = true;
        action(start_vertex);
        for (auto it1 = map_v[start_vertex].begin(); it1 != map_v[start_vertex].end(); ++it1) {
            int next_node = it1->second.id2;
            if (!visited[next_node]) {
                walk_(next_node);
            }
        }

    }
public:
    Graph(int n_vert = 0) : n(n_vert) {}
    friend std::ostream& operator<< (std::ostream& out, const Edge& e)
    {
        out << "-(" << e.id1 << ", " << e.id2 << "; " << e.dist << ')';
        return out;
    }
    friend std::ostream& operator<< (std::ostream& out, const std::map<int, Edge>& map)
    {
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            out << it->first << ':' << it->second ;
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
            std::map<int, Edge> mass;
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
            for (auto it = map_v[from].begin(); it != map_v[from].end(); ++it)
            {
                if (it->second.id2 == to) return true;
            }
        }
        return false;
    }
    bool has_edge(const vertex_type& from, const vertex_type& to, const Distance& dist)
    {
        if (has_vertex(from) && has_vertex(to))
        {
            for (auto it = map_v[from].begin(); it != map_v[from].end(); ++it)
            {
                if (it->second.id2 == to && it->second.dist == dist) return true;
            }
        }
        return false;
    }
    bool add_edge(const vertex_type& from, const vertex_type& to, const Distance& d)
    {
        Edge tmp(from, to, d);
        if (!has_edge(tmp))
        {
            if (has_vertex(from) && has_vertex(to))
            {
                auto it = map_v[from].begin();
                int n_map = 0;
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
    bool remove_edge(const vertex_type& from, const vertex_type& to, const Distance& dist)
    {
        if (has_edge(from, to, dist))
        {
            for (auto it1 = map_v[from].begin(); it1 != map_v[from].end(); ++it1)
            {
                if (it1->second.id2 == to && it1->second.dist == dist)
                {
                    map_v[from].erase(it1);
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
        for (auto it1 = map_v.begin(); it1 != map_v.end(); ++it1)
        {
            vert_mass.push_back(it1->first);
        }
        return vert_mass;
    }
    std::vector<Edge> edges(const vertex_type& vertex)
    {
        if (!has_vertex(vertex)) return NULL;
        std::vector<Edge> edge_mass;
        for (auto it1 = map_v[vertes].begin(); it1 != map_v.end(); ++it1)
        {
            edge_mass.push_back(it1->second);
        }
        return edge_mass;
    }
    size_t degree() const
    {
        size_t max_edge = -1;
        for (auto it1 = map_v[vertes].begin(); it1 != map_v.end(); ++it1)
        {
            std::vector<Edge> tmp_edges = edges(it1->first);
            if (tmp_edges.size() > max_edge) max_edge = tmp_edges.size();
        }
        return max_edge;
    }
    void init()
    {
        for (auto it1 = map_v.begin(); it1 != map_v.end(); ++it1)
        {
            visited[it1->first] = false;
        }
    }
    void walk(const vertex_type& start_vertex, std::function<void(const vertex_type&)> action)
    {
        init();
        /*for (auto& node : map_v) 
        {
            if (node.first == start_vertex && !visited[node.first]) {
                walk_(node.first);
            }
        }*/
        walk_(start_vertex);
        cout << endl;
        for (auto& node : visited)
        {
            if (!node.second) 
            {
                walk_(node.first);
            }
        }

    }
    size_t check_path()
    {
        std::map<vertex_type, Distance> distances;
        std::map<vertex_type, vertex_type> prev;
        for (auto it = map_v.begin(); it != map_v.end(); ++it)
        {
            distances[it->first] = INT_MAX;
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
            for (auto it = map_v[vertex].begin(); it != map_v[vertex].end(); ++it)
            {
                double newDist = dist + it->second.dist;
                if (newDist < distances[it->second.id2])
                {
                    distances[it->second.id2] = newDist;
                    prev[it->second.id2] = vertex;
                    pq.push(make_pair(newDist, it->second.id2));
                }
            }
        }
    }
    std::vector<vertex_type> shortest_path(const vertex_type& from, const vertex_type& to)
    {
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
           /* for (auto it1 = map_v.begin(); it1 != map_v.end(); ++it1)
            {
                if (it1->first == vertex)
                {
                    for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
                    {
                        double newDist = dist + it2->second.dist;
                        if (newDist < distances[it2->second.id2]) {
                            distances[it2->second.id2] = newDist;
                            pq.push({ newDist, it2->second.id2 });
                        }
                    }
                }
                break;
            }*/
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
    cout << "3. char" << endl;
    cout << "4. float" << endl;
    cout << "5. back main menu " << endl;
    cout << "choice: ";
}
void menu3_1()
{
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
    cout << "choice: ";
}
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
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            cout << "weight: ";
                            cin >> dist;
                            if (graph.has_edge(v1, v2)) cout << "edge exists" << endl;
                            else cout << "edge doesn't exists" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 5)
                        {
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            cout << "weight: ";
                            cin >> dist;
                            if (graph.remove_edge(v1, v2, dist)) cout << "edge deleted successfully" << endl;
                            else cout << "this edge doesn't exist in graph" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 6)
                        {
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
                            cout << "degree of graph : " << graph.degree() << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 8)
                        {
                            cout << "order of graph : " << graph.order() << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 9)
                        {
                            cout << "vertex1 : ";
                            cin >> v1;
                            cout << "vertex2 : ";
                            cin >> v2;
                            if (graph.shortest_path(v1, v2) != NULL) cout << "edge deleted successfully" << endl;
                            else cout << "this edge doesn't exist in graph" << endl;
                            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = 0;
                            choi = _getch();
                            if (choi == 8) flag3 = true;
                        }
                        else if (ch == 10)
                        {
                        cout << "order of graph : " << graph.order() << endl;
                        cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                        choi = 0;
                        choi = _getch();
                        if (choi == 8) flag3 = true;
                        }
                        else
                        {
                            cout << "invalid character entered!!!!!!!    try again" << endl;
                            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                            choi = _getch();
                            if (choi == 8) flag2 = true;
                        }
                    }

                    
                }
                else if (ch == 2)
                {
                    cout << "value: ";
                    cin >> val;
                    if (head.erase(val)) cout << "value deleted successfully" << endl;
                    else cout << "there is no such value in the tree" << endl;
                    cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
                else if (ch == 3)
                {
                    head.print();
                    cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
                else if (ch == 4)
                {
                    cout << "value: ";
                    cin >> val;
                    if (head.contains(val)) cout << "this element is present in the tree" << endl;
                    else cout << "this element is not present in the tree" << endl;
                    cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
                else if (ch == 5)
                {
                    flag2 = false;
                }
                else
                {
                    cout << "invalid character entered!!!!!!!    try again" << endl;
                    cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
            }
        }
        if (choice == 2)
        {
            fill_tree(1000, 100);
            fill_tree(10000, 100);
            fill_tree(100000, 100);
            cout << endl;
            fill_vector(1000, 100);
            fill_vector(10000, 100);
            fill_vector(100000, 100);
            cout << endl;
            cout << endl;
            contains_tree(1000, 1000);
            contains_tree(10000, 1000);
            contains_tree(100000, 1000);
            cout << endl;
            contains_vector(1000, 1000);
            contains_vector(10000, 1000);
            contains_vector(100000, 1000);
            cout << endl;
            cout << endl;
            insert_tree(1000, 1000);
            insert_tree(10000, 1000);
            insert_tree(100000, 1000);
            cout << endl;
            insert_vector(1000, 1000);
            insert_vector(10000, 1000);
            insert_vector(100000, 1000);
            cout << endl;
            cout << endl;
            erase_tree(1000, 1000);
            erase_tree(10000, 1000);
            erase_tree(100000, 1000);
            cout << endl;
            erase_vector(1000, 1000);
            erase_vector(10000, 1000);
            erase_vector(100000, 1000);
            cout << endl << endl;
            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;

        }
        if (choice == 3)
        {
            std::vector<int> myVector = { 1, -3, 2, 7, 11, 63, 99, 2, 0,0, 7, 1, -2, 99, 88, 73, -42, -2, -2, -3, 19, 0 };
            std::vector<int> new_vector;
            cout << "vector: ";
            for (int i = 0; i < 22; i++)
            {
                if (head.insert(myVector[i]) == false && find_elem(new_vector, myVector[i]) == false)
                {
                    new_vector.push_back(myVector[i]);
                }
                cout << myVector[i] << "; ";
            }
            cout << endl;
            cout << "new vector: ";
            for (int i = 0; i < new_vector.size(); i++)
            {
                cout << new_vector[i] << "; ";
            }
            cout << endl;
            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;

        }
        if (choice == 4) return 0;
        else if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            cout << "invalid character entered!!!!!!!    try again" << endl;
            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;
        }
    }
}