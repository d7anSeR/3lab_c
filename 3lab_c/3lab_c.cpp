#include <iostream>
#include <map>
#include <vector>
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
    std::map<vertex_type, vector<Edge>> map_v;

public:
    Graph(int n_vert = 0) : n(n_vert){}
    
    friend std::ostream& operator<< (std::ostream& out, const Edge& e)
    {
        out << "-(" << e.id1 << ", " << e.id2 << "; " << e.dist << ')';
        return out;
    }
    friend std::ostream& operator<< (std::ostream& out, const std::vector<Edge>&vec)
    {
        for(int i = 0; i < vec.size();i++)
        out << "[" << i << "] " << vec[i];
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
            std::vector<Edge> mass;
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
            std::vector<Edge>tmp = map_v[from];
            for(int i = 0; i < tmp.size(); i++)
            {
                if (tmp[i].id2 == to) return true;
            }
            return false;
        }
        return false;
    }
    bool has_edge(const Edge& e) //c учетом расстояния в Edge
    {
        if (has_vertex(e.id1) && has_vertex(e.id2))
        {
            std::vector<Edge>tmp = map_v[e.id1];
            for (int i = 0; i < tmp.size(); i++)
            {
                if (tmp[i].id2 == e.id2 && tmp[i].dist == e.dist) return true;
            }
            return false;
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
                map_v[from].push_back(tmp);
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
    /*bool remove_edge(const vertex_type& from, const vertex_type& to)
    {

    }*/
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
    /*std::cout << "Hello World!\n";
    std::vector<int> m;
    m.resize(0);*/
    Graph<int> tmp;
    tmp.add_vertex(1);
    tmp.add_vertex(2);
    tmp.add_vertex(3);
    tmp.add_vertex(4);
    tmp.remove_vertex(5);
    tmp.remove_vertex(3);
    tmp.add_edge(1, 2, 16);
    tmp.add_edge(2, 6, 2);
    tmp.add_edge(1, 3, 2);
    tmp.add_edge(3, 2, 9);
    tmp.add_edge(3, 4, 5);
    tmp.add_edge(4, 1, 8);
    tmp.Print();
    return 0;
}