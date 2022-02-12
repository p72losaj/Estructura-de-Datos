#ifndef __ED_AVLTree_HPP__
#define __ED_AVLTree_HPP__

#include <cassert>
#include <exception>
#include <functional>
#include <memory>
#include <iostream>

/** @brief a AVLTree's Node.*/
template <class T>
class AVLTNode
{
public:

    /** @brief Define a shared reference to a AVLTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< AVLTNode<T> > Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create a AVLTNode.
     * @post n_children() == 0
     */
    AVLTNode (T const& it=T(), AVLTNode<T>::Ref parent=nullptr, AVLTNode<T>::Ref left=nullptr, AVLTNode<T>::Ref right=nullptr):
        _item(it), parent_(parent), left_(left), right_(right), height_(0)
    {}

    /** @brief Destroy a AVLTNode. **/
    ~AVLTNode()
    {}

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T& item() const
    {
        return _item;
    }

    /** @brief Get the node's height.*/
    int height() const
    {
        return height_;
    }

    /** @brief Compute the balance factor of the node.*/
    int balance_factor() const
    {
      int l_h=0, r_h=0;
      if(has_left())
      {
      	left_->compute_height();
        l_h=left_->height()+1;
      }
      if(has_right())
      {
      	right_->compute_height();
        r_h=right_->height()+1;
      }
      return r_h-l_h;
    }

    /** @brief Has it a parent?*/
    bool has_parent() const
    {
        return parent_ != nullptr;
    }

    /** @brief get the parent.*/
    const AVLTNode<T>::Ref& parent() const
    {
        return parent_;
    }

    /** @brief get the parent.*/
    AVLTNode<T>::Ref& parent()
    {
        return parent_;
    }

    /** @brief Has it a left child?*/
    bool has_left() const
    {
        return left_ != nullptr;
    }

    /** @brief get the left child.*/
    const AVLTNode<T>::Ref& left() const
    {
        return left_;
    }

    /** @brief get the left child.*/
    AVLTNode<T>::Ref& left()
    {
        return left_;
    }

    /** @brief Has it a right child? */
    bool has_right() const
    {
        return right_ != nullptr;
    }

    /** @brief get the right child.*/
    const AVLTNode<T>::Ref& right() const
    {
        return right_;
    }

    /** @brief get the right child.*/
    AVLTNode<T>::Ref& right()
    {
        return right_;
    }

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T& new_it)
    {
        _item = new_it;
    }

    /** @brief Set the parent.*/
    void set_parent(AVLTNode<T>::Ref const& new_parent)
    {
        parent_ = new_parent;
    }

    /** @brief Remove link to the left child. */
    void remove_parent()
    {
        parent_.reset();
    }

    /** @brief Set the left child.*/
    void set_left(AVLTNode<T>::Ref const& new_child)
    {
        left_ = new_child;
    }

    /** @brief Remove link to the left child. */
    void remove_left()
    {
        left_.reset();
    }

    /** @brief Set the right child.*/
    void set_right(AVLTNode<T>::Ref const& new_child)
    {
        right_ = new_child;
    }

    /** @brief Remove link to the right child. */
    void remove_right()
    {
        right_.reset();
    }

    /** @brief Compute height. */
    void compute_height()
    {
      //NODO NO TIENE HIJOS Y SU PADRE ACABA DE DEJAR DE SER NODO HOJA
      if(!has_left()&&!has_right())
      {
        height_=0;
        if(has_parent())
        {
          parent_->compute_height();
        }
        //NODO TIENE HIJOS Y SU ALTURA COINCIDE CON UNA DE LA DE SUS HIJOS
      }else if(has_right()||has_left())
      {
        int l_h=0, r_h=0;
        if(has_left())
        {
          l_h=left_->height();
        }
        if(has_right())
        {
          r_h=right_->height();
        } 
        if(l_h>r_h)
        {
          height_=l_h+1;
        }else
        {
          height_=r_h+1;
        }
        if(has_parent())
        {
          parent_->compute_height();
        }
      }
    }

