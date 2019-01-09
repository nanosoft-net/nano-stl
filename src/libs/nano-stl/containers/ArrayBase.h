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

#ifndef ARRAYBASE_H
#define ARRAYBASE_H

#include "IArray.h"
#include "IErrorHandler.h"

namespace nano_stl
{

/** \brief Base class for all arrays implementations */
template <typename ItemType>
class ArrayBase : public IArray<ItemType>
{
    public:    

        /** \brief Constructor */
        ArrayBase(ItemType* const items, const nano_stl_size_t size)
        : m_items(items)
        , m_size(size)

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        , m_begin(*this, 0u)
        , m_end(*this, IIteratorBase<ItemType>::INVALID_POSITION)
        , m_it(*this, 0u)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)

#endif // NANO_STL_ITERATORS_ENABLED
        {}


        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const override { return m_size; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const override { return m_size; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const override
        {
            bool found = false;

            for (nano_stl_size_t index = 0u; !found && (index < m_size); index++)
            {
                if (item == m_items[index])
                {
                    found = true;
                }
            }

            return found;
        }


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        ////// Implementation of IIterable interface //////

        
        /** \brief Get the iterator which points to the start of the container */
        virtual const IIterator<ItemType>& begin() const override { return m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        virtual const IIterator<ItemType>& end() const override { return m_end; }

        /** \brief Get the iterator of the container */
        virtual IIterator<ItemType>& it() override { begin(m_it); return m_it; }

        /** \brief Get the const iterator which points to the start of the container */
        virtual const IConstIterator<ItemType>& cbegin() const override { return m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        virtual const IConstIterator<ItemType>& cend() const override { return m_const_end; }

        /** \brief Get the const iterator of the container */
        virtual IConstIterator<ItemType>& const_it() const override { cbegin(*m_pconst_it); return (*m_pconst_it); }

#endif // NANO_STL_ITERATORS_ENABLED


        ////// Implementation of IArray interface //////


        /** \brief Get an item at a specified index */
        virtual ItemType& operator [] (const nano_stl_size_t index) override
        {
            #if (NANO_STL_ITEM_ACCESS_CHECK_ENABLE == 1)
            if (index >= m_size)
            {
                NANO_STL_CRITICAL_ERROR();
            }
            #endif // NANO_STL_ITEM_ACCESS_CHECK_ENABLE

            return m_items[index];
        }

        /** \brief Get an item at a specified index */
        virtual const ItemType& operator [] (const nano_stl_size_t index) const override
        {
            #if (NANO_STL_ITEM_ACCESS_CHECK_ENABLE == 1)
            if (index >= m_size)
            {
                NANO_STL_CRITICAL_ERROR();
            }
            #endif // NANO_STL_ITEM_ACCESS_CHECK_ENABLE

            return m_items[index];
        }


        ////// Implementation of ArrayBase methods //////


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        /** \brief Get the iterator which points to the start of the container */
        const void begin(typename IArray<ItemType>::Iterator& it) const { it = m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        const void end(typename IArray<ItemType>::Iterator& it) const { it = m_end; }

        /** \brief Get the const iterator which points to the start of the container */
        const void cbegin(typename IArray<ItemType>::ConstIterator& it) const { it = m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        const void cend(typename IArray<ItemType>::ConstIterator& it) const { it = m_const_end; }

#endif // NANO_STL_ITERATORS_ENABLED


    private:

        /** \brief Underlying C array */
        ItemType* const m_items;

        /** \brief Underlying C array size */
        const nano_stl_size_t m_size;


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        /** \brief Iterator to the beginning of the array */
        const typename IArray<ItemType>::Iterator m_begin;

        /** \brief Iterator to the end of the array */
        const typename IArray<ItemType>::Iterator m_end;

        /** \brief Iterator of the container */
        typename IArray<ItemType>::Iterator m_it;

        /** \brief Iterator to the beginning of the array */
        const typename IArray<ItemType>::ConstIterator m_const_begin;

        /** \brief Iterator to the end of the array */
        const typename IArray<ItemType>::ConstIterator m_const_end;

        /** \brief Const iterator of the container */
        typename IArray<ItemType>::ConstIterator m_const_it;

        /** \brief Pointer to the const iterator of the container */
        typename IArray<ItemType>::ConstIterator* const m_pconst_it;

#endif // NANO_STL_ITERATORS_ENABLED

};

}

#endif // ARRAYBASE_H
