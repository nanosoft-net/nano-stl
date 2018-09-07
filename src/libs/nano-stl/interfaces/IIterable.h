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

#ifndef IITERABLE_H
#define IITERABLE_H

#include "IIterator.h"

namespace nano_stl
{


/** \brief Interface for all iterable containers */
template <typename ItemType>
class IIterable
{
    public:

        /** \brief Get the iterator which points to the start of the container */
        virtual const IIterator<ItemType>& begin() const = 0;

        /** \brief Get the iterator which points to the end of the container */
        virtual const IIterator<ItemType>& end() const = 0;

        /** \brief Get the iterator of the container */
        virtual IIterator<ItemType>& it() = 0;

        /** \brief Get the const iterator which points to the start of the container */
        virtual const IConstIterator<ItemType>& cbegin() const = 0;

        /** \brief Get the const iterator which points to the end of the container */
        virtual const IConstIterator<ItemType>& cend() const = 0;

        /** \brief Get the const iterator of the container */
        virtual IConstIterator<ItemType>& const_it() const = 0;
};

}

#endif // IITERABLE_H
