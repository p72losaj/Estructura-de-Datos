#ifndef A_STAR_ALGORITHM_HPP
#define A_STAR_ALGORITHM_HPP

#include<iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <limits>
#include <functional>

#include "graph.hpp"

/**
 * @brief A* algorithm.
 * Its a version of Dijkstra algorithm with an heuristic to find out the
 * the shortest path between two vertex.
 * @arg[in] g is the graph.
 * @arg[in] start,
 * @arg[in] end are the vertices to link.
 * @arg[in] distance is a functional to compute a heuristic of the distance between two vertices.
 * @arg[out] predecesors is the predecesor vector.
 * @arg[out] distances is the distances vector.
 * @return the number of iterations executed.
 * @pre g.has(source)
 * @pre g.has(end)
 */
template<class T, class Distance>
size_t
a_star_algorithm(WGraph<T>& g,
                 typename WGraph<T>::NodeRef const& start,
                 typename WGraph<T>::NodeRef const& end,
                 const Distance& distance,
                 std::vector<size_t>& predecessors,
                 std::vector<float>& distances)
{
    assert(g.has(start));
    assert(g.has(end));

    //Remember to use (dist-to-end,dist-front-start,u,v) format for the tuples due to they are lexicographicaly sorted.
    //Use typedef to create an alias. So we'll have an easier code.
    //TODO: typedef std::tuple< ...... > Tuple;
    typedef std::tuple<float,float,typename WGraph<T>::NodeRef,typename WGraph<T>::NodeRef> tupla_;
    //Initialize data.
    size_t iterations = 0;
    g.set_visited(false);
    predecessors.resize(g.size());
    for (size_t i=0;i<predecessors.size();++i)
        predecessors[i]=i;
    distances.resize(g.size(), std::numeric_limits<float>::infinity());

    //TODO: Create a priority queue. Remember we want to pick up the lowest item into the queue.
    std::priority_queue<tupla_> cola;

    //TODO: Insert the first item. You can use std::make_tuple(...) for this.
   	auto nuevoItem=std::make_tuple(distance(end,start),0,start,start);
   	cola.push(nuevoItem);

    //While there are nodes to visit and the end node has not been achieved ...
    while (!cola.empty())
    {
        iterations ++;

        //TODO: Get the next tuple to process.
        auto next=cola.top();

        //TODO: Remove the tuple from the queue.
        cola.pop();
        //TODO: Set u as the next vertex to visit.
        auto nuevoNodo=std::get<2>(next);

        //If u is not visited yet, it will be processed.
        if (nuevoNodo->is_visited()==false)
        {
            //Set u as visited.
            nuevoNodo->set_visited(true);
            //Update predessors[u]
            predecessors[nuevoNodo->label()]=std::get<3>(next)->label();
            //Update distances[u]
            distances[nuevoNodo->label()]=distance(nuevoNodo,end);
            //Add new tuples for not visited vertices linked with u.
            g.find(nuevoNodo->item());
            g.goto_first_edge();
            while(g.has_current_edge())
            {
            	auto nuevoNodo2=g.current_edge()->second();
            	if(nuevoNodo2->is_visited()==false)
            	{
            		auto tupla=std::make_tuple(distance(end,nuevoNodo2),distance(start,nuevoNodo2),nuevoNodo2,nuevoNodo);
            		cola.push(tupla);
            	}
            	g.goto_next_edge();
            }
            //Le v one of these vertices. Remenber that:
            
            //0 -> estimated_dist = distance_from_start_V + heuristic(v, end).
            
            //1 -> distance_from_start_V = dist_from_start_U + edge(u,v)->item
            
            //2 -> Next vertex is v.
            
            //3 -> Predecessor is u.
        }

    }
    return iterations;
}

#endif // A_STAR_ALGORITHM_HPP
