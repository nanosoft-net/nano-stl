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

#ifndef IRINGBUFFER_H
#define IRINGBUFFER_H

#include "IContainer.h"

namespace nano_stl
{

/** \brief Interface for all ring buffers implementations */
template <typename ItemType>
class IRingBuffer : public IContainer<ItemType>
{
    public:

        /** \brief Write an item into the ring buffer */
        virtual bool write(const ItemType& item) = 0;

        /** \brief Read an item from the ring buffer */
        virtual bool read(ItemType& item) = 0;

        /** \brief Remove all the items from the ring buffer */
        virtual void clear() = 0;

};

}

#endif // IRINGBUFFER_H
