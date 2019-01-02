/*
Copyright(c) 2017 Cedric Jimenez

This file is part of Nano-STL.

Nano-STL is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Nano-STL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Nano-STL.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAPBASE_H
#define MAPBASE_H

#include "IMap.h"
#include "IBSTree.h"

namespace nano_stl
{

/** \brief Base class for all maps implementations */
template <typename KeyType, typename ItemType>
class MapBase : public IMap<KeyType, ItemType>
{
    public:

        /** \brief Constructor */
        MapBase(IBSTree<KeyType, typename IMap<KeyType, ItemType>::Node>& bstree)
        : m_bstree(bstree)
        , m_first(nullptr)
        , m_last(nullptr)

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        , m_begin(*this, nullptr)
        , m_end(*this, nullptr)
        , m_it(*this, nullptr)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)
        
#endif // NANO_STL_ITERATORS_ENABLED
        {}


        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const { return m_bstree.getCapacity(); }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const { return m_bstree.getCount(); }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const 
        {
            typename IMap<KeyType, ItemType>::Node node;
            node.pitem = &item;
            return m_bstree.contains(node); 
        }



// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        ////// Implementation of IIterable interface //////


        /** \brief Get the iterator which points to the start of the container */
        virtual const IIterator<ItemType>& begin() const { return m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        virtual const IIterator<ItemType>& end() const { return m_end; }

        /** \brief Get the iterator of the container */
        virtual IIterator<ItemType>& it() { begin(m_it); return m_it; }

        /** \brief Get the const iterator which points to the start of the container */
        virtual const IConstIterator<ItemType>& cbegin() const { return m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        virtual const IConstIterator<ItemType>& cend() const { return m_const_end; }

        /** \brief Get the const iterator of the container */
        virtual IConstIterator<ItemType>& const_it() const { cbegin(*m_pconst_it); return (*m_pconst_it); }

#endif // NANO_STL_ITERATORS_ENABLED


        ////// Implementation of IMap interface //////
        

        /** \brief Get the item corresponding to a key */
        virtual ItemType& operator [] (const KeyType& key) { return m_bstree[key].item; }

        /** \brief Get the item corresponding to a key */
        virtual const ItemType& operator [] (const KeyType& key) const { return m_bstree[key].item; }

        /** \brief Add an item to the map */
        virtual bool add(const KeyType& key, const ItemType& item) 
        {
            typename IMap<KeyType, ItemType>::Node node;
            node.pitem = &item;
            const bool ret = m_bstree.add(key, node);
            if (ret)
            {
                typename IMap<KeyType, ItemType>::Node* added_node = m_bstree.getLastModified();
                added_node->previous = nullptr;
                added_node->next = m_first;
                if (m_first != nullptr)
                {
                    m_first->previous = added_node;
                }
                else
                {
                    setLast(added_node);
                }

                setFirst(added_node);
            }

            return ret;
        }

        /** \brief Check if the map contains a specific key */
        virtual bool containsKey(const KeyType& key) const { return m_bstree.containsKey(key); }

        /** \brief Get an item from the map */
        virtual bool get(const KeyType& key, ItemType& item) const 
        { 
            typename IMap<KeyType, ItemType>::Node node;
            node.pitem = &item;
            
            const bool found = m_bstree.get(key, node); 
            if (found)
            {
                item = (*node.pitem);
            }

            return found;
        }

        /** \brief Remove an item from the map */
        virtual bool remove(const KeyType& key) 
        { 
            const bool ret = m_bstree.remove(key); 
            if (ret)
            {
                typename IMap<KeyType, ItemType>::Node* added_node = m_bstree.getLastModified();
                if (added_node->previous != nullptr)
                {
                    added_node->previous->next = added_node->next;
                }
                else
                {
                    setFirst(added_node->next);
                }
                if (added_node->next != nullptr)
                {
                    added_node->next->previous = added_node->previous;
                }
                else
                {
                    setLast(added_node->previous);
                }                
            }

            return ret;
        }

        /** \brief Remove all the items from the map */
        virtual void clear()
        {
            m_bstree.clear();
            setFirst(nullptr);
            setLast(nullptr);
        }

    protected:

        /** \brief Get the first item of the map */
        virtual typename IMap<KeyType, ItemType>::Node* getFirst() const { return m_first; }

        /** \brief Get the last item of the map */
        virtual typename IMap<KeyType, ItemType>::Node* getLast() const { return m_last; }

    public:


        ////// Implementation of MapBase methods //////


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        /** \brief Get the iterator which points to the start of the container */
        const void begin(typename IMap<KeyType, ItemType>::Iterator& it) const { it = m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        const void end(typename IMap<KeyType, ItemType>::Iterator& it) const { it = m_end; }

        /** \brief Get the const iterator which points to the start of the container */
        const void cbegin(typename IMap<KeyType, ItemType>::ConstIterator& it) const { it = m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        const void cend(typename IMap<KeyType, ItemType>::ConstIterator& it) const { it = m_const_end; }

#endif // NANO_STL_ITERATORS_ENABLED


    private:

        /** \brief Underlying binary search tree */
        IBSTree<KeyType, typename IMap<KeyType, ItemType>::Node>& m_bstree;


        /** \brief First node */
        typename IMap<KeyType, ItemType>::Node* m_first;

        /** \brief Last node */
        typename IMap<KeyType, ItemType>::Node* m_last;


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        /** \brief Iterator to the beginning of the map */
        typename IMap<KeyType, ItemType>::Iterator m_begin;

        /** \brief Iterator to the end of the map */
        typename IMap<KeyType, ItemType>::Iterator m_end;

        /** \brief Iterator of the container */
        typename IMap<KeyType, ItemType>::Iterator m_it;

        /** \brief Iterator to the beginning of the map */
        typename IMap<KeyType, ItemType>::ConstIterator m_const_begin;

        /** \brief Iterator to the end of the map */
        typename IMap<KeyType, ItemType>::ConstIterator m_const_end;

        /** \brief Const iterator of the container */
        typename IMap<KeyType, ItemType>::ConstIterator m_const_it;

        /** \brief Pointer to the const iterator of the container */
        typename IMap<KeyType, ItemType>::ConstIterator* const m_pconst_it;

#endif // NANO_STL_ITERATORS_ENABLED


        /** \brief Set the first node of the list and update the iterators */
        void setFirst(typename IMap<KeyType, ItemType>::Node* const first)
        {
            m_first = first;

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

            m_begin = typename IMap<KeyType, ItemType>::Iterator(*this, m_first);
            m_const_begin = m_begin;

#endif // NANO_STL_ITERATORS_ENABLED
        }

        /** \brief Set the last node of the list and update the iterators */
        void setLast(typename IMap<KeyType, ItemType>::Node* const last)
        {
            m_last = last;
        }  
};

}

#endif // MAPBASE_H
