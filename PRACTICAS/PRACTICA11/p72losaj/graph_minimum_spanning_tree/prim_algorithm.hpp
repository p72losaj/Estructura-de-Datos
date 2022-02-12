#ifndef __FLOYD_ALGORITHM_HPP__
#define __FLOYD_ALGORITHM_HPP__

#include <exception>
#include <limits>
#include <memory>
#include <valarray>
#include <vector>

#include "graph.hpp"

/**
 * @brief Apply the Prim algorithm to a undirected connected graph to get the minimum spannig tree.
 * The current node of g is used as root.
 * @arg[in] g is the graph.
 * @arg[out] mst is the list of edges of g that forms the minium spanning tree.
 * @return the total weigth of the mininum spanning tree.
 * @pre g is an undirected connected graph.
 * @pre g.hash_current()
 * @warning throw std:runtine_error("It is a non-connected graph.") if a solution could not be computed.
 */
template <class T>
float
prim_algorithm(WGraph<T>& g, std::vector<typename WGraph<T>::EdgeRef>& mst) noexcept(false)
{
    assert(g.has_current_node());

    //TODO: Declare the U, V and C vectors according to the algorithm (see class documentation.)

    float total_distance = 0.0;
    auto u = g.current_node();

    std::vector<bool> U; 
    std::vector<typename WGraph<T>::NodeRef> V; // Vector de nodos más cercano
    std::vector<float> C; // vector de distancias

    V.resize(g.size(), nullptr);
    C.resize(g.size(), std::numeric_limits<float>::infinity()); 
    U.resize(g.size(), false);

    //TODO: Add the start node to the Minimum Spanning Tree (mst).

    int x = 0;

    g.goto_first_node();

    while(g.has_current_node() && g.current_node() != u)
    {
        g.goto_next_node();
        x++;
    }

    U[x] = true;

    //ITERATE FOR the N-1 edges.
    for (size_t i=1; i<g.size(); ++i)
    {
        //TODO: Update vector of best distances regarding the last vertex added u to the mst.

        int min = 0;   // numero de vectores más cercanos a un vector

        g.goto_first_node();

        for(int j = 0; j < g.size(); j++)
        {
            float distancia = g.weight(u, g.current_node()); // distancia entre el nodo u y el nodo actual

            if( distancia < C[j] && U[j] == false)
            {
                V[j] = u;
                C[j] = distancia;
            }

            if( C[j] < C[min] && U[j] == false) min = j; 

            g.goto_next_node();
        }    

        //TODO: Find the next vertex to be added to the mst.
        //Remeber: if a tie exists, select the vertex with lesser label.
        //You can use std::numeric_limits<float>::infinity() if it is necessary.

        g.goto_first_node();

        for(int j = 0; j < min; j++) g.goto_next_node(); // localiza el nodo de distancia minima

        auto next = g.current_node(); // nodo más cercano

        //TODO: check if a valid condition is met for a connected graph.
        //Suggestion: What about the minimum distance found?
        if (total_distance == std::numeric_limits<float>::infinity())
            throw std::runtime_error("It is a non-connected graph.");

        //TODO:Set vertex found as beloning to the mst.

        U[min] = true;

        float distancia = C[min]; // new edge's weight

        C[min] = std::numeric_limits<float>::infinity();

        //TODO:Add the edge found to the mst vector.

        mst.push_back(g.edge(next, V[min]));

        //TODO: update the total distance of the mst with the new edge's weight.
        
        total_distance = total_distance + distancia;
        u = next;
        
    }

    return total_distance;
}



#endif //__FLOYD_ALGORITHM_HPP__
