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

#ifndef STATICBSTREE_H
#define STATICBSTREE_H

#include "BSTreeBase.h"

namespace nano_stl
{

/** \brief Static binary search tree implementation 
 *         The binary search tree memory is statically allocated by the class.
*/
template <typename KeyType, typename ItemType, nano_stl_size_t MAX_NODE_COUNT>
class StaticBSTree : public BSTreeBase<KeyType, ItemType>
{
    public:

        /** \brief Constructor */
        StaticBSTree() : BSTreeBase<KeyType, ItemType>(m_nodes, MAX_NODE_COUNT)
        {}

    private:

        /** \brief Internal C array */
        typename BSTreeBase<KeyType, ItemType>::Node m_nodes[MAX_NODE_COUNT];

};

}

#endif // STATICBSTREE_H