protected:
    T _item;
    AVLTNode<T>::Ref parent_;
    AVLTNode<T>::Ref left_;
    AVLTNode<T>::Ref right_;
    int height_;
};

/**
 * @brief ADT AVLTree.
 * Models a AVLTree of T.
 */
template<class T>
class AVLTree
{
  public:

  /** @name Life cicle.*/
  /** @{*/

    /** @brief Create an empty AVLTree.
     * @post is_empty()
     */
    AVLTree ()
    {
      _root=nullptr;
      parent_=nullptr;
      current_=nullptr;
    }

    /**
     * @brief Create a AVLTree using a given node as root.
     * @post not is_empty()
     * @post not current_exists()
    */
    AVLTree (typename AVLTNode<T>::Ref& new_root)
    {
        _root=new_root;
        current_=nullptr;
        assert(!is_empty());
        assert(!current_exists());
    }

    /** @brief Destroy a AVLTree.**/
    ~AVLTree()
    {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      if(_root==nullptr)
      {
          return true;
      }
      return false;
  }

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T const& item() const
  {
      return _root->item();
  }

  /** @brief Is the cursor at a valid position?*/
  bool current_exists() const
  {
      if(current_!=nullptr)
      {
        return true;
      }
      return false;
  }

  /**
   * @brief Get the current key.
   * @pre current_exists()
   */
  T const& current() const
  {
      //check preconditions.
      assert(current_exists());      
      return current_->item();
  }

  /** @brief Get the root node.*/
  typename AVLTNode<T>::Ref const& root() const
  {
      return _root;
  }

  /** @brief Get the root node.*/
  typename AVLTNode<T>::Ref root()
  {
      return _root;
  }

  /** @brief Has the tree got this key */
  bool has(const T& k) const
  {
      //check invariants.
      assert(is_a_binary_search_subtree(root()));
      assert(is_a_balanced_subtree(root()));
      if(_root==nullptr)
      {
        return false;
      }
      typename AVLTNode<T>::Ref cursor=_root;
      bool found=false;
      bool ended=false;
      do
      {
        if(cursor->item()==k)
        {
            found=true;
        }else if((cursor->has_left())&&(cursor->item()>k))
        {
            cursor=cursor->left();
        }else if((cursor->has_right())&&(cursor->item()<k))
        {
            cursor=cursor->right();
        }else
        {
            ended=true;
        }

      }while((found==false)&&(ended==false));
      return found;
  }

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /** @brief set a new root node.*/
  void set_root(typename AVLTNode<T>::Ref& new_root)
  {
      _root=new_root;
      _root->compute_height();
      assert(is_a_binary_search_subtree(root()));
     assert(is_a_balanced_subtree(root()));
  }

  /**
   * @brief Search a key moving the cursor.
   * @post retV implies current()==k
   * @post not retv implies not current_exits()
   */
  bool search(T const& k)
  {
      //check invariants.
      assert(is_a_binary_search_subtree(_root));
      //assert(is_a_balanced_subtree(_root));
      bool found = false;
      bool limit = false;
      current_ = _root;
      do
      {
          if(current()==k)
          {
              found=true;
          }else if((current_->has_left())&&(current()>k))
          {
              current_=current_->left();
          }else if((current_->has_right())&&(current()<k))
          {
              current_=current_->right();
          }else
          {
              limit=true;
          }
      }while((found==false)&&(limit==false));


      //check invariants.
      assert(is_a_binary_search_subtree(_root));
      assert(is_a_balanced_subtree(_root));
      if((limit==true)&&(found==false))
      {
          current_=nullptr;
      }else
      {
        if(current_->has_parent())
        {
          parent_=current_->parent();
        }
      }
      assert(!found || current()==k);
      assert(found || !current_exists());
      return found;
  }

