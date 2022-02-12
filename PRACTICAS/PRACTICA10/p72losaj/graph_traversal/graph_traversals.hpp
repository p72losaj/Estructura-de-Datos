#ifndef __GRAPH_TRAVERSALS_HPP
#define __GRAPH_TRAVERSALS_HPP

#include <stack>
#include <queue>

#include "graph.hpp"

/**
 * @brief Depth first search from a vertex.
 * The current node will be used as start vertex.
 * @arg g is the graph.
 * @arg p is a functional to process the vertex.
 * @return the last p() return value.
 * @pre g.has_current_node()
 * @warning if p() return false, the search will be finished.
 * @warning only a spanning tree is searched.
 */
template<class T, class Processor>
bool depth_first_search(WGraph<T>& g, Processor& p)
{
    assert(g.has_current_node());
    bool ret_val = true;

    //TODO
    //Do an ITERATIVE implementation.

    std::stack <typename GraphNode<T>::Ref> stack;
    stack.push(g.current_node());
	while(!stack.empty() && ret_val==true)
	{
		auto v_u = stack.top();
		stack.pop();
		if(!v_u->is_visited())
		{
			v_u->set_visited(true);
			ret_val=p.apply(v_u);
			g.goto_node(v_u);
			while(g.has_current_edge())
			{
				auto v_v=g.current_edge()->other(v_u);
				if(!v_v->is_visited())
				{
					stack.push(v_v);
				}
				g.goto_next_edge();
			}
		}
	}

    return ret_val;
}

/**
 * @brief breadth first search from a vertex.
 * The current node will be used as start node.
 * @arg g is the graph.
 * @arg p is a functional to process the vertex.
 * @return the last p() return value.
 * @pre g.has_current_node()
 * @warning if p() return false, the search will be finished.
 * @warning only a spanning tree is searched.
 */
template<class T, class Processor>
bool breadth_first_search(WGraph<T>& g, Processor& p)
{
    assert(g.has_current_node());
    bool ret_val = true;

    //TODO

    std::queue <typename GraphNode<T>::Ref> cola;
    cola.push(g.current_node());
	while(!cola.empty() && ret_val==true)
	{
		auto v_u = cola.front();
		cola.pop();
		if(!v_u->is_visited())
		{
			ret_val=p.apply(v_u);
			v_u->set_visited(true);
			g.goto_node(v_u);
			while(g.has_current_edge())
			{
				auto v_v=g.current_edge()->other(v_u);
				if(!v_v->is_visited())
				{
					cola.push(v_v);
				}
				g.goto_next_edge();
			}
		}
	}

    return ret_val;
}

#endif // __GRAPH_TRAVERSALS_HPP
