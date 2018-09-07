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

#ifndef STATICLIST_H
#define STATICLIST_H

#include "ListBase.h"

namespace nano_stl
{

/** \brief Static list implementation 
 *         The list memory is statically allocated by the class.
*/
template <typename ItemType, nano_stl_size_t MAX_ITEM_COUNT>
class StaticList : public ListBase<ItemType>
{
    public:

        /** \brief Constructor */
        StaticList() : ListBase<ItemType>(m_items, MAX_ITEM_COUNT)
        {}

    private:

        /** \brief Internal C array */
        typename IList<ItemType>::Item m_items[MAX_ITEM_COUNT];

};

}

#endif // STATICLIST_H