  /**
   * @brief Insert a new key in the tree.
   * @pre not has(k)
   * @post current_exists()
   * @post current()==k
   */
  void insert(T const& k)
  {
      //preconditions.
      assert(! has(k));

      //check invariants.
      assert(is_a_binary_search_subtree(root()));
	  assert(is_a_balanced_subtree(root()));

      //TODO
      //First delivery, only the invariant for a Binary Search Tree
      //must be met.
      if(_root==nullptr)
      {
        typename AVLTNode<T>::Ref new_node = std::make_shared<AVLTNode<T>>();
        new_node->set_item(k);
        set_root(new_node);
        current_=_root;
      }else
      {
        current_=_root;
        bool settled=false;
        do
        {
          if(current_exists()==true)
          {
            if(k<current())
            {
              if(current_->has_left())
              {
                current_=current_->left();
              }else
              {
                typename AVLTNode<T>::Ref new_node = std::make_shared<AVLTNode<T>>();
                new_node->set_item(k);
                new_node->set_parent(current_);
                current_->set_left(new_node);
                current_=current_->left();
                parent_=current_->parent();
                current_->compute_height(); //Para computar alturas desde current
                settled=true;
              }
            }else
            {
               if(current_->has_right())
              {
                current_=current_->right();
              }else
              {
                typename AVLTNode<T>::Ref new_node = std::make_shared<AVLTNode<T>>();
                new_node->set_item(k);
                new_node->set_parent(current_);
                current_->set_right(new_node);
                current_=current_->right();
                parent_=current_->parent();
                current_->compute_height(); //Para computar alturas desde current
                settled=true;
              }
            }
          }
        }while(settled==false);
      }

      ////////////////////////
      
      make_balanced();
      
      //check invariants.
      assert(is_a_binary_search_subtree(root()));
      assert(is_a_balanced_subtree(root()));

      //check postconditions.
      assert(current_exists());
      assert(current()==k);
  }

  /**
   * @brief remove current from the tree.
   * @pre current_exists()
   * @post not current_exists()
   */
  void remove ()
  {
      //check preconditions.
      assert(current_exists());

      // @WARNING Here, we must not check invariants because this function could be called
      // in recursion and then the invariants are not met.

      bool replace_with_subtree = true;
      typename AVLTNode<T>::Ref subtree;


      //TODO: first delivery
      //Check if there are one subtree (may be empty) to replace node to be removed.
      if(current_->has_left()||current_->has_right())
      {
        if(current_->has_left()&&current_->has_right())
        {
          replace_with_subtree=false;
        }else
        {
          if(current_->has_left())
          {
            subtree=current_->left();
          }else if(current_->has_right())
          {
            subtree=current_->right();
          }
        }
        if(replace_with_subtree)//Caso 1 y 2 tiene un nodo hijo.
        {
            //TODO: first delivery
            //Replace the node with the subtree.
            if(current_->parent()==nullptr)//en caso en el que vayamos a borrar root
            {
              _root=subtree;
              current_=nullptr;
            }else//caso en el que el current a borrar no es root
            {
              parent_=current_->parent();
              if(parent_->right()->item()==current())
              {
                parent_->set_right(subtree);
                current_=nullptr;
              }else
              {

                parent_->set_left(subtree);
                current_=nullptr;
              }
            }
        }
        else
        {
            //Remove case 3.
            auto tmp = current_;
            find_inorder_sucessor();
            tmp->set_item(current_->item());
            remove();
        }
      }else//caso 0: no tiene nodos hijos
      {
        parent_=current_->parent();

        if(parent_->has_left()&&parent_->left()->item()==current())
        {
          parent_->remove_left();
          current_=nullptr;
        }else
        {
          parent_->remove_right();
          current_=nullptr;
        }
        assert(! current_exists());
      }
      make_balanced();
            //check invariants.
            assert(is_a_binary_search_subtree(root()));
            assert(is_a_balanced_subtree(root()));

            //check postconditions.
            assert(! current_exists());

      // @WARNING Here, we must not check the
      // postconditions and invariants because this function could be called
      // in recursion and then the invariants are not met.
  }



