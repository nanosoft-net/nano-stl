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

#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "ArrayBase.h"

namespace nano_stl
{

/** \brief Static array implementation 
 *         The array memory is statically allocated by the class.
*/
template <typename ItemType, nano_stl_size_t MAX_ITEM_COUNT>
class StaticArray : public ArrayBase<ItemType>
{
    public:

        /** \brief Constructor */
        StaticArray() : ArrayBase<ItemType>(m_items, MAX_ITEM_COUNT)
        {}

    private:

        /** \brief Internal C array */
        ItemType m_items[MAX_ITEM_COUNT];

};

}

#endif // STATICARRAY_H
