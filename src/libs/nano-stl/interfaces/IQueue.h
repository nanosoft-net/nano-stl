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

#ifndef IQUEUE_H
#define IQUEUE_H

#include "IContainer.h"

namespace nano_stl
{

/** \brief Interface for all queues implementations */
template <typename ItemType>
class IQueue : public IContainer<ItemType>
{
    public:

        /** \brief Remove all the items from the queue */
        virtual bool clear() = 0;

        /** \brief Add an item to the queue */
        virtual bool push(const ItemType& item) = 0;

        /** \brief Remove the oldest item from the queue */
        virtual bool pop(ItemType& item) = 0;

};

}

#endif // IQUEUE_H
