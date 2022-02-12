#include "a_star_algorithm.hpp"
#include "maze_solver.hpp"

#include <stack>
#include <cmath>
#include <algorithm>

/**
 * @brief Convert from vertex label to x,y coordinates.
 * @param v is the vertex label.
 * @param grid_width is the width of the grid.
 * @return a tuple <x,y>.
 */
static inline std::tuple<int, int>
label_to_grid_coord(size_t v, int grid_width)
{
    int y=v/grid_width;
    int x=v%grid_width;
    return std::make_tuple(x, y);
}

/**
 * @brief Functional to compute the euclidean distance between graph vertices.
 */
struct Distance
{
    Distance(int ancho) : anchura(ancho)
    {
    }

    float operator()(const WGraph<int>::NodeRef& a,
                     const WGraph<int>::NodeRef& b) const
    {
        int x1,x2,y1,y2;
        std::tuple<int,int> tupla=label_to_grid_coord(a->label(),anchura);
        x1=std::get<0>(tupla);
        y1=std::get<1>(tupla);
        tupla=label_to_grid_coord(b->label(),anchura);
        x2=std::get<0>(tupla);
        y2=std::get<1>(tupla);
        return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    }
    int anchura;
};

void
maze_solver(WGraph<int>& maze,
            WGraph<int>::NodeRef& start,
            WGraph<int>::NodeRef& end,
            const int grid_width,
            std::vector<std::tuple<int, int> > &path)
{
    std::vector<size_t> predecesors;
    std::vector<float> distances;
    struct Distance d(grid_width);

    //TODO
    //Call to a*  with the proper arguments.
    predecesors.resize(grid_width);
    distances.resize(grid_width);
    auto it=a_star_algorithm(maze,start,end,d,predecesors,distances);

    //
    path.resize(0);
        //If there is a path, save it into path vector.
            //Remenber: the result will be tuples <x,y> for the all the points in the path from start point to end point.
        //TODO
    for(int i = end->label(); predecesors[i] != i; i = predecesors[i])
    {
            path.push_back(label_to_grid_coord( i, grid_width));
    }

    if (path.size() !=0)
    {
        path.push_back(std::make_tuple(0,0));
        std::reverse(path.begin(),path.end()); // Invierte el vector
    }

}
