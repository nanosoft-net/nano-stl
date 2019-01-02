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

#ifndef ILIST_H
#define ILIST_H

#include "IContainer.h"
#include "IIterable.h"

namespace nano_stl
{

/** \brief Interface for all lists implementations */
template <typename ItemType>
class IList : public IContainer<ItemType>, public IIterable<ItemType>
{
    public:

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        // Iterator forward declaration
        class Iterator;
        class ConstIterator;

#endif // NANO_STL_ITERATORS_ENABLED

        /** \brief Add an item at the start of the list */
        virtual bool pushFront(const ItemType& item) = 0;

        /** \brief Remove the item at the start of the list */
        virtual bool popFront(ItemType& item) = 0;

        /** \brief Add an item at the end of the list */
        virtual bool pushBack(const ItemType& item) = 0;

        /** \brief Remove the item at the end of the list */
        virtual bool popBack(ItemType& item) = 0;

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        /** \brief Insert an item at a specific location (before item pointed by the iterator) */
        virtual bool insert(const Iterator& position, const ItemType& item) = 0;

        /** \brief Remove an item at a specific location */
        virtual bool remove(const Iterator& position) = 0;

        /** \brief Remove a range of items (item pointed by the last iterator is not removed) */
        virtual bool remove(const Iterator& first, const Iterator& last) = 0;

        /** \brief Remove all the items from the list */
        virtual void clear() = 0;

#endif // NANO_STL_ITERATORS_ENABLED


    protected:

        /** \brief List item */
        struct Item
        {
            /* Value */
            ItemType value;
            /* Previous item */
            Item* previous;
            /* Next item */
            Item* next;
        };

        /** \brief Get the first item of the list */
        virtual Item* getFirst() const = 0;

        /** \brief Get the last item of the list */
        virtual Item* getLast() const = 0;

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        /** \brief Get the underlying item of an iterator */
        Item* getItem(const Iterator& it) const { return it.m_current; }

        /** \brief Get the underlying item of a const iterator */
        const Item* getItem(const ConstIterator& it) const { return it.m_current; }


    public:


        /** \brief Const iterator */
        class ConstIterator : public IConstIterator<ItemType>
        {
                /* To allow access to current item */
                friend class IList;
                
            public:

                /** \brief Constructor */
                ConstIterator(const IList<ItemType>& list)
                : m_list(&list)
                , m_current(m_list.getFirst())
                , m_position((m_current == NULL) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Constructor */
                ConstIterator(const IList<ItemType>& list, const typename IList<ItemType>::Item* const position)
                : m_list(&list)
                , m_current(position)
                , m_position((m_current == NULL) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Copy constructor */
                ConstIterator(const ConstIterator& copy)
                : m_list(copy.m_list)
                , m_current(copy.m_current)
                , m_position(copy.m_position)
                {}

                /**\brief Conversion constructor */
                ConstIterator(const Iterator& it)
                : m_list(it.m_list)
                , m_current(it.m_current)
                , m_position(it.m_position)
                {}

                /** \brief Get the element at the current position */
                virtual const ItemType& operator * ()
                {
                    return m_current->value;
                }

                /** \brief Move to the next element */
                virtual void operator ++ ()
                {
                    if (m_current != NULL)
                    {
                        m_current = m_current->next;
                        if (m_current == NULL)
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
                    if (m_current != NULL)
                    {
                        if (m_current->previous != NULL)
                        {
                            m_current = m_current->previous;
                            m_position--;
                        }
                    }
                }

                /** \brief Get the position of an iterator */
                virtual nano_stl_size_t getPosition() const { return m_position; }

                /** \brief Get the iterable instance */
                virtual const IIterable<ItemType>& getIterable() const { return (*m_list); }

                /** \brief Copy operator */
                ConstIterator& operator = (const ConstIterator& copy)
                {
                    m_list = copy.m_list;
                    m_current = copy.m_current;
                    m_position = copy.m_position;
                    return (*this);
                }

                /** \brief Copy operator */
                ConstIterator& operator = (const Iterator& copy)
                {
                    m_list = copy.m_list;
                    m_current = copy.m_current;
                    m_position = copy.m_position;
                    return (*this);
                }

            private:

                /** \brief Underlying IList object */
                const IList<ItemType>* m_list;

                /** \brief Current position */
                const typename IList<ItemType>::Item* m_current;

                /** \brief Current position */
                nano_stl_size_t m_position;
        };

        /** \brief Iterator */
        class Iterator : public IIterator<ItemType>
        {
                /* To allow conversion to ConstIterator */
                friend class ConstIterator;

                /* To allow access to current item */
                friend class IList;

            public:

                /** \brief Constructor */
                Iterator(IList<ItemType>& list)
                : m_list(&list)
                , m_current(m_list->getFirst())
                , m_position((m_current == NULL) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Constructor */
                Iterator(IList<ItemType>& list, typename IList<ItemType>::Item* const position)
                : m_list(&list)
                , m_current(position)
                , m_position((m_current == NULL) ? IIteratorBase<ItemType>::INVALID_POSITION : 0u)
                {}

                /** \brief Copy constructor */
                Iterator(const Iterator& copy)
                : m_list(copy.m_list)
                , m_current(copy.m_current)
                , m_position(copy.m_position)
                {}

                /** \brief Get the element at the current position */
                virtual ItemType& operator * ()
                {
                    return m_current->value;
                }

                /** \brief Move to the next element */
                virtual void operator ++ ()
                {
                    if (m_current != NULL)
                    {
                        m_current = m_current->next;
                        if (m_current == NULL)
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
                    if (m_current != NULL)
                    {
                        if (m_current->previous != NULL)
                        {
                            m_current = m_current->previous;
                            m_position--;
                        }
                    }
                }

                /** \brief Get the position of an iterator */
                virtual nano_stl_size_t getPosition() const { return m_position; }

                /** \brief Get the iterable instance */
                virtual const IIterable<ItemType>& getIterable() const { return (*m_list); }

                /** \brief Copy operator */
                Iterator& operator = (const Iterator& copy)
                {
                    m_list = copy.m_list;
                    m_current = copy.m_current;
                    m_position = copy.m_position;
                    return (*this);
                }

            private:

                /** \brief Underlying IList object */
                IList<ItemType>* m_list;

                /** \brief Current position */
                typename IList<ItemType>::Item* m_current;

                /** \brief Current position */
                nano_stl_size_t m_position;
        };

#endif // NANO_STL_ITERATORS_ENABLED

};

}

#endif // ILIST_H
