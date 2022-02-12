#ifndef __Queue_HPP__
#define __Queue_HPP__

#include <cassert>
#include <cstdlib>
#include <list>


/**
 * @brief ADT Queue.
 * Models a queue of T.
 */
template<class T>
class Queue
{
  public:

  /** @name Life cicle.*/
  /** @{*/

  /** @brief Create an empty Queue.
   * @post is_empty()
   */
  Queue ()
  {
      //TODO
      assert(is_empty());
  }

  /** @brief Destroy a Queue.**/
  ~Queue()
  {
      //TODO

      for(int i=0; i<lista.size(); i++) lista.pop_back();

  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO

      if(lista.size() == 0) return true;

      else return false;
  }

  /** @brief Gets the number of items in the queue.*/
  size_t size() const
  {
      //TODO
     return lista.size();
  }

  /** @brief get the front item (the oldest one).
   * @pre not is_empty()
   */
  const T& front() const
  {
      //TODO

      
      return lista.front();
  }

  /** @brief get the back item (the newest one).
   * @pre not is_empty()
   */
  const T& back() const
  {
      //TODO
      
      return lista.back();
  }

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief Insert a new item.
   * @post !is_empty()
   */
  void enque(const T& new_it)
  {
      //TODO
      lista.push_back( new_it );

  }

  /** Remove the front item.
   * @pre not is_empty()
   * @post !is_empty() || size()==0
   */
  void deque()
  {
      //TODO
      
      lista.remove(lista.front());

  }

  /** @} */

private:

  /** @brief Copy constructor.
   * @warning we don't want a copy constructor.
   */
  Queue(const Queue<T>& other)
  {}

  /** @brief Assign operator.
   * @warning we don't want the assign operator.
   */
  Queue<T>& operator=(const Queue<T>& other)
  {
      return *this;
  }

protected:
    //TODO

    std::list <T> lista;
};

#endif
