#ifndef MAZE_SOLVER_HPP
#define MAZE_SOLVER_HPP

#include <tuple>
#include <vector>
#include "graph.hpp"

/**
 * @brief Solve a maze.
 * A maze is a grid (height, widht) of connected points.
 * The path linking the start point with the end point must be found out.
 * The label of a vertex codifies the x,y coordinates of the point in the grid: y=label/grid_width, x=label%grid_width.
 * @param maze is a graph representing the maze.
 * @param start is the start point.
 * @param end is the goal point.
 * @param grid_width is the width of the grid.
 * @param path save the path of connected grid points that links the start with the end points.
 * @post if none path exists, path.size()==0.
 */
void maze_solver(WGraph<int>& maze,
                 WGraph<int>::NodeRef& start,
                 WGraph<int>::NodeRef& end,
                 const int grid_width,
                 std::vector<std::tuple<int, int> >& path);


#endif // MAZE_SOLVER_HPP
