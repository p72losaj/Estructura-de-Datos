#ifndef __KMEANS_HPP__
#define __KMEANS_HPP__

#include <vector>
#include "pattern.hpp"

/**
 * @brief kmeans algorithm.
 * @see https://en.wikipedia.org/wiki/K-means_clustering
 * @param[in,out] dts is the dataset.
 * @param K is the number of clusters to look for.
 * @param max_iters is the maximum number of iterations to do.
 * @param centroids are the centroids.
 * @return the actual number of iterations carried out.
 *
 * @warning the patterns in dts will change the class labels regarding
 * the nearest centroid.
 */
size_t kmeans(std::vector<Pattern>& dts,
            const size_t K,
            const size_t max_iters,
            std::vector<Pattern>& centroids);

#endif
