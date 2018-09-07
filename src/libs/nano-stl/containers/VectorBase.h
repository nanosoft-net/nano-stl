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

#ifndef VECTORBASE_H
#define VECTORBASE_H

#include "IVector.h"

namespace nano_stl
{

/** \brief Base class for all vectors implementations */
template <typename ItemType>
class VectorBase : public IVector<ItemType>
{
    public:

        /** \brief Constructor */
        VectorBase(ItemType* const items, const nano_stl_size_t size)
        : m_items(items)
        , m_size(size)
        , m_count(0u)
        , m_begin(*this, IIteratorBase<ItemType>::INVALID_POSITION)
        , m_end(*this, IIteratorBase<ItemType>::INVALID_POSITION)
        , m_it(*this, IIteratorBase<ItemType>::INVALID_POSITION)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)
        {}


        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const { return m_size; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const { return m_count; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const
        {
            bool found = false;

            for (nano_stl_size_t index = 0u; !found && (index < m_count); index++)
            {
                if (item == m_items[index])
                {
                    found = true;
                }
            }

            return found;
        }


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


        ////// Implementation of IArray interface //////


        /** \brief Get an item at a specified index */
        virtual ItemType& operator [] (const nano_stl_size_t index)
        {
            return m_items[index];
        }

        /** \brief Get an item at a specified index */
        virtual const ItemType& operator [] (const nano_stl_size_t index) const
        {
            return m_items[index];
        }


        ////// Implementation of IVector interface //////


        /** \brief Add an item at the end of the vector */
        virtual bool pushBack(const ItemType& item)
        {
            bool ret = false;

            if (m_count < m_size)
            {
                m_items[m_count] = item;
                m_count++;

                // Update iterators
                if (m_count == 1u)
                {
                    m_begin = typename IArray<ItemType>::Iterator(*this, 0u);
                    m_const_begin = m_begin;
                }

                ret = true;
            }

            return ret;
        }

        /** \brief Remove the item at the end of the vector */
        virtual bool popBack(ItemType& item)
        {
            bool ret = false;

            if (m_count != 0u)
            {
                item = m_items[m_count - 1u];
                m_count--;

                // Update iterators
                if (m_count == 0u)
                {
                    m_begin = typename IArray<ItemType>::Iterator(*this, IIteratorBase<ItemType>::INVALID_POSITION);
                    m_const_begin = m_begin;
                }

                ret = true;
            }

            return ret;
        }

        /** \brief Remove all the items from the vector */
        virtual void clear()
        {
            // Update count
            m_count = 0u;

            // Update iterators
            m_begin = typename IArray<ItemType>::Iterator(*this, IIteratorBase<ItemType>::INVALID_POSITION);
            m_const_begin = m_begin;
        }


        ////// Implementation of VectorBase methods //////


        /** \brief Get the iterator which points to the start of the container */
        const void begin(typename IArray<ItemType>::Iterator& it) const { it = m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        const void end(typename IArray<ItemType>::Iterator& it) const { it = m_end; }

        /** \brief Get the const iterator which points to the start of the container */
        const void cbegin(typename IArray<ItemType>::ConstIterator& it) const { it = m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        const void cend(typename IArray<ItemType>::ConstIterator& it) const { it = m_const_end; }



    private:

        /** \brief Underlying C array */
        ItemType* const m_items;

        /** \brief Underlying C array size */
        const nano_stl_size_t m_size;

        /** \brief Item count */
        nano_stl_size_t m_count;


        /** \brief Iterator to the beginning of the array */
        typename IArray<ItemType>::Iterator m_begin;

        /** \brief Iterator to the end of the array */
        typename IArray<ItemType>::Iterator m_end;

        /** \brief Iterator of the container */
        typename IArray<ItemType>::Iterator m_it;

        /** \brief Iterator to the beginning of the array */
        typename IArray<ItemType>::ConstIterator m_const_begin;

        /** \brief Iterator to the end of the array */
        typename IArray<ItemType>::ConstIterator m_const_end;

        /** \brief Const iterator of the container */
        typename IArray<ItemType>::ConstIterator m_const_it;

        /** \brief Pointer to the const iterator of the container */
        typename IArray<ItemType>::ConstIterator* const m_pconst_it;
};

}

#endif // VECTORBASE_H
