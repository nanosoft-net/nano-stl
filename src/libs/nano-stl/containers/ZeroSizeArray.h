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

#ifndef ZEROSIZEARRAY_H
#define ZEROSIZEARRAY_H

#include "IArray.h"

namespace nano_stl
{

/** \brief Implements an array of size 0 */
template <typename ItemType>
class ZeroSizeArray : public IArray<ItemType>
{
    public:


        /** \brief Constructor */
        ZeroSizeArray()

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        : m_begin(*this, 0u)
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
        virtual nano_stl_size_t getCapacity() const override { return 0u; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const override { return 0u; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const override { return false; }


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        ////// Implementation of IIterable interface //////

        
        /** \brief Get the iterator which points to the start of the container */
        virtual const IIterator<ItemType>& begin() const override { return m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        virtual const IIterator<ItemType>& end() const override { return m_end; }

        /** \brief Get the iterator of the container */
        virtual IIterator<ItemType>& it() override { return m_it; }

        /** \brief Get the const iterator which points to the start of the container */
        virtual const IConstIterator<ItemType>& cbegin() const override { return m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        virtual const IConstIterator<ItemType>& cend() const override { return m_const_end; }

        /** \brief Get the const iterator of the container */
        virtual IConstIterator<ItemType>& const_it() const override { return (*m_pconst_it); }

#endif // NANO_STL_ITERATORS_ENABLED


        ////// Implementation of IArray interface //////


        /** \brief Get an item at a specified index */
        virtual ItemType& operator [] (const nano_stl_size_t index) override
        {
            return (*reinterpret_cast<ItemType*>(nullptr));
        }

        /** \brief Get an item at a specified index */
        virtual const ItemType& operator [] (const nano_stl_size_t index) const override
        {
            return (*reinterpret_cast<ItemType*>(nullptr));
        }

    private:


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

#endif // ZEROSIZEARRAY_H
