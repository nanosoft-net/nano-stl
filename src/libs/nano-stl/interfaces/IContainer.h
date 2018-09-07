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

#ifndef ICONTAINER_H
#define ICONTAINER_H

#include "nano-stl-conf.h"

namespace nano_stl
{



/** \brief Interface for all containers implementations */
template <typename ItemType>
class IContainer
{
    public:

        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const = 0;

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const = 0;

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const = 0;
};

}

#endif // ICONTAINER_H
