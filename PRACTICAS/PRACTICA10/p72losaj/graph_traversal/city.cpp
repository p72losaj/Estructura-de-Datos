#include <cmath>
#include "city.hpp"

/** @brief convert from degrees to radians. */
inline static
double
to_rad(const double a)
{
    return M_PI/180.0 * a;
}

double
distance(const City& s, const City& d)
{
    const double EARTH_RADIX = 6378.0; //Km.
    const double dif_latitude = to_rad(d.latitude - s.latitude);
    const double dif_longitude = to_rad(d.longitude - s.longitude);

    const double a = std::pow(std::sin(dif_latitude/2.0), 2.0) +
              std::cos(to_rad(s.latitude))*
              std::cos(to_rad(d.latitude))*
              std::pow(std::sin(dif_longitude/2.0),2.0);
    const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0-a));
    return c*EARTH_RADIX;
}

/**
 * @brief unfold a city from an input stream.
 */
std::istream&
operator>>(std::istream& in, City& c)
{
    in >> c.name >> c.latitude >> c.longitude;
    return in;
}

/**
 * @brief fold a City to an output stream.
 */
std::ostream&
operator<<(std::ostream& out, City const& c)
{
    out << c.name << ' ' << c.latitude << ' ' << c.longitude;
    return out;
}

/**
 * @brief Template specialization for City.
 */
template<>
std::shared_ptr<WGraph<City>> create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    std::shared_ptr<WGraph<City>> graph;

    //TODO
    //Remenber: to save space, for the edges it is only used the name of de
    //city and not the whole city data.

    std::string tipo;
    in >> tipo;
    int vertices;
    in >> vertices;
    graph = std::make_shared<WGraph<City>>(vertices);
    City nuevoNodo;

    for(int i = 0; i < vertices; i++)
    {
        
        in >> nuevoNodo.name; // Obtenemos el nombre del nodo
        in >> nuevoNodo.latitude; // Obtenemos la latitud del nodo
        in >> nuevoNodo.longitude; // Obtenemos la longitud del nodo
        graph->add_node(nuevoNodo); // Añadimos el nodo al grafo
    }

    int bordes;
    in >> bordes;
    City u, v;
    int peso;
    if( tipo == "DIRECTED")
    {
            for( int i=0; i < bordes; i++)
            {                
                in >> u.name;            
                in >> v.name;                
                in >> peso;                
                auto nodo_u = graph->find(u); 
                auto nodo_v = graph->find(v); 
                graph -> set_weight(nodo_u, nodo_v, peso);
            }
    }
    else
    {
        for(int i = 0; i < bordes; i++ )
        {
            in >> u.name;
            in >> v.name;
            in >> peso;
            auto nodo_u = graph->find(u); 
            auto nodo_v = graph->find(v); 
            graph -> set_weight(nodo_u, nodo_v, peso);
            graph -> set_weight(nodo_v, nodo_u, peso);
        }
    }
    return graph;
}

