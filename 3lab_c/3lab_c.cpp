﻿#include <iostream>
#include <map>
#include <vector>
#include <iterator>
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
            out << it->first << ':' << it->second << endl;
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
    bool has_edge(const vertex_type& from, const vertex_type& to) const
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
    //bool remove_edge(const vertex_type& from, const vertex_type& to) { // удаление ребра
    //    std::map<int, Edge>::std::iterator it;
    //    for (it = map_v[from].begin(); it != map_v[from].end(); it++) {
    //        if (it->second.id2 == to) {
    //            map_v[from].erase(it);
    //            return true;
    //        }
    //    }
    //    return false;
    //}
    //bool remove_edge(const vertex_type& from, const vertex_type& to) { // удаление ребра
    //    map<vertex_type, std::vector<Edge>>::iterator it, itEnd;
    //    it = map_v.begin();
    //    itEnd = map_v.end();
    //    while (it != itEnd)
    //    {
    //        
    //        it++;
    //    }

    //    for (it = adj[v].begin(); it != adj[v].end(); it++) {
    //        if (*it == w) {
    //            adj[v].erase(it);
    //            break;
    //        }
    //    }
    //    for (it = adj[w].begin(); it != adj[w].end(); it++) {
    //        if (*it == v) {
    //            adj[w].erase(it);
    //            break;
    //        }
    //    }
    //}
    //bool remove_edge(const Edge& e); //c учетом расстояния
    //

    ////получение всех ребер, выходящих из вершины
    //std::vector<Edge> edges(const Vertex& vertex);

    //size_t order() const; //порядок
    //size_t degree() const; //степень


    ////поиск кратчайшего пути
    //std::vector<Edge> shortest_path(const Vertex& from,
    //    const Vertex& to) const;
    ////обход
    //std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};

int main()
{
    Graph<int> tmp;
    tmp.add_vertex(1);
    tmp.add_vertex(2);
    tmp.add_vertex(3);
    tmp.add_vertex(4);
    tmp.add_edge(1, 2, 16);
    tmp.add_edge(2, 6, 2);
    tmp.add_edge(1, 3, 2);
    tmp.add_edge(3, 2, 9);
    tmp.add_edge(3, 4, 5);
    tmp.add_edge(4, 1, 8);
    tmp.Print();
    tmp.remove_vertex(5);
    tmp.remove_vertex(3);
    
   /* tmp.remove_edge(1, 2);*/
    tmp.Print();
    return 0;
}