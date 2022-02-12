#ifndef __ED_BTree_Utils_HPP__
#define __ED_BTree_Utils_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree.hpp"


/** @brief Prefix processing of a node
 * The template class Processor must have an apply interface:
 * bool Processor::apply(BTNode<T>::Ref& node).
 * returning true to continue the process or false to stop it.
 *
 * @arg[in] node is the node to be processed.
 * @arg[in] is the process to be apply to the node item.
 * @pre node.get()!=null
 * @return true if the process must continue.
 */
template <class T, class Processor>
bool
prefix_process(typename BTNode<T>::Ref& node, Processor& p)
{
    assert(node.get()!=nullptr);    

//TODO

    p.apply(node);

    if( node->left() ) prefix_process<T, Processor>( node->left(), p);

    if( node->right() ) prefix_process<T, Processor>( node->right(), p);

    return false;
}

/** @brief Prefix processing of a binary tree
 * The template class Processor must have an apply interface:
 * bool Processor::apply(BTNode<T>::Ref & node).
 * returning true to continue the process or false to stop it.
 *
 * @return true if all nodes were processed.
 */
template <class T, class Processor>
bool
prefix_process(BTree<T>& tree, Processor& p)
{
    bool retVal = true;
    if (!tree.is_empty())
        retVal = prefix_process<T, Processor>(tree.root(), p);
    return retVal;
}

/** @brief Infix processing of a node
 * The template class Processor must have an apply interface:
 * bool Processor::apply(BTNode<T>::Ref& node).
 * returning true to continue the process or false to stop it.
 *
 * @arg[in] node is the node to be processed.
 * @arg[in] is the process to be apply to the node item.
 * @pre node.get()!=null
 * @return true if the process must continue.
 */
template <class T, class Processor>
bool
infix_process(typename BTNode<T>::Ref& node, Processor& p)
{
    assert(node.get()!=nullptr);
//TODO

    if( node->left() ) infix_process <T, Processor> (node->left(), p);
    p.apply(node);
    if( node->right() ) infix_process <T,Processor> (node->right(), p);
    return false;
}

/** @brief Infix processing of a binary tree
 * The template class Processor must have an apply interface:
 * bool Processor::apply(BTNode<T>::Ref & node).
 * returning true to continue the process or false to stop it.
 *
 * @return true if all nodes were processed.
 */
template <class T, class Processor>
bool
infix_process(BTree<T>& tree, Processor& p)
{
    bool retVal = true;
    if (!tree.is_empty())
        retVal = infix_process<T, Processor>(tree.root(), p);
    return retVal;
}

/** @brief Postfix processing of a node
 * The template class Processor must have an apply interface:
 * bool Processor::apply(BTNode<T>::Ref & node).
 * returning true to continue the process or false to stop it.
 *
 * @arg[in] node is the node to be processed.
 * @arg[in] is the process to be apply to the node item.
 * @pre node.get()!=null
 * @return true if the process must continue.
 */
template <class T, class Processor>
bool
postfix_process(typename BTNode<T>::Ref& node, Processor& p)
{
    assert(node.get()!=nullptr);
//TODO

    if( node->left() ) postfix_process <T, Processor> (node->left(), p);
    if( node->right() ) postfix_process <T, Processor> (node->right(), p);
    p.apply(node);
    return false;
}

/** @brief Postfix processing of a binary tree
 * The template class Processor must have an apply interface:
 * bool Processor::apply(BTNode<T>::Ref & node).
 * returning true to continue the process or false to stop it.
 *
 * @return true if all nodes were processed.
 */
template <class T, class Processor>
bool
postfix_process(BTree<T>& tree, Processor& p)
{
    bool retVal = true;
    if (!tree.is_empty())
        retVal = postfix_process<T, Processor>(tree.root(), p);
    return retVal;
}


/** @brief Bread-first processing of a btree.
 * The template class Processor must have an apply interface:
 * bool Processor::apply(BTNode<T>::Ref& node).
 * returning true to continue the process or false to stop it.
 *
 * Wise: should you need a queue?
*/
template <class T, class Processor>
bool
breadth_first_process(BTree<T>& tree, Processor& p)
{
//TODO

    std::queue<typename BTNode<T>::Ref> _cola;

    _cola.push(tree.root());

    BTree <T> arbol;

    while( _cola.empty() == false)
    {
        
        arbol.set_root( _cola.front() );

        _cola.pop();

        p.apply(arbol.root());

        if( arbol.root()->left() ) _cola.push(arbol.root()->left() );

        if( arbol.root()->right() ) _cola.push(arbol.root()->right() );

        
    }
    

    return false;
}



#endif
