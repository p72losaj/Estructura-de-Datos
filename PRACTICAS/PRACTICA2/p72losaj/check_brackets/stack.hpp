#ifndef __Stack_HPP__
#define __Stack_HPP__

#include <cassert>


/**
 * @brief ADT Stack.
 * Models a Single linked list[T].
 */
template<class T>
class Stack
{
  public:

  /** @name Life cicle.*/
  /** @{*/

  /** @brief Create an empty Stack.
   * @post is_empty()
   */
  Stack ()
  {
     raiz = NULL;
     assert(is_empty());
  }

  /** @brief Destroy a Stack.**/
  ~Stack()
  {
      Nodo *reco = raiz;
      Nodo *bor;
      while (reco != NULL)
      {
        bor = reco;
        reco = reco->sig;
        delete bor;
      }

  }

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      if(raiz == NULL) return true;

      else return false;
  }

  /** @brief get the top item.
   * @pre not is_empty()
   */
  const T& top() const
  {

      assert(!is_empty());
      return raiz->item;

  }

  /**@}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief Insert a new item.
   * @post top() == new_it
   */
  void push(const T& new_it)
  {

    Nodo *nuevo;

    nuevo = new Nodo();

    nuevo->item = new_it;


    if (raiz == NULL)
    {
        raiz = nuevo;
        nuevo->sig = NULL;
    }
    else
    {
        nuevo->sig = raiz;
        raiz = nuevo;
    }



  }

  /** Remove the top item.
   * @pre not is_empty()
   */
  void pop()
  {

      assert (!is_empty());

      Nodo *bor = raiz;

      raiz = raiz->sig;

      delete bor;
      
  }

  /** @} */

private:

  /** @brief Copy constructor.
   * @warning we don't want a copy constructor.
   */
  Stack(const Stack<T>& other)
  {}

  /** @brief Assign operator.
   * @warning we don't want the assign operator.
   */
  Stack<T>& operator=(const Stack<T>& other)
  {
      return *this;
  }

protected:

  //TODO

    class Nodo
    {
        public:

        T item;
        Nodo *sig;

    };

    Nodo *raiz;
};

#endif
