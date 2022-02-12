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

template<>
std::shared_ptr<WGraph<City>> create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    std::shared_ptr<WGraph<City>> graph;
    std::string type;
    in >> type;
    bool is_directed = true;
    if (type != "DIRECTED")
        is_directed = false;

    size_t size;
    in >> size;
    if (!in)
        return nullptr;
    graph = std::make_shared<WGraph<City>>(size);
    for (size_t i=0;i<size;++i)
    {
        City item;
        in >> item;
        if (in)
            graph->add_node(item);
        else
            return nullptr;
    }
    size_t n_edges;
    in >> n_edges;
    if (!in)
        return nullptr;
    for (size_t i=0;i<n_edges;++i)
    {
        std::string u, v;
        float weight;
        in >> u >> v >> weight;
        if (!in)
            return nullptr;
        auto vertex_u = graph->find(City(u));
        if (!vertex_u)
            throw std::runtime_error("Wrong graph");
        auto vertex_v = graph->find(City(v));
        if (!vertex_v)
            throw std::runtime_error("Wrong graph");
        graph->set_weight(vertex_u, vertex_v , weight);
        if (!is_directed)
            graph->set_weight(vertex_v, vertex_u, weight);
    }

    return graph;
}

