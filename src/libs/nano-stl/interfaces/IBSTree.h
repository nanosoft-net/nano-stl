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

#ifndef IBSTREE_H
#define IBSTREE_H

#include "IContainer.h"

namespace nano_stl
{

/** \brief Interface for all binary search tree implementations */
template <typename KeyType, typename ItemType>
class IBSTree : public IContainer<ItemType>
{
    public:

        /** \brief Get the item corresponding to a key */
        virtual ItemType& operator [] (const KeyType& key) = 0;

        /** \brief Get the item corresponding to a key */
        virtual const ItemType& operator [] (const KeyType& key) const = 0;

        /** \brief Add an item to the binary search tree */
        virtual bool add(const KeyType& key, const ItemType& item) = 0;

        /** \brief Check if the binary search tree contains a specific key */
        virtual bool containsKey(const KeyType& key) const = 0;

        /** \brief Get an item from the binary search tree */
        virtual bool get(const KeyType& key, ItemType& item) const = 0;

        /** \brief Remove an item from the binary search tree */
        virtual bool remove(const KeyType& key) = 0;

        /** \brief Remove all the items from the binary search tree */
        virtual void clear() = 0;

        /** \brief Get the last item which has been modified */
        virtual ItemType* getLastModified() = 0;

        /** \brief Get the last item which has been modified */
        virtual const ItemType* getLastModified() const = 0;
};

}

#endif // IBSTREE_H
