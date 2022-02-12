#ifndef __HASH_table_
#define __HASH_table_
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cassert>

#include <vector>
#include <list>
#include <utility>
#include <memory>

#include <fstream>


/**
 * @brief Implement the HashTable[K,V] ADT.
 * The template parameter keyToInt is a functional to transform
 * values of type K into size_t. It must be implement the interface:
 *    size_t operator()(K const&k)
 */
template<class K, class V, class keyToInt>
class HashTable
{
public:
    /** @name Life cicle.*/
    /** @{*/

    /**
      * @brief Create a new HashTable.
      * @post is_empty()
      * @post not is_valid()
      */
    HashTable(size_t m, uint64_t a=32, uint64_t b=3, uint64_t p=4294967311l,
              keyToInt key_to_int=keyToInt())
    {
        //TODO
        this->dim = m;
        this->a = a;
        this->b = b;
        this->p = p;
        this->key = key_to_int;

        this->tabla.resize(dim);
        this->index = 0;

        

        assert(is_empty());
        assert(!is_valid());
    }
    

    /** @}*/

    /** @name Observers*/
    /** @{*/

    /**
     * @brief Is the table empty?
     * @return true if it is empty.
     */
    bool is_empty()
    {
        
        //TODO
        for (size_t x = 0; x < tabla.size(); x++) 
        {
            if (!tabla[x].empty()) return false;
        }

        return true;
    }

    /**
     * @brief is the cursor at a valid position?
     * @return true if the cursor is at a valid position.
     */
    bool is_valid() const
    {
        
        //TODO

        if( index < dim && !tabla[index].empty() ) return true;
        else return false;
    }

    /**
     * @brief Get the number of valid keys in the table.
     * @return the number of valid keys in the table.
     */
    size_t num_of_valid_keys() const
    {
        
        //TODO
        
        size_t contador = 0;

        for (size_t x = 0; x < tabla.size(); x++) 
            contador = contador + tabla[x].size();
        

        return contador;
    }

    /**
     * @brief Compute the load factor of the table.
     * @return the load factor of the table.
     */
    float load_factor() const
    {
        
        //TODO
        size_t contador = num_of_valid_keys();
        return (float) contador / dim;
    }

    /**
     * @brief Has the table this key?
     * @param k the key to find.
     * @return true if the key is saved into the table.
     * @warning The cursor is not affected by this operation.
     */
    bool has(K const& k) const
    {
        
        //TODO
        //You can use find() but
        //you must remenber to restore the cursor at the end.
        bool res = false;

        auto has_key = hash(key(k));
        if (tabla[has_key].empty()) return res;

        for (auto x = tabla[has_key].begin(); x != tabla[has_key].end(); x++) 
        {
            if ( x->first == k) 
            {
                res=true;
                break;
            }
        }

        return res;
    }


    /**
     * @brief Get the key at cursor.
     * @return return the key of the cursor.
     */
    K const& get_key() const
    {
        
        assert(is_valid());
        //TODO
        return itr->first;
    }

    /**
     * @brief Get tha value at cursor.
     * @return return the value of the cursor.
     */
    V const& get_value() const
    {
        
        assert(is_valid());
        //TODO
        return itr->second;
    }

    /**
     * @brief hash a key value k.
     * @return h = ((int(k)*a + b) % p) % m
     */
    size_t
    hash(uint64_t k) const
    {
        //TODO
        return (((k*a + b) % p) % dim);
    }

    /** @}*/

    /** @name Modifiers*/
    /** @{*/

    /**
     * @brief Find a key value.
     * @return true if the key is found.
     * @post !is_valid() or get_key()==k
     */
    bool find(K const& k)
    {
        
        bool is_found=false;

        //TODO
        //1. hash the key to get the table entry.
        //2. Is the table entry empty
        //2.1 yes, not found
        //2.2 else find into the chain (list) of the entry.
        // !!Remenber to update the cursor state.

        index = hash(key(k));
        if (tabla[index].empty()) return is_found;

        for (itr = tabla[index].begin(); itr != tabla[index].end(); itr++) {
            if (itr->first == k) {
                is_found = true;
                break;
            }
        }

        return is_found;
    }

    /**
     * @brief insert a new entry.
     * If the key is currently in the table, the value is updated.
     * @post is_valid()
     * @post get_key()==k
     * @post get_value()==v;
     * @post not old(has(k)) -> num_of_valid_keys() = old(num_of_valid_keys())+1
     */
    void insert(K const& k, V const& v)
    {
        
#ifndef NDEBUG //In Relase mode this macro is defined.
        bool old_has = has(k);
        size_t old_num_of_valid_keys = num_of_valid_keys();
#endif
        //TODO
        //1. find the key.
        //2.1 if it is found, reset the value part.
        //2.2 else, add the new pair (key,value) to the entry chain.
        //Remenber to update the cursor state and the valid keys counter.

        if (find(k)) {
            itr->second++;
        }
        else {
            index = hash(key(k));
            tabla[index].push_front(std::make_pair(k, v));
            itr = tabla[index].begin();
        }

        if (load_factor() > 0.9) {
            rehash();
        }

        assert(is_valid());
        assert(get_key()==k);
        assert(get_value()==v);
        assert(old_has || (num_of_valid_keys()==old_num_of_valid_keys+1));
    }

