#include "kmeans.hpp"
#include <time.h>
/**
 * @brief kmeans_initialice_centroids
 * Initialize K centroids picking at random K patterns from dts.
 * @warning avoid select the same pattern several times.
 */
static void
kmeans_initialize_centroids(const std::vector<Pattern>& dts,
                                 size_t K,
                                 std::vector<Pattern>& centroids)
{

  centroids.resize(K, Pattern(dts[0].dim()));

  //TODO : WARNING AVOD SELECT THE SAME PATTERN SEVERAL TIMES.
  bool res;
  int c;
  int valores[K];
  for(int i=0; i<K; i++)
  {
      do{

          res = false;

          c = rand() % (dts.size()+1);
          
          for(int j=0; j<i; j++)
          {
              if( valores[K] == c)
              {
                  res = true;
                  break;
              } // if
          } // for
      } while(res);
      centroids[i] = dts[c];
      valores[i] = c;
      centroids[i].set_class_label(i);
  } //for
}

/** @brief assign patterns to the nearest centroid.
 * Each pattern in dts will have the nearest centroid's label.
 * @return the number of changes carried out.
 */
static size_t
kmeans_assign_patterns(std::vector<Pattern>& dts,
                           std::vector<Pattern>& centroids)
{
  size_t num_changes = 0;

  //TODO

  int near; // Pattern más cercano
  float d; // distancia
  for( int i=0; i< dts.size(); i++) 
  {
    for(int j=0;j<centroids.size();j++) 
    {
        if(distance(dts[i],centroids[j]) == 0 ) break;
        if(j==0)
        {
          if(dts[i].class_label() == -1)
          {
            dts[i].set_class_label(j);
            near = j;
            d = distance(dts[i],centroids[j]);
            continue;
          } // if
          else
          {
              near = dts[i].class_label();
              d = distance(centroids[near],dts[i]); 
          } //else
        } //if
        if(distance(dts[i],centroids[j]) < d) 
        {
          d = distance(dts[i],centroids[j]); // asignamos la distancia minima
          near = centroids[j].class_label(); // asignamos la etiqueta del más cercano
          dts[i].set_class_label(near);
          num_changes++;
        } //if
    } //for
  } //for    
  return num_changes;
}

/**
 * @brief Given a dts compute the centrois of each class label.
 * @param dts is the dataset.
 * @param centroids are the centroids.
 */
static void
kmeans_compute_centroids(const std::vector<Pattern>& dts,
                              const size_t K,
                              std::vector<Pattern>& centroids)
{
  /* reset centroids to zero.*/
  const size_t dim = dts[0].dim();
  if (centroids.size() != K)
      centroids.resize(K, Pattern(dts[0].dim()));
  for(size_t k=0; k<centroids.size(); ++k)
      centroids[k] = Pattern(dim, static_cast<int>(k));

    //TODO

    float min; 
    int c;  
    float suma; 
    int nCentroid;  // nuevo Centroid
    bool res;
    for(int i=0;i<K;i++)
    {
      min=0.0;  
      res = false;
      for(int j=0;j<dts.size();j++)
      {
          if(dts[j].class_label() != i)
          {
              continue;           
          } //if
          suma=0.0; 
          c = 0; 
          for(int k=0;k<dts.size();k++)
          {
            if(dts[j].class_label() == dts[k].class_label()) 
            {
              suma = suma + distance(dts[j],dts[k]);
              c++;
            } // if
          } // for
          float media = suma/c;
          if(min == 0.0 || media < min)
          {
            min = media;
            nCentroid = j;
            res = true;
          } //if
      } //for
      if(res)
      {
        centroids[i] = dts[nCentroid];
      } // if
    } //for 
}


size_t
kmeans(std::vector<Pattern>& dts,
            const size_t K,
            const size_t max_iters,
            std::vector<Pattern>& centroids)
{

    /*Reset labels to -1 (none class).*/
    for(size_t i = 0; i < dts.size(); ++i)
        dts[i].set_class_label(-1);

    /*Initialice picking at random K patterns.*/
    kmeans_initialize_centroids(dts, K, centroids);

    size_t iter = 0;
    size_t num_changes;
    do
    {
        num_changes = kmeans_assign_patterns(dts, centroids);
        /* assign patterns to the nearest centroid. */
        if (num_changes>0)
            kmeans_compute_centroids (dts, K, centroids);
    }
    while (++iter < max_iters && num_changes>0);
    return iter;
}
