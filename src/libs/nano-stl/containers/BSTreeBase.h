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

#ifndef BSTREEBASE_H
#define BSTREEBASE_H

#include "IBSTree.h"

namespace nano_stl
{

/** \brief Base class for all binary search tree implementations */
template <typename KeyType, typename ItemType>
class BSTreeBase : public IBSTree<KeyType, ItemType>
{
    public:
        
        /** \brief Binary search tree node */
        struct Node
        {
            /** \brief Key */
            KeyType key;
            /** \brief Item */
            ItemType item;
            /** \brief Left node */
            Node* left;
            /** \brief Right node */
            Node* right;
        };


        /** \brief Constructor */
        BSTreeBase(Node* const nodes, const nano_stl_size_t size)
        : m_nodes(nodes)
        , m_size(size)
        , m_count(0u)
        , m_root(nullptr)
        , m_first_free(nodes)
        , m_last_modified(nullptr)
        {
            // Initialize free list
            initFreeList();
        }


        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const { return m_size; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const { return m_count; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const
        {
            bool contains = false;

            if (m_root != nullptr)
            {
                contains = nodeContains(m_root, item);
            }

            return contains;
        }


        ////// Implementation of IBSTree interface //////


        /** \brief Get the item corresponding to a key */
        virtual ItemType& operator [] (const KeyType& key)
        {
            bool left = false;
            Node* current = nullptr;
            Node* parent = nullptr;
            if (lookForKey(key, current, parent, left))
            {
                return current->item;
            }
            else
            {
                return (*reinterpret_cast<ItemType*>(nullptr));
            }
        }

        /** \brief Get the item corresponding to a key */
        virtual const ItemType& operator [] (const KeyType& key) const
        {
            bool left = false;
            Node* current = nullptr;
            Node* parent = nullptr;
            if (lookForKey(key, current, parent, left))
            {
                return current->item;
            }
            else
            {
                return (*reinterpret_cast<const ItemType*>(nullptr));
            }
        }

        /** \brief Add an item to the binary search tree */
        virtual bool add(const KeyType& key, const ItemType& item)
        {
            bool ret = false;

            // Check for free space
            if (m_first_free != nullptr)
            {
                // Look for the key
                bool left = false;
                Node* current = nullptr;
                Node* parent = nullptr;
                const bool found = lookForKey(key, current, parent, left);
                if (!found)
                {
                    Node* const new_node = m_first_free;
                    m_last_modified = &new_node->item;

                    // Remove node from free list
                    m_first_free = m_first_free->right;

                    // Init node
                    new_node->key = key;
                    new_node->item = item;
                    new_node->left = nullptr;
                    new_node->right = nullptr;

                    if (parent == nullptr)
                    {
                        m_root = new_node;
                    }
                    else
                    {
                        if (left)
                        {
                            parent->left = new_node;
                        }
                        else
                        {
                            parent->right = new_node;
                        }
                    }

                    // Update count
                    m_count++;

                    ret = true;
                }
            }

            return ret;
        }

        /** \brief Check if the binary search tree contains a specific key */
        virtual bool containsKey(const KeyType& key) const
        {
            bool left = false;
            Node* current = nullptr;
            Node* parent = nullptr;
            return lookForKey(key, current, parent, left);
        }

        /** \brief Get an item from the binary search tree */
        virtual bool get(const KeyType& key, ItemType& item) const
        {
            // Look for the item
            bool left = false;
            Node* current = nullptr;
            Node* parent = nullptr;
            const bool found = lookForKey(key, current, parent, left);
            if (found)
            {
                // Update item value
                item = current->item;
            }

            return found;
        }

        /** \brief Remove an item from the binary search tree */
        virtual bool remove(const KeyType& key)
        {
            // Look for the item
            bool left = false;
            Node* current = nullptr;
            Node* parent = nullptr;
            const bool found = lookForKey(key, current, parent, left);
            if (found)
            {
                // Remove item node
                Node* child = nullptr;
                if (current->right == nullptr)
                {
                    child = current->left;
                }
                else
                {
                    child = current->right;
                    if (current->left != nullptr)
                    {
                        Node* previous = current->right;
                        Node* most_left_node = current->right->left;
                        while (most_left_node != nullptr)
                        {
                            previous = most_left_node;
                            most_left_node = most_left_node->left;
                        }
                        previous->left = current->left;
                    }
                }

                // Affect new child node to parent
                if (parent != nullptr)
                {
                    if (left)
                    {
                        parent->left = child;
                    }
                    else
                    {
                        parent->right = child;
                    }
                }
                else
                {
                    m_root = child;
                }

                // Add deleted node to the free list
                current->right = m_first_free;
                m_first_free = current;
                m_last_modified = &current->item;

                // Update count
                m_count--;
            }

            return found;
        }

        /** \brief Remove all the items from the binary search tree */
        virtual void clear()
        {
            if (m_count != 0u)
            {
                // Put back all the nodes into the free list
                initFreeList();

                // Clear list
                m_count = 0u;
                m_root = nullptr;
                m_last_modified = 0u;
            }
        }

        /** \brief Get the last item which has been modified */
        virtual ItemType* getLastModified() { return m_last_modified; }

        /** \brief Get the last item which has been modified */
        virtual const ItemType* getLastModified() const { return m_last_modified; }


    private:

        /** \brief Underlying C array */
        Node* const m_nodes;

        /** \brief Underlying C array size */
        const nano_stl_size_t m_size;

        /** \brief Node count */
        nano_stl_size_t m_count;

        /** \brief Root node */
        Node* m_root;

        /** \brief First free node */
        Node* m_first_free;

        /** \brief Last modified item */
        ItemType* m_last_modified;



        /** \brief Initializes the free nodes list */
        void initFreeList()
        {
            // Put back all the nodes into the free list
            m_first_free = m_nodes;
            for (nano_stl_size_t i = 0; i < (m_size - 1u); i++)
            {
                m_first_free[i].right = &m_first_free[i+1];
            }
            m_first_free[m_size - 1u].right = nullptr;
        }

        /** \brief Look for a key in the binary search tree */
        bool lookForKey(const KeyType& key, Node*& current, Node*& parent, bool& left) const
        {
            bool found = false;

            left = false;
            parent = nullptr;
            current = m_root;
            while (!found && (current != nullptr))
            {
                if (key > current->key)
                {
                    left = false;
                    parent = current;
                    current = current->right;
                }
                else if (key < current->key)
                {
                    left = true;
                    parent = current;
                    current = current->left;
                }
                else
                {
                    found = true;
                }
            }

            return found;
        }

        /** \brief Recursivly checks if a node or its childs contains a specific item */
        bool nodeContains(const Node* const node, const ItemType& item) const
        {
            bool contains = false;

            if (node->item == item)
            {
                contains = true;
            }
            else
            {
                if (node->left != nullptr)
                {
                    contains = nodeContains(node->left, item);
                }
                if (!contains && (node->right != nullptr))
                {
                    contains = nodeContains(node->right, item);
                }
            }

            return contains;
        }
};

}

#endif // BSTREEBASE_H