    /**
     * @brief remove the entry at the cursor position.
     * The cursor will be move to the next valid position if there is.
     * @pre is_valid()
     * @post !is_valid() || old(goto_next() && get_key())==get_key()
     * @post num_of_valid_keys() = old(num_of_valid_keys())-1
     */
    void remove()
    {
        
        assert(is_valid());
#ifndef NDEBUG //In Relase mode this macro is defined.
        size_t old_n_valid_keys = num_of_valid_keys();
#endif        

        //TODO
        //First save the current cursor state.
        auto aux_index = index;
        auto aux_it = itr;
        //

        goto_next(); //move the cursor to next position.
          
        //TODO
        //Second, remove the old cursor position.
        tabla[aux_index].erase(aux_it);

        //
        
        assert( (num_of_valid_keys()+1)==old_n_valid_keys );
        return;
    }

    /**
     * @brief set the value of the entry at the cursor position.
     */

    
    void set_value(const V& v)
    {
        
        assert(is_valid());
        //TODO
        itr->second = v;
    }
    

    /**
     * @brief rehash the table to double size.
     * @warning A new hash function is random selected.
     * @post old.is_valid() implies is_valid() && old.get_key()==get_key() && old.get_value()==get_value()
     */
    void rehash()
    {
        
#ifndef NDEBUG  //In Relase mode this macro is defined.
        bool old_is_valid = is_valid();
        K old_key;
        V old_value;
        if (old_is_valid)
        {
            old_key = get_key();
            old_value = get_value();
        }
#endif
        //1. Save the state of the cursor.
        auto aux_key = get_key();

        //2. Pick up at random a new h.
        //uint64_t P = /*TODO use here the coefficiente P used for the hash function.*/ 0;
        uint64_t P = p;
        const uint64_t a = 1 + static_cast<uint64_t>(std::rand()/(RAND_MAX+1.0) * static_cast<double>(P-1));
        const uint64_t b = static_cast<uint64_t>(std::rand()/(RAND_MAX+1.0) * static_cast<double>(P));

        //3. Create a new table with double size with the new hash.
        //size_t M = /*TODO use the current table size.*/ 0;
        size_t M = dim;
        HashTable<K, V, keyToInt> new_table (M*2, a, b);

        //TODO
        //4. Traversal the old table inserting the values into the new.
        //4.1 goto to the first entry.
        //4.2 while isValid() do
        //4.3    insert in new table current pair key,value
        //4.4    goto next entry.
        goto_begin();
        while (is_valid()) {
            new_table.insert(get_key(), get_value());
            goto_next();
        }

        //TODO
        //5 commute the new_table with this.
        //THIS DEPENDS ON YOUR IMPLEMENTATION.
        //CHECK CAREFULY IF YOU NEED OR NOT TO
        //OVERLOAD THE ASSIGN OPERATOR.
        (*this) = new_table;

        //TODO
        //6. Before returning, the cursor must be restored
        //to the same state that old state.
        //
        find(aux_key);

        //post condition
        assert(!old_is_valid || (is_valid() && old_key==get_key() && old_value==get_value()));
    }

    /**
     * @brief move the cursor to the first valid entry.
     * @post is_empty() || is_valid()
     */
    void goto_begin()
    {
        
        //TODO
        for (index = 0; index < tabla.size(); index++) {
            if (is_valid()) break;
        }
        itr = tabla[index].begin();
        
        assert(is_empty() || is_valid());
    }

    /**
     * @brief Move the cursor to next valid position.
     * @post not is_valid() marks none any more valid entry exists.
     */
    void goto_next()
    {
        
        assert(is_valid());
        //TODO
        
        if(++itr == tabla[index].end()){
            index++;
            while(!is_valid() && index < dim){
                
                index++;
                
            }
            itr = tabla[index].begin();
        }
        
    }
    /** @} */

protected:

    //TODO
    //Care must be taken about the type of the attributes.
    //It is recommended to use types that not imply to overload
    //the assign operator used in the rehash method.

    std::vector< std::list<std::pair< K, V> > > tabla;

    size_t index;

    typename std::list<std::pair<K, V>>::iterator itr;

    size_t dim;
    uint64_t a, b, p;
    keyToInt key;

};

#endif
