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

#ifndef IVECTOR_H
#define IVECTOR_H

#include "IArray.h"

namespace nano_stl
{

/** \brief Interface for all vectors implementations */
template <typename ItemType>
class IVector : public IArray<ItemType>
{
    public:

        /** \brief Add an item at the end of the vector */
        virtual bool pushBack(const ItemType& item) = 0;

        /** \brief Remove the item at the end of the vector */
        virtual bool popBack(ItemType& item) = 0;

        /** \brief Remove all the items from the vector */
        virtual void clear() = 0;
};

}

#endif // IVECTOR_H
