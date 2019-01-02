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

#ifndef LISTBASE_H
#define LISTBASE_H

#include "IList.h"

namespace nano_stl
{

/** \brief Base class for all lists implementations */
template <typename ItemType>
class ListBase : public IList<ItemType>
{
    public:

        

        /** \brief Constructor */
        ListBase(typename IList<ItemType>::Item* const items, const nano_stl_size_t size)
        : m_items(items)
        , m_size(size)
        , m_count(0u)
        , m_first(nullptr)
        , m_last(nullptr)
        , m_first_free(items)
        , m_begin(*this, nullptr)
        , m_end(*this, nullptr)
        , m_it(*this, nullptr)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)
        {
            // Initialize free list
            for (uint32_t i = 0; i < (size - 1u); i++)
            {
                m_first_free[i].next = &m_first_free[i+1];
            }
            m_first_free[size - 1u].next = nullptr;
        }


        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const { return m_size; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const { return m_count; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const
        {
            bool found = false;

            typename IList<ItemType>::Item* current = m_first;
            while (!found && (current != nullptr))
            {
                if (item == current->value)
                {
                    found = true;
                }
                else
                {
                    current = current->next;
                }
            }

            return found;
        }


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


        ////// Implementation of IList interface //////


        /** \brief Add an item at the start of the list */
        virtual bool pushFront(const ItemType& item)
        {
            bool ret = false;

            // Check for free space
            if (m_first_free != nullptr)
            {
                typename IList<ItemType>::Item* const new_item = m_first_free;

                // Remove item from free list
                m_first_free = m_first_free->next;

                // Add item at the start of the list
                new_item->value = item;
                new_item->previous = nullptr;
                new_item->next = m_first;
                if (m_first != nullptr)
                {
                    m_first->previous = new_item;
                }
                setFirst(new_item);

                // Check if the list was empty
                if (m_last == nullptr)
                {
                    setLast(new_item);
                }

                // Update list count
                m_count++;

                ret = true;
            }

            return ret;
        }

        /** \brief Remove the item at the start of the list */
        virtual bool popFront(ItemType& item)
        {
            bool ret = false;

            // Check for empty list
            if (m_first != nullptr)
            {
                typename IList<ItemType>::Item* const del_item = m_first;

                // Remove item from list
                item = m_first->value;
                setFirst(m_first->next);
                if (m_first != nullptr)
                {
                    m_first->previous = nullptr;
                }     
                else
                {
                    setLast(nullptr);
                }           
                

                // Add item to the free list
                del_item->next = m_first_free;
                m_first_free = del_item;

                // Update list count
                m_count--;

                ret = true;
            }

            return ret;
        }

        /** \brief Add an item at the end of the list */
        virtual bool pushBack(const ItemType& item)
        {
            bool ret = false;

            // Check for free space
            if (m_first_free != nullptr)
            {
                typename IList<ItemType>::Item* const new_item = m_first_free;

                // Remove item from free list
                m_first_free = m_first_free->next;

                // Add item at the end of the list
                new_item->value = item;
                new_item->previous = m_last;
                new_item->next = nullptr;
                if (m_last != nullptr)
                {
                    m_last->next = new_item;
                }
                setLast(new_item);

                // Check if the list was empty
                if (m_first == nullptr)
                {
                    setFirst(new_item);
                }

                // Update list count
                m_count++;

                ret = true;
            }

            return ret;
        }

        /** \brief Remove the item at the end of the list */
        virtual bool popBack(ItemType& item)
        {
            bool ret = false;

            // Check for empty list
            if (m_last != nullptr)
            {
                typename IList<ItemType>::Item* const del_item = m_last;

                // Remove item from list
                item = m_last->value;
                setLast(m_last->previous);
                if (m_last != nullptr)
                {
                    m_last->next = nullptr;
                }     
                else
                {
                    setFirst(nullptr);
                }           

                // Add item to the free list
                del_item->next = m_first_free;
                m_first_free = del_item;

                // Update list count
                m_count--;

                ret = true;
            }

            return ret;
        }

        /** \brief Insert an item at a specific location (before item pointed by the iterator) */
        virtual bool insert(const typename IList<ItemType>::Iterator& position, const ItemType& item)
        {
            bool ret = false;

            // Check for free space and matching iterator
            if ((m_first_free != nullptr) && 
                (&position.getIterable() == static_cast<IIterable<ItemType>*>(this)))
            {
                typename IList<ItemType>::Item* const new_item = m_first_free;

                // Remove item from free list
                m_first_free = m_first_free->next;

                // Add item before the selected item
                typename IList<ItemType>::Item* const next_item = IList<ItemType>::getItem(position);
                new_item->value = item;
                new_item->next = next_item;
                if (next_item != nullptr)
                {
                    new_item->previous = next_item->previous;
                    if (next_item->previous != nullptr)
                    {
                        next_item->previous->next = new_item;
                    }
                }
                else
                {
                    if (m_last != nullptr)
                    {
                        m_last->next = new_item;
                        new_item->previous = m_last;
                    }
                    setLast(new_item);
                }
                if ((m_first == nullptr) || (m_first == next_item))
                {
                    setFirst(new_item);
                    new_item->previous = nullptr;
                }

                // Update list count
                m_count++;

                ret = true;
            }

            return ret;
        }

        /** \brief Remove an item at a specific location */
        virtual bool remove(const typename IList<ItemType>::Iterator& position)
        {
            bool ret = false;

            // Check for free space and matching iterator
            if ((m_first_free != nullptr) && 
                (&position.getIterable() == static_cast<IIterable<ItemType>*>(this)))
            {
                // Remove the item
                typename IList<ItemType>::Iterator last(position);
                ++last;
                ret = remove(position, last);
            }

            return ret;
        }

        /** \brief Remove a range of items (item pointed by the last iterator is not removed) */
        virtual bool remove(const typename IList<ItemType>::Iterator& first, const typename IList<ItemType>::Iterator& last)
        {
            bool ret = false;

            // Check for already empty list and matching iterator
            if ((m_count != 0u) && 
                (first != last) &&
                (&first.getIterable() == static_cast<IIterable<ItemType>*>(this)) &&
                (&last.getIterable() == static_cast<IIterable<ItemType>*>(this)) &&
                (last.getPosition() > first.getPosition()))
            {
                // Get the first and the last item to remove
                typename IList<ItemType>::Item* const first_item = IList<ItemType>::getItem(first);
                typename IList<ItemType>::Item* const last_item = IList<ItemType>::getItem(last);

                // Remove items
                if (first_item->previous != nullptr)
                {
                    first_item->previous->next = last_item;
                }                
                else
                {
                    setFirst(last_item);
                }
                if (last_item != nullptr)
                {
                    last_item->previous = first_item->previous;
                }
                else
                {
                    setLast(first_item->previous);
                }

                // Update count
                typename IList<ItemType>::Item* item_before_last = nullptr;
                for (typename IList<ItemType>::Item* item = first_item; item != last_item; item = item->next)
                {
                    m_count--;
                    item_before_last = item;
                }

                // Put back items into free list
                item_before_last->next = m_first_free;
                m_first_free = first_item;
                
                ret = true;
            }

            return ret;
        }

        /** \brief Remove all the items from the list */
        virtual void clear()
        {
            // Check for already empty list
            if (m_count != 0u)
            {
                // Put back all the items into the free list
                m_last->next = m_first_free;
                m_first_free = m_first;

                // Clear list
                setFirst(nullptr);
                setLast(nullptr);
                m_count = 0u;
            }
        }

    protected:

        /** \brief Get the first item of the list */
        virtual typename IList<ItemType>::Item* getFirst() const { return m_first; }

        /** \brief Get the last item of the list */
        virtual typename IList<ItemType>::Item* getLast() const { return m_last; }


    public:


        ////// Implementation of ListBase methods //////

        /** \brief Get the iterator which points to the start of the container */
        const void begin(typename IList<ItemType>::Iterator& it) const { it = m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        const void end(typename IList<ItemType>::Iterator& it) const { it = m_end; }

        /** \brief Get the const iterator which points to the start of the container */
        const void cbegin(typename IList<ItemType>::ConstIterator& it) const { it = m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        const void cend(typename IList<ItemType>::ConstIterator& it) const { it = m_const_end; }



    private:

        /** \brief Underlying C array */
        typename IList<ItemType>::Item* const m_items;

        /** \brief Underlying C array size */
        const nano_stl_size_t m_size;

        /** \brief Item count */
        nano_stl_size_t m_count;

        /** \brief First item */
        typename IList<ItemType>::Item* m_first;

        /** \brief Last item */
        typename IList<ItemType>::Item* m_last;

        /** \brief First free item */
        typename IList<ItemType>::Item* m_first_free;


        /** \brief Iterator to the beginning of the list */
        typename IList<ItemType>::Iterator m_begin;

        /** \brief Iterator to the end of the list */
        typename IList<ItemType>::Iterator m_end;

        /** \brief Iterator of the container */
        typename IList<ItemType>::Iterator m_it;

        /** \brief Iterator to the beginning of the list */
        typename IList<ItemType>::ConstIterator m_const_begin;

        /** \brief Iterator to the end of the list */
        typename IList<ItemType>::ConstIterator m_const_end;

        /** \brief Const iterator of the container */
        typename IList<ItemType>::ConstIterator m_const_it;

        /** \brief Pointer to the const iterator of the container */
        typename IList<ItemType>::ConstIterator* const m_pconst_it;


        /** \brief Set the first item of the list and update the iterators */
        void setFirst(typename IList<ItemType>::Item* const first)
        {
            m_first = first;
            m_begin = typename IList<ItemType>::Iterator(*this, m_first);
            m_const_begin = m_begin;
        }

        /** \brief Set the last item of the list and update the iterators */
        void setLast(typename IList<ItemType>::Item* const last)
        {
            m_last = last;
        }  

};

}

#endif // LISTBASE_H
