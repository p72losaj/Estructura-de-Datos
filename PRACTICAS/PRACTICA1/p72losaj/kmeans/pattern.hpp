#ifndef __Pattern_HPP__
#define __Pattern_HPP__

#include <cassert>
#include <iostream>
#include <exception>
#include <valarray>

/**
 * @brief ADT Pattern.
 * Models a pattern for Machine Learning.
 */
class Pattern
{
  public:

  /** @name Life cicle.*/

  /** @{*/

  /** @brief Create a patterm.
   * @pre dim>=0
   * @post dim()>0 implies min()==max()==0.0
   */
  Pattern (const size_t dim=0, const int class_label=-1);

  /** @brief Create a patterm.
   * @pre dim>0
   */
  Pattern (const float values[], const size_t dim, const int class_label=-1);

  /** @brief Copy constructor.*/
  Pattern (const Pattern& other);

  /** @brief Destroy a pattern.**/
  ~Pattern();

  /** @}*/

  /** @name Observers*/

  /**@{*/

  /** @brief get the pattern's dimension.*/
  size_t dim() const ;

  /** @brief get the class label */
  int class_label() const;

  /** @brief get the n-dimensio
   * @pre 0<= idx < dimensions()
   */
  float operator[](const size_t idx) const;

  /** @brief get the sum of all values. */
  float sum() const;

  /** @brief get the maximum of all values.
   * @post retVal >= all values.
   */
  float max() const;

  /** @brief get the minimum of all values.
   * @post retVal <= all values.
   */
  float min() const;

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief Resize the pattern.
   * @pre dim>0
   */
  void set_dim(size_t new_dim);

  /** @brief set the class label.
   * @post class_label() == new_label
   */
  void set_class_label(const int new_label);

  /** @brief set the i-dimension value.
   * @pre 0<=i<dim()
   * @post This[i] == new_v;
   */
  void set_value(const size_t i, const float new_v);

  /** @brief set all the values.
   * @pre value array. has at least dim() values.
   * @post This[i] == values[i] for 0<i<dim();
   */
  void set_values(const float values[]);

  /** @brief add other pattern to this.
   * @pre dim()==other.dim()
   * @post this == (old.this()+other)
   */
   Pattern& operator += (const Pattern& other);

   /** @brief Substract other pattern to this.
    * @pre dim()==other.dim()
    * @post this == (old.this()-other)
    */
    Pattern& operator -= (const Pattern& other);

   /** @brief elementwise product.
    * @pre dim()==other.dim()
    * @post this == (old.this()*other)
    */
   Pattern& operator *= (const Pattern& other);

   /** @brief multiply each element by a constant value.
    * @post for each dimension i, This[i] = old.This[i]*c
    */
   Pattern& operator *= (const float c);


  /** @} */

  protected:

   //TODO

    int c_;
    std:: valarray <float> v_;
};

/** @brief add two patterns.
 * @pre a.dim()==b.dim()
 */
inline Pattern
operator+(const Pattern& a, const Pattern b)
{
    Pattern ret (a);
    ret += b;
    return ret;
}

/** @brief substract two patterns.
 * @pre a.dim()==b.dim()
*/
inline Pattern
operator-(const Pattern& a, const Pattern b)
{
    Pattern ret (a);
    ret -= b;
    return ret;
}

/** @brief multiply (elementwise) two patterns.
 * @pre a.dim()==b.dim()
*/
inline Pattern
operator*(const Pattern& a, const Pattern b)
{
    Pattern ret (a);
    ret *= b;
    return ret;
}

/** @brief multiply by a constant all the dimensions of a pattern.*/
inline Pattern
operator*(const Pattern& a, const float c)
{
    Pattern ret (a);
    ret *= c;
    return ret;
}

/** @brief multiply by a constant all the dimensions of a pattern.*/
inline Pattern
operator*(const float c, const Pattern& a)
{
    Pattern ret (a);
    ret *= c;
    return ret;
}

/** @brief scalar product of two patterns.
 * @pre a.dim()==b.dim()
*/
inline float
dot(const Pattern& a, const Pattern& b)
{
    return (a*b).sum();
}

/**
 * @brief Compute the euclidean distance between two patterns.
 * @param a is one pattern.
 * @param b is the other pattern.
 * @pre a.dim()==b.dim()
 * @return the euclidean distance from a to b.
 */
float distance(const Pattern& a, const Pattern& b);

/** @brief Load a pattern from an input stream.
 * @pre the input format will be "class_label d0 ... dn-1"
 * @pre p.dim() == input dims.
 */
std::istream& operator >> (std::istream& input, Pattern& p)
    noexcept(false);

/** @brief Output a pattern to an output stream.
 * @post the output format will be "class_label d0 ... dn-1\n"
 */
std::ostream& operator << (std::ostream& output, const Pattern& p);


/** @brief Load a file with patterns.
 * @pre the format is a first line <num patterns> <dimension> and then
 * a pattern per line.
 * @warning throw runtine_error if a wrong format is detected.
 */
std::istream& load_dataset(std::istream& in,
                           std::vector<Pattern>& dts) noexcept(false);
#endif
