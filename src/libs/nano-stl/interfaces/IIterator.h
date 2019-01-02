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

#ifndef IITERATOR_H
#define IITERATOR_H

#include "nano-stl-conf.h"


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

namespace nano_stl
{

// Iterable interface forward declaration */
template <typename ItemType>
class IIterable;


/** \brief Interface for all iterators implementations */
template <typename ItemType>
class IIteratorBase
{
    public:

        /** \brief Move to the next element */
        virtual void operator ++ () = 0;

        /** \brief Move to the previous element */
        virtual void operator -- () = 0;

        /** \brief Compare 2 iterators */
        virtual bool operator == (const IIteratorBase<ItemType>& it) const = 0;

        /** \brief Compare 2 iterators */
        virtual bool operator != (const IIteratorBase<ItemType>& it) const = 0;

        /** \brief Get the position of an iterator */
        virtual nano_stl_size_t getPosition() const = 0;

        /** \brief Get the iterable instance */
        virtual const IIterable<ItemType>& getIterable() const = 0;


        /** \brief Invalid iterator position */
        static const nano_stl_size_t INVALID_POSITION = static_cast<nano_stl_size_t>(-1);

};

/** \brief Base class for all iterators implementations */
template <typename ItemType>
class IteratorBase : public IIteratorBase<ItemType>
{
    public:

        /** \brief Compare 2 iterators */
        virtual bool operator == (const IIteratorBase<ItemType>& it) const
        {
            return ((&this->getIterable() == &it.getIterable()) && 
                    (this->getPosition() == it.getPosition()));
        }

        /** \brief Compare 2 iterators */
        virtual bool operator != (const IIteratorBase<ItemType>& it) const
        {
            return !(this->operator==(it));
        }

};

/** \brief Interface for all non const iterators implementations */
template <typename ItemType>
class IIterator : public IteratorBase<ItemType>
{
    public:

        /** \brief Get the element at the current position */
        virtual ItemType& operator * () = 0;

};

/** \brief Interface for all const iterators implementations */
template <typename ItemType>
class IConstIterator : public IteratorBase<ItemType>
{
    public:

        /** \brief Get the element at the current position */
        virtual const ItemType& operator * () = 0;

};

}

#endif // NANO_STL_ITERATORS_ENABLED

#endif // IITERATOR_H
