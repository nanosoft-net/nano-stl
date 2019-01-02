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

#ifndef IARRAY_H
#define IARRAY_H

#include "IContainer.h"
#include "IIterable.h"

namespace nano_stl
{

/** \brief Interface for all arrays implementations */
template <typename ItemType>
class IArray : public IContainer<ItemType>, public IIterable<ItemType>
{
    public:

        /** \brief Get an item at a specified index */
        virtual ItemType& operator [] (const nano_stl_size_t index) = 0;

        /** \brief Get an item at a specified index */
        virtual const ItemType& operator [] (const nano_stl_size_t index) const = 0;

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        // Iterator forward declaration
        class Iterator;

        /** \brief Const iterator */
        class ConstIterator : public IConstIterator<ItemType>
        {
            public:

                /** \brief Constructor */
                ConstIterator(const IArray<ItemType>& array)
                : m_array(&array)
                , m_current(0u)
                {}

                /** \brief Constructor */
                ConstIterator(const IArray<ItemType>& array, const nano_stl_size_t position)
                : m_array(&array)
                , m_current(position)
                {}

                /** \brief Copy constructor */
                ConstIterator(const ConstIterator& copy)
                : m_array(copy.m_array)
                , m_current(copy.m_current)
                {}

                /**\brief Conversion constructor */
                ConstIterator(const Iterator& it)
                : m_array(it.m_array)
                , m_current(it.m_current)
                {}

                /** \brief Get the element at the current position */
                virtual const ItemType& operator * ()
                {
                    return m_array->operator[](m_current);
                }

                /** \brief Move to the next element */
                virtual void operator ++ ()
                {
                    if (m_current < m_array->getCount())
                    {
                        m_current++;
                        if (m_current == m_array->getCount())
                        {
                            m_current = IIteratorBase<ItemType>::INVALID_POSITION;
                        }
                    }
                }

                /** \brief Move to the previous element */
                virtual void operator -- ()
                {
                    if (m_current != 0u)
                    {
                        m_current--;
                    }
                }

                /** \brief Get the position of an iterator */
                virtual nano_stl_size_t getPosition() const { return m_current; }

                /** \brief Get the iterable instance */
                virtual const IIterable<ItemType>& getIterable() const { return (*m_array); }

                /** \brief Copy operator */
                ConstIterator& operator = (const ConstIterator& copy)
                {
                    m_array = copy.m_array;
                    m_current = copy.m_current;
                    return (*this);
                }

                /** \brief Copy operator */
                ConstIterator& operator = (const Iterator& copy)
                {
                    m_array = copy.m_array;
                    m_current = copy.m_current;
                    return (*this);
                }

            private:

                /** \brief Underlying IArray object */
                const IArray<ItemType>* m_array;

                /** \brief Current position */
                nano_stl_size_t m_current;
        };

        /** \brief Iterator */
        class Iterator : public IIterator<ItemType>
        {
                /* To allow conversion to ConstIterator */
                friend class ConstIterator;

            public:

                /** \brief Constructor */
                Iterator(IArray<ItemType>& array)
                : m_array(&array)
                , m_current(0u)
                {}

                /** \brief Constructor */
                Iterator(IArray<ItemType>& array, const nano_stl_size_t position)
                : m_array(&array)
                , m_current(position)
                {}

                /** \brief Copy constructor */
                Iterator(const Iterator& copy)
                : m_array(copy.m_array)
                , m_current(copy.m_current)
                {}

                /** \brief Get the element at the current position */
                virtual ItemType& operator * ()
                {
                    return m_array->operator[](m_current);
                }

                /** \brief Move to the next element */
                virtual void operator ++ ()
                {
                    if (m_current < m_array->getCount())
                    {
                        m_current++;
                        if (m_current == m_array->getCount())
                        {
                            m_current = IIteratorBase<ItemType>::INVALID_POSITION;
                        }
                    }
                }

                /** \brief Move to the previous element */
                virtual void operator -- ()
                {
                    if (m_current != 0u)
                    {
                        m_current--;
                    }
                }

                /** \brief Get the position of an iterator */
                virtual nano_stl_size_t getPosition() const { return m_current; }

                /** \brief Get the iterable instance */
                virtual const IIterable<ItemType>& getIterable() const { return (*m_array); }

                /** \brief Copy operator */
                Iterator& operator = (const Iterator& copy)
                {
                    m_array = copy.m_array;
                    m_current = copy.m_current;
                    return (*this);
                }

            private:

                /** \brief Underlying IArray object */
                IArray<ItemType>* m_array;

                /** \brief Current position */
                nano_stl_size_t m_current;
        };

#endif // NANO_STL_ITERATORS_ENABLED

};

}

#endif // IARRAY_H