  /** @}*/

private:

  /** @brief desactivate Copy constructor. */
  AVLTree(const AVLTree<T>& other);

  /** @brief desactivate assign operator. */
  AVLTree<T>& operator =(const AVLTree<T>& other);

protected:

  /**
   * @brief Move current to its in order sucessor.
   */
  void find_inorder_sucessor()
  {
    auto l=current_->left();
    auto r=current_->right();
    if(r->has_left())
    {
      current_=r->left();
    }else if(!r->has_left()&& !r->has_right())
    {
      current_=r;
    }else if(l->has_right())
    {
      current_=l->right();
    }else
    {
      current_=l;
    }
  }


  /**
   * @brief make a left rotation.
   * @warning it is posible there is none grand parent (==nullptr).
   */
  void rotate_left(typename AVLTNode<T>::Ref& child,
                   typename AVLTNode<T>::Ref& parent,
                   typename AVLTNode<T>::Ref& grand_parent)
  {
      //TODO: second delivery.
      //First update grand parent link.
      //If there is not grand parent, the child will be
      //the new root of the tree.
     if(grand_parent!=nullptr)
     {
        //ACTUALIZAMOS LINKS
        if(parent->has_left())
        {
          auto l=parent->left();
          grand_parent->set_right(l);
          l->set_parent(grand_parent);
          parent->remove_left();
        }else
        {
          grand_parent->remove_right();
          
        }

        if(grand_parent->has_parent())
        {
          auto p_gp=grand_parent->parent();
          if(p_gp->right()==grand_parent)
          {
            p_gp->set_right(parent);
          }else
          {
            p_gp->set_left(parent);
          }
          parent->set_parent(p_gp);
          grand_parent->set_parent(parent);
          parent->set_left(grand_parent);
        }else
        {
          parent->remove_parent();
          grand_parent->set_parent(parent);
          parent->set_left(grand_parent);
        }
        if(_root->has_parent())
        {
          _root=_root->parent();
        }

      }else
      {//REVISAR POR UNION INFINITA
        if(parent->has_parent())
        {
          auto p_p = parent->parent();
          if(p_p->left()==parent)
          {
            p_p->set_left(child);
            child->set_parent(p_p);
          }else
          {
            p_p->set_right(child);        
            child->set_parent(p_p);
          }
          parent->set_parent(child);
          parent->remove_right();
          if(child->has_left())
          {
          	auto l=child->left();
          	l->set_parent(parent);
          	parent->set_right(l);
          }
          child->set_left(parent);
        }else
        {
          parent->set_parent(child);
          parent->remove_right();
          child->remove_parent();
          child->set_left(parent);
        }
      }
      //ACTUALIZAMOS LA VARIABLE ROOT DEL ARBOL EN CASO DE VERSE MODIFICADA
      //CALCULAMOS ALTURAS DE PARENT Y CHILD
      if(grand_parent!=nullptr)
      {
        parent->compute_height();     
      }else
      {
        parent->compute_height();
        child->compute_height();
      }   

      
      //TODO: second delivery.
      //second update child<->parent links.



      //TODO: second delivery.
      //Update heigths for parent, child and grandparent if there is.


  }
  /**
   * @brief make a right rotation.
   * @warning it is posible there is none grand parent (==nullptr).
   */

