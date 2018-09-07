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

#ifndef STATICMAP_H
#define STATICMAP_H

#include "MapBase.h"
#include "StaticBSTree.h"

namespace nano_stl
{

/** \brief Static map implementation 
 *         The map memory is statically allocated by the class.
*/
template <typename KeyType, typename ItemType, nano_stl_size_t MAX_ITEM_COUNT>
class StaticMap : public MapBase<KeyType, ItemType>
{
    public:

        /** \brief Constructor */
        StaticMap() : MapBase<KeyType, ItemType>(m_bstree)
        {}

    private:

        /** \brief Internal binary search tree */
        StaticBSTree<KeyType, typename IMap<KeyType, ItemType>::Node, MAX_ITEM_COUNT> m_bstree;

};

}

#endif // STATICMAP_H
