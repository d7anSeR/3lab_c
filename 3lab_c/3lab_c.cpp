﻿#include <iostream>
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
    void walk_(const vertex_type& start_vertex/*, std::function<void(const vertex_type&)> action*/)
    {
        visited[start_vertex] = true;
        cout << start_vertex;
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
    //проверка-добавление-удаление вершин
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
    ///////////////////////////////////////////

    //проверка-добавление-удаление ребер
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
    bool has_edge(const Edge& e) //c учетом расстояния в Edge
    {
        if (has_vertex(e.id1) && has_vertex(e.id2))
        {
            for (auto it = map_v[e.id1].begin(); it != map_v[e.id1].end(); ++it)
            {
                if (it->second.id2 == e.id2 && it->second.dist == e.dist) return true;
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
    bool remove_edge(const vertex_type& from, const vertex_type& to)  // удаление ребра
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
    bool remove_edge(const Edge& e) //c учетом расстояния
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
        return n;
    }
    /*std::vector<Vertex> vertices() const;*/
    ////получение всех ребер, выходящих из вершины
    //std::vector<Edge> edges(const Vertex& vertex);
    //size_t degree() const; //степень
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
   
    std::vector<vertex_type> shortest_path(const vertex_type& from, const vertex_type& to)
    {
        std::map<vertex_type, Distance> distances;
        std::map<vertex_type, vertex_type> prev;
        for (auto it = map_v.begin(); it != map_v.end(); ++it) {
            distances[it->first] = INT_MAX;
        }
        priority_queue<pair<Distance, vertex_type>, vector<pair<Distance, vertex_type>>, greater<pair<Distance, vertex_type>>> pq;
        distances[from] = 0;
        pq.push({ 0, from });
        vector<vertex_type> vis;
        while (!pq.empty()) {
            Distance dist = pq.top().first;
            vertex_type vertex = pq.top().second;
            pq.pop();

            if (dist > distances[vertex]) {
                continue;
            }
            
            
            for (auto it = map_v[vertex].begin(); it != map_v[vertex].end(); ++it)
            {
                double newDist = dist + it->second.dist;
                if (newDist < distances[it->second.id2]) {
                    distances[it->second.id2] = newDist;
                    prev[it->second.id2] = vertex;
                    pq.push(make_pair(newDist, it->second.id2));
                }
            }
            vector<vertex_type> path;
            vertex_type current = to;
            while (current != from) {
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
    }
};
void print(int val)
{
    cout << val;
}

int main()
{
    Graph<int> tmp;
    tmp.add_vertex(1);
    tmp.add_vertex(2);
    tmp.add_vertex(3);
    tmp.add_vertex(4);
    tmp.add_vertex(5);
    tmp.add_vertex(7);
    tmp.add_edge(1, 2, 16);
    tmp.add_edge(2, 6, 2);
    tmp.add_edge(1, 3, 2);
    tmp.add_edge(3, 2, 9);
    tmp.add_edge(3, 4, 5);
    tmp.add_edge(4, 1, 8);
    tmp.add_edge(5, 7, 9);
    tmp.Print();
    cout << endl;
    /*tmp.remove_vertex(1);*/
    tmp.Print();
    cout << endl;
    /*tmp.remove_edge(3, 6);
    tmp.remove_edge(3, 2);
    tmp.remove_edge(1, 2);*/
    tmp.Print();
    tmp.walk(3, print);
    std::vector<int> res = tmp.shortest_path(1,4);
    for (auto i : res)
    {
        cout << i;
    }
    cout << endl;
    return 0;
}