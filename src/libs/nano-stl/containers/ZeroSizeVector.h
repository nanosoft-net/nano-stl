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

#ifndef ZEROSIZEVECTOR_H
#define ZEROSIZEVECTOR_H

#include "IVector.h"

namespace nano_stl
{

/** \brief Implements a vector of size 0 */
template <typename ItemType>
class ZeroSizeVector : public IVector<ItemType>
{
    public:


        /** \brief Constructor */
        ZeroSizeVector()
        : m_begin(*this, 0u)
        , m_end(*this, IIteratorBase<ItemType>::INVALID_POSITION)
        , m_it(*this, 0u)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)
        {}

        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const { return 0u; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const { return 0u; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const { return false; }


        ////// Implementation of IIterable interface //////

        
        /** \brief Get the iterator which points to the start of the container */
        virtual const IIterator<ItemType>& begin() const { return m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        virtual const IIterator<ItemType>& end() const { return m_end; }

        /** \brief Get the iterator of the container */
        virtual IIterator<ItemType>& it() { return m_it; }

        /** \brief Get the const iterator which points to the start of the container */
        virtual const IConstIterator<ItemType>& cbegin() const { return m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        virtual const IConstIterator<ItemType>& cend() const { return m_const_end; }

        /** \brief Get the const iterator of the container */
        virtual IConstIterator<ItemType>& const_it() const { return (*m_pconst_it); }


        ////// Implementation of IArray interface //////


        /** \brief Get an item at a specified index */
        virtual ItemType& operator [] (const nano_stl_size_t index)
        {
            return (*reinterpret_cast<ItemType*>(NULL));
        }

        /** \brief Get an item at a specified index */
        virtual const ItemType& operator [] (const nano_stl_size_t index) const
        {
            return (*reinterpret_cast<ItemType*>(NULL));
        }


        ////// Implementation of IVector interface //////


        /** \brief Add an item at the end of the vector */
        virtual bool pushBack(const ItemType& item) { (void)item; return false; }

        /** \brief Remove the item at the end of the vector */
        virtual bool popBack(ItemType& item) { (void)item; return false; }

        /** \brief Remove all the items from the vector */
        virtual void clear() {}


    private:

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

};

}

#endif // ZEROSIZEVECTOR_H