  void rotate_right(typename AVLTNode<T>::Ref& child,
                    typename AVLTNode<T>::Ref& parent,
                    typename AVLTNode<T>::Ref& grand_parent)
  {
      //TODO: second delivery.
      //First update grand parent link.
      //If there is not grand parent, the child will be
      //the new root of the tree.
      if(grand_parent!=nullptr)
     {
        //ACTUALIZAMOS LINKS
        if(parent->has_right())
        {
          auto r=parent->right();
          grand_parent->set_left(r);
          r->set_parent(grand_parent);
          parent->remove_right();
        }else
        {
          grand_parent->remove_left();

        }

        if(grand_parent->has_parent())
        {
          auto p_gp=grand_parent->parent();
          if(p_gp->left()==grand_parent)
          {
            p_gp->set_left(parent);
          }else
          {
            p_gp->set_right(parent);
          }
          parent->set_parent(p_gp);
          grand_parent->set_parent(parent);
          parent->set_right(grand_parent);
        }else
        {
          parent->remove_parent();
          grand_parent->set_parent(parent);
          parent->set_right(grand_parent);
        }

      }else
      {
        if(parent->has_parent())
        {
          //exit(0);
          auto p_p = parent->parent();
          if(p_p->left()==parent)
          {
            p_p->set_left(child);
          }else
          {
            p_p->set_right(child);
          }
          parent->set_parent(child);
          parent->remove_left();
          if(child->has_right())
          {
          	auto r=child->right();
          	r->set_parent(parent);
          	parent->set_left(r);
          }
          
	          child->set_right(parent);
	          child->set_parent(p_p);
        }else
        {
          parent->set_parent(child);
          parent->remove_left();
          child->set_right(parent);
          child->remove_parent();
        }
      }
      //CALCULAMOS ALTURAS DE PARENT Y CHILD
      if(_root->has_parent())
      {
        _root=_root->parent();
      }
      if(grand_parent!=nullptr)
      {
        grand_parent->compute_height();

      }else
      {
        parent->compute_height();
        child->compute_height();
      }


      //TODO: second delivery.
      //second update child<->parent links.



      //TODO: second delivery.
      //Update heigths for parent, child and grandparent if there is.


  }
  /**
   * @brief make a balanced tree.
   */
  void make_balanced()
  {
      while(parent_)
      {
          //TODO: second delivery.
          //First, update parent height.
          parent_->compute_height();

          //TODO: second delivery.
          //Second, check balance factors.
          int bf = parent_->balance_factor();
          if (bf < -1)//ARBOL MAS LARGO EN LA IZQUIERDA
          {
              //The subtree is left un-banlaced.
              //Get the grand-parent link.
          	  auto child=parent_->left();
              //Check the left child balanced factor.
              int bf_child = child->balance_factor();

              if (bf_child <= 0)
              {
              	
              		auto l=child->left();
                  typename AVLTNode<T>::Ref null=nullptr;
                    rotate_right(l,child,parent_);

              }
              else
              {
                  typename AVLTNode<T>::Ref null=nullptr;
                  auto temp=child->right();
                  typename AVLTNode<T>::Ref temp2;
                  rotate_left(temp,child,null);
                  temp=parent_->left();
                  temp2=temp->left();
                  rotate_right(temp2,temp,parent_);

              }
              
          }
          else if (bf > 1)//ARBOL MAS LARGO EN LA DERECHA
          {              
              //The subtree is right un-balanced.
              //get the grand-parent link.
                auto child = parent_->right();

              //Check the child balanced factor.
              int bf_child = child->balance_factor();

              if (bf_child>=0)
              {
                  //TODO: second delivery
                  //We have a Case 2.
                  //right-right unbalanced.
              	auto r=child->right();
                rotate_left(r,child,parent_);
              }
              else
              {
                  //TODO: second delivery
                  //We have a Case 4.
                  //right-left unbalanced.
                typename AVLTNode<T>::Ref null=nullptr;
                auto temp=child->left();
                rotate_right(temp,child,null);

                typename AVLTNode<T>::Ref  temp2;
                temp=parent_->right();
                temp2=temp->right();
                rotate_left(temp2,temp,parent_);
                temp->compute_height();

                //exit(0);
              }
          }
          else
          {
              //The subtree is balanced. Go up.
              parent_ = parent_->parent();
          }
      }
  }
  /**
   * @brief Check the binary search tree invariant.
   * @param node is the subtree's root.
   * @return true of the subtree with node as root is a binary search tree.
   */
  bool is_a_binary_search_subtree(typename AVLTNode<T>::Ref const& node) const
  {
      bool r=false;
      bool l=false;
      int t=0;//comprueba que se hayan visitado los hijos
      if(node==nullptr)
      {
        return true;
      }
      if(node->has_left())
      {
          l=true;
      }
      if(node->has_right())
      {
          r=true;
      }
      if((l==false)&&(r==false))
      {
        return true;
      }else
      {
          if((l==true))
          {
            if(node->item()>node->left()->item())
            {
              is_a_binary_search_subtree(node->left());
              t++;
            }else
            {
              return false;
            }
          }
          if(r==true)
          {
            if(node->item()<node->right()->item())
            {
             is_a_binary_search_subtree(node->left());
             t++;
            }else
            {
              return false;
            }
          }
          if(t==0)
          {
              return false;
          }else
          {
              return true;
          }
      }
  }

