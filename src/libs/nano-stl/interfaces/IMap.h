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

#ifndef IMAP_H
#define IMAP_H

#include "IContainer.h"
#include "IIterable.h"

namespace nano_stl
{

/** \brief Interface for all maps implementations */
template <typename KeyType, typename ItemType>
class IMap : public IContainer<ItemType>, public IIterable<ItemType>
{
    public:

        /** \brief Get the item corresponding to a key */
        virtual ItemType& operator [] (const KeyType& key) = 0;

        /** \brief Get the item corresponding to a key */
        virtual const ItemType& operator [] (const KeyType& key) const = 0;

        /** \brief Add an item to the map */
        virtual bool add(const KeyType& key, const ItemType& item) = 0;

        /** \brief Check if the map contains a specific key */
        virtual bool containsKey(const KeyType& key) const = 0;

        /** \brief Get an item from the map */
        virtual bool get(const KeyType& key, ItemType& item) const = 0;

        /** \brief Remove an item from the map */
        virtual bool remove(const KeyType& key) = 0;

        /** \brief Remove all the items from the map */
        virtual void clear() = 0;


    protected:

        /** \brief Mode node */
        struct Node
        {
            /** \brief Pointer to the item */
            const ItemType* pitem;
            /** \brief Item */
            ItemType item;
            /** \brief Next node */
            Node* next;
            /** \brief Previous node */
            Node* previous;

            /** \brief Copy operator */
            Node& operator = (const Node& copy)
            {
                if (copy.pitem != nullptr)
                {
                    if (pitem != nullptr)
                    {
                        pitem = copy.pitem;
                    }
                    else
                    {
                        item = (*copy.pitem);
                    }
                }
                else
                {
                    if (pitem != nullptr)
                    {
                        pitem = &copy.item;
                    }
                    else
                    {
                        item = copy.item;
                    }
                }
                return (*this);
            }

            /** \brief Comparison operator */
            bool operator == (const Node& node) const
            {
                bool equals;

                if (node.pitem != nullptr)
                {
                    if (pitem != nullptr)
                    {
                        equals = (pitem == node.pitem);
                    }
                    else
                    {
                        equals = (item == (*node.pitem));
                    }
                }
                else
                {
                    if (pitem != nullptr)
                    {
                        equals = (pitem == &node.item);
                    }
                    else
                    {
                        equals = (item == node.item);
                    }
                }

                return equals;
            }
        };


        /** \brief Get the first item of the map */
        virtual Node* getFirst() const = 0;

        /** \brief Get the last item of the map */
        virtual Node* getLast() const = 0;


    public:

        // Iterator forward declaration
        class Iterator;

        /** \brief Const iterator */
        class ConstIterator : public IConstIterator<ItemType>
        {
                /* To allow access to current item */
                friend class IMap;
                
            public:

                /** \brief Constructor */
                ConstIterator(const IMap<KeyType, ItemType>& map)
                : m_map(&map)
                , m_current(m_map.getFirst())
                , m_position((m_current == nullptr) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Constructor */
                ConstIterator(const IMap<KeyType, ItemType>& map, const typename IMap<KeyType, ItemType>::Node* const position)
                : m_map(&map)
                , m_current(position)
                , m_position((m_current == nullptr) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Copy constructor */
                ConstIterator(const ConstIterator& copy)
                : m_map(copy.m_map)
                , m_current(copy.m_current)
                , m_position(copy.m_position)
                {}

                /**\brief Conversion constructor */
                ConstIterator(const Iterator& it)
                : m_map(it.m_map)
                , m_current(it.m_current)
                , m_position(it.m_position)
                {}

                /** \brief Get the element at the current position */
                virtual const ItemType& operator * ()
                {
                    return m_current->item;
                }

                /** \brief Move to the next element */
                virtual void operator ++ ()
                {
                    if (m_current != nullptr)
                    {
                        m_current = m_current->next;
                        if (m_current == nullptr)
                        {
                            m_position = IIteratorBase<ItemType>::INVALID_POSITION;
                        }
                        else
                        {
                            m_position++;
                        }
                    }
                }

                /** \brief Move to the previous element */
                virtual void operator -- ()
                {
                    if (m_current != nullptr)
                    {
                        if (m_current->previous != nullptr)
                        {
                            m_current = m_current->previous;
                            m_position--;
                        }
                    }
                }

                /** \brief Get the position of an iterator */
                virtual nano_stl_size_t getPosition() const { return m_position; }

                /** \brief Get the iterable instance */
                virtual const IIterable<ItemType>& getIterable() const { return (*m_map); }

                /** \brief Copy operator */
                ConstIterator& operator = (const ConstIterator& copy)
                {
                    m_map = copy.m_map;
                    m_current = copy.m_current;
                    m_position = copy.m_position;
                    return (*this);
                }

                /** \brief Copy operator */
                ConstIterator& operator = (const Iterator& copy)
                {
                    m_map = copy.m_map;
                    m_current = copy.m_current;
                    m_position = copy.m_position;
                    return (*this);
                }

            private:

                /** \brief Underlying IMap object */
                const IMap<KeyType, ItemType>* m_map;

                /** \brief Current position */
                const typename IMap<KeyType, ItemType>::Node* m_current;

                /** \brief Current position */
                nano_stl_size_t m_position;
        };

        /** \brief Iterator */
        class Iterator : public IIterator<ItemType>
        {
                /* To allow conversion to ConstIterator */
                friend class ConstIterator;

                /* To allow access to current item */
                friend class IMap;

            public:

                /** \brief Constructor */
                Iterator(IMap<KeyType, ItemType>& map)
                : m_map(&map)
                , m_current(m_map->getFirst())
                , m_position((m_current == nullptr) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Constructor */
                Iterator(IMap<KeyType, ItemType>& map, typename IMap<KeyType, ItemType>::Node* const position)
                : m_map(&map)
                , m_current(position)
                , m_position((m_current == nullptr) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Copy constructor */
                Iterator(const Iterator& copy)
                : m_map(copy.m_map)
                , m_current(copy.m_current)
                , m_position(copy.m_position)
                {}

                /** \brief Get the element at the current position */
                virtual ItemType& operator * ()
                {
                    return m_current->item;
                }

                /** \brief Move to the next element */
                virtual void operator ++ ()
                {
                    if (m_current != nullptr)
                    {
                        m_current = m_current->next;
                        if (m_current == nullptr)
                        {
                            m_position = IIteratorBase<ItemType>::INVALID_POSITION;
                        }
                        else
                        {
                            m_position++;
                        }
                    }
                }

                /** \brief Move to the previous element */
                virtual void operator -- ()
                {
                    if (m_current != nullptr)
                    {
                        if (m_current->previous != nullptr)
                        {
                            m_current = m_current->previous;
                            m_position--;
                        }
                    }
                }

                /** \brief Get the position of an iterator */
                virtual nano_stl_size_t getPosition() const { return m_position; }

                /** \brief Get the iterable instance */
                virtual const IIterable<ItemType>& getIterable() const { return (*m_map); }

                /** \brief Copy operator */
                Iterator& operator = (const Iterator& copy)
                {
                    m_map = copy.m_map;
                    m_current = copy.m_current;
                    m_position = copy.m_position;
                    return (*this);
                }

            private:

                /** \brief Underlying IMap object */
                IMap<KeyType, ItemType>* m_map;

                /** \brief Current position */
                typename IMap<KeyType, ItemType>::Node* m_current;

                /** \brief Current position */
                nano_stl_size_t m_position;
        };


};

}

#endif // IMAP_H
