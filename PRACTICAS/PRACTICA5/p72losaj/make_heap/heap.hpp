#ifndef __ED_Heap_HPP__
#define __ED_Heap_HPP__

#include <cassert>
#include <iostream>
#include <functional>
#include <memory>
#include <algorithm>

/**
 * @brief Implement the Heap ADT.
 * The parameter template Comp must implement the interface:
 *          bool operator()(T const& a, T const& b)
 * to compare two values a, b.
 * For instance, std::less_equal<T> could be used.
 *
 * It is interesting both the heap can manage its own storage as use a external
 * storage (a given array).
 *
 * For this, you can use two attributes, i.e., my_storage_ and data_.
 *
 * When the heap is created empty with a capacity of elements, my_strogage_ and data_
 * points to a new block of capacity elements. Then when the heap variable is destroied,
 * you must free this memory.
 *
 * When an external storage is used, (i. e. heapify a given vector), my_storage is null and data_ points to
 * the first value of the vector. Then when the heap varible is destroid, you MUST NOT free the memory (my_storage_ is null)
 * because this memory is owned by other external object.
 *
 * The type std::unique_ptr<> is strongly recommended to use for my_storage_ attribute.
 *
 */
template<class T, class Comp = std::less_equal<T> >
class Heap
{
  public:

  /** @name Life cicle.*/
  /** @{*/

    /**
     * @brief Create an empty Heap with a given capacity.
     * @warning the heap is the owner of the reserved memory.
     * @post is_empty()
     */
    Heap (int capacity=0)
    {
        //TODO
        capacidad = capacity;
        size_ = 0;
        array = new T[capacidad];

        //
        assert(is_a_heap());
        assert(is_empty());
    }

    /**
     * @brief Create an Heap from a array of items.
     * @waring The heap not is the responsable of the memory pointed by @arg data.
     * @post is_full()
     */
    Heap (T* data, size_t size)
    {        
        //TODO
        capacidad = size;
        size_ = size;
        array = new T[capacidad];

        for (int i = 0; i < size_; i++) {
            array[i] = data[i];
        }

        heapify();
        //
        assert(is_a_heap());
        assert(is_full());
    }

    /** @brief Destroy a Heap.**/
    ~Heap()
    {
        delete array;
    }

  /** @}*/

  /** @name Observers*/

  /** @{*/

    /** @brief is the list empty?.*/
    bool is_empty () const
    {
        //TODO
        return size_ == 0;
    }

    /** @brief is the heap full?.*/
    bool is_full () const
    {
        //TODO
        return size_ == capacidad;
    }

    /** @brief Get the heap size. */
    int size() const
    {
        //TODO
        return size_;
    }

    /** @brief Get the heap capacity. */
    int capacity() const
    {
        //TODO
        return capacidad;
    }

    /** @brief Get the root item.
     * @pre not is_empty();
     */
    T const& top() const
    {
        assert(! is_empty());
        //TODO
        return array[0];
    }

    /** @brief Get the raw vector with the heap data.*/
    T const* data() const
    {
        //TODO
        return array;
    }

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief insert a new item.
   * @pre not is_full()
   */
    void insert (T const& new_it)
    {
        assert(! is_full());      
        //TODO
        array[size_]= new_it;
        int i = size_;

        size_++;
        
        while (i > 0 && comp_(array[i], array[parent(i)])) {
            int aux = array[i];
            array[i] = array[parent(i)];
            array[parent(i)] = aux;

            i = parent(i);
        }

        //
        assert(is_a_heap());
    }

    /** @brief Remove the root item.
     * @pre not is_empty()
     */
    void remove()
    {
        assert(! is_empty());
        //TODO
        for (int i = 1; i < size_; i++) {
            array[i-1] = array[i];
        }
        size_--;

        heapify();

        //
        assert(is_a_heap());
    }

  /** @}*/
private:

  /** @brief disable copy constructor.*/
  Heap(Heap<T, Comp> const& other);

  /** @brief disable assign operator.*/
  Heap<T, Comp>& operator=(Heap<T, Comp> const& other);

protected:

    /**
     * @brief get the parent of node i
     * @pre i>0
     */
    int parent(int i) const
    {
        assert(i>0);
        //TODO
        int parent = i/2;
        if (i % 2 == 0) { parent--; }

        return parent;
    }

    /**
     * @brief get the left child of node i.
     */
    int left(int i) const
    {
        //TODO
        return (2*i)+1;
    }

    /**
     * @brief get the right child of node i.
     */
    int right(int i) const
    {
        //TODO
        return (2*i)+2;
    }

    /**
     * @brief Check the head invariant for the subtree.
     * @pre 0<=root && root < size()
     */
    bool is_a_heap(int root=0) const
    {      
        //TODO
        bool izq = false, der = false;
        // Lado izquierdo del subarbol
        int l = left(root);
        if( l >= size_) izq = true;
        else if ( comp_(array[root], array[l])) izq = is_a_heap(l); // recursividad
        else return false;
        // lado derecho del subarbol
        int r = right(root);
        if( r >= size_) der = true;
        else if ( comp_(array[root], array[r])) der = is_a_heap(r); // recursividad
        else return false;

        return izq && der;

    }

  /** @brief Shitup a node.*/
    void shit_up(int i)
    {
        int p = parent(i);

        //if _comp(item(i), item(p)), swap i with p and shift up p.
        //TODO
        if (comp_(array[i], array[p])) {
            int aux = array[i];
            array[i] = array[p];
            array[p] = aux;

            shit_up(p);
        }

    }

    /** @brief shitdown a node. */
    void shit_down(int i)
    {
        int n = i; //n will have the node to swap with. by default is the root i.

        int l = left(i); //the left child of i.
        int r = right(i); //the right child of i.

        //if l is a valid index and comp_(item(l), item(n) then now n is l
        //TODO
        if (l >= 0 && l < size_ && comp_(array[l], array[n])) {
            T aux = array[n];
            array[n] = array[l];
            array[l] = aux;
        }

        //if r is a valid index and comp_(item(r), item(n) then now n i s r
        //TODO
        if (r >= 0 && r < size_ && comp_(array[r], array[n])) {
            T aux = array[n];
            array[n] = array[r];
            array[r] = aux;
        }
        
        //if i <> n then invariant is not meet, swap i with n and shift down n.
        //TODO
        if (i != n) {
            int c = i;
            i = n;
            n = i;
            shit_down(n);
        }
    }

    void ordenar (int i) {
        int n = i;
        int l = left(i);
        int r = right(i);

        if (l < size_ && comp_(array[l], array[n]))
            n = l;

        if (r < size_ && comp_(array[r], array[n]))
            n = r;

        if (n != i) {
            T aux = array[n];
            array[n] = array[i];
            array[i] = aux;

            ordenar(n);
        }
    }

    /** @brief make the subtree starting in root to be a heap.*/
    void heapify(/*int root=0*/)
    {
        //TODO
        //Remenber there are two ways to implement.
        //The best is to use shiftdowns from the second to last level (|size/2| ... 0)
        for (int i = (size_ / 2)-1; i >= 0; i--) {
            ordenar(i);
        }

        //
        assert(is_a_heap());
    }

    Comp comp_; //Functor to compare heap items. comp_(it1, it2)

    //TODO
    T* array;
    size_t capacidad;
    size_t size_;

};


#endif
