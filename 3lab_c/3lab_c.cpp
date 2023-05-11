#include <iostream>
#include <map>
#include <memory>
using namespace std;
template<typename vertex_type, typename Distance = double>
class Graph {
private:
    struct Edge 
    {
        vertex_type id1;
        vertex_type id2;
        Edge* next;
        Distance dist;
        Edge(vertex_type id1_ = 0,vertex_type id_2 = 0, Distance distance_ = 0, Edge* next_ = NULL) : id1(id1_), id2(id_2), dist(distance_), next(next_) {}
    };
    int n;
    std::map<vertex_type, Edge*> map_v;

public:
    Graph(int n_vert = 0) : n(n_vert){}
    int get_n() const {
        return n;
    }
    //проверка-добавление-удаление вершин
    bool has_vertex(const vertex_type& v) const
    {
        if (n == 0) return false;
        if (map_v.count(v) != 0) return true;
        return false;
    }
    void add_vertex(const vertex_type& v)
    {
        /*Edge vertex(v);*/
        map_v[v] = NULL;
        n++;
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
            Edge* tmp = map_v[from];
            while (tmp)
            {
                if (tmp->id2 == to) return true;
                tmp = tmp->next;
            }
            return false;
        }
        return false;
    }
    bool has_edge(const Edge& e) //c учетом расстояния в Edge
    {
        if (has_vertex(e.id1) && has_vertex(e.id2))
        {
            Edge* tmp = map_v[e.id1];
            while (tmp)
            {
                if (tmp->id2 == e.id2 && tmp->dist == e.dist) return true;
                tmp = tmp->next;
            }
            return false;
        }
        return false;
    }
    void add_edge(const vertex_type& from, const vertex_type& to, const Distance& d)
    {
        Edge tmp(from, to, d);
        if (!has_edge(tmp))
        {
            if (has_vertex(from) && has_vertex(to))
            {
                Edge* t = map_v[from];
                /*Edge b(from, to, d, t);
                std::unique_ptr<Edge> e = b;*/
                Edge e(from, to, d, t);
                if (t != NULL)
                {
                    while (t->next != NULL)
                    {
                        t = t->next;
                    }
                    t->next = &e;
                }
                else
                {
                    map_v[from] = &e;
                }
            }
        }
    }
    //bool remove_edge(const Vertex& from, const Vertex& to);
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
    tmp.add_edge(1, 2, 16);
    tmp.add_edge(2, 6, 2);
    tmp.add_edge(1, 3, 2);
    tmp.add_edge(3, 2, 9);
    tmp.add_edge(3, 4, 5);
    tmp.add_edge(4, 1, 8);
}