  /**
   * @brief check the balanced tree invariant.
   * @param node is the subtree's root.
   * @return true if the subtree with node as root is balanced.
   */
  bool is_a_balanced_subtree(typename AVLTNode<T>::Ref const& node) const
  {
  	if(node==nullptr)
  	{
  		return true;
  	}else
  	{
		int bf=node->balance_factor();
		if(bf>=2||bf<=-2)
		{
			return false;
		}
		if(node->has_right()==false&&node->has_right()==false)
		{
			return true;
		}else
		{
			bool r_bf=true, l_bf=true;
			if(node->has_left())
			{
				l_bf=is_a_balanced_subtree(node->left());
			}
			if(node->has_right())
			{
				r_bf=is_a_balanced_subtree(node->right());
			}
			if(r_bf==false||l_bf==false)
			{
				return false;
			}else
			{
				return true;
			}
		}
	}
  }
  typename AVLTNode<T>::Ref _root;
  typename AVLTNode<T>::Ref current_;
  typename AVLTNode<T>::Ref parent_;

};


/**  @brief Fold an avl tree node.
 * The output format will be:
 * [<item> : <left> : <right>] or [] if its a empty node.
*/
template<class T>
std::ostream&
fold_AVLTNode (std::ostream& out, typename AVLTNode<T>::Ref const& node)
{
    out << '[';
    if (node != nullptr)
    {
        out << node->item() << " : ";
        fold_AVLTNode<T>(out, node->left());
        out << " : ";
        fold_AVLTNode<T>(out, node->right());
    }
    out << ']';
    return out;
}

/**  @brief Fold an avl tree. */
template<class T>
std::ostream&
operator << ( std::ostream& out, AVLTree<T> const& tree)
{
    fold_AVLTNode<T> (out, tree.root());
    return out;
}

/** @brief Load an AVLTNode from a input stream.
 * @return the node on success.
 * @warning runtime_error will throw if worng input format is found.
 */
template<class T>
std::istream&
operator >> (std::istream& in, typename AVLTNode<T>::Ref& node) noexcept(false)
{
    char sep=' ';
    while(in && sep!='[')
        in >> sep;
    if (!in)
        throw std::runtime_error("Wrong input format.");
    sep = static_cast<char>(in.peek());
    if (sep != ']')
    {
        T item;
        in >> item;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        while(in && sep!=':')
            in >> sep;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        typename AVLTNode<T>::Ref left;
        in >> left;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        while(in && sep!=':')
            in >> sep;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        typename AVLTNode<T>::Ref right;
        in >> right;
        if (!in)
            throw std::runtime_error("Wrong input format.");
        node = std::make_shared< AVLTNode<T> >(item, left, right);
    }
    else
        in >> sep;//remove the close bracket from stream.
    return in;
}

/** @brief Load an avl tree from a input stream.
 * @warning runtime_error will throw if worng input format is found.
 */
template<class T>
std::istream&
operator >> (std::istream& in, AVLTree<T>& tree)
{
    typename AVLTNode<T>::Ref root;
    in >> root;
    if (in)
        tree.set_root(root);
    return in;
}

#endif
