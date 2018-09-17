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

#ifndef RINGBUFFERBASE_H
#define RINGBUFFERBASE_H

#include "IRingBuffer.h"

namespace nano_stl
{

/** \brief Base class for all ring buffers implementations */
template <typename ItemType>
class RingBufferBase : public IRingBuffer<ItemType>
{
    public:

        

        /** \brief Constructor */
        RingBufferBase(ItemType* const items, const nano_stl_size_t size)
        : m_items(items)
        , m_size(size)
        , m_count(0u)
        , m_read(m_items)
        , m_write(m_items)
        {}


        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const { return m_size; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const { return m_count; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const ItemType& item) const
        {
            bool found = false;

            ItemType* current = m_read;
            for (nano_stl_size_t index = 0u; !found && (index < m_count); index++)
            {
                if (item == (*current))
                {
                    found = true;
                }
                else
                {
                    current++;
                    if (current == &m_items[m_size])
                    {
                        current = &m_items[0u];
                    }
                }
            }

            return found;
        }


        ////// Implementation of IRingBuffer interface //////


        /** \brief Write an item into the ring buffer */
        virtual bool write(const ItemType& item)
        {
            (*m_write) = item;
            m_write++;
            if (m_write == &m_items[m_size])
            {
                m_write = &m_items[0u];
            }
            if (m_write == m_read)
            {
                m_read++;
                if (m_read == &m_items[m_size])
                {
                    m_read = &m_items[0u];
                }
            }
            else
            {
                m_count++;
            }

            return true;
        }

        /** \brief Read an item from the ring buffer */
        virtual bool read(ItemType& item)
        {
            bool ret = false;

            if (m_count != 0u)
            {
                item = (*m_read);
                m_count--;
                m_read++;
                if (m_read == &m_items[m_size])
                {
                    m_read = &m_items[0u];
                }

                ret = true;
            }

            return ret;
        }

        /** \brief Remove all the items from the ring buffer */
        virtual void clear()
        {
            m_count = 0u;
            m_read = &m_items[0u];
            m_write = &m_items[0u];
        }


        ////// Implementation of RingBufferBase methods //////


    private:

        /** \brief Underlying C array */
        ItemType* const m_items;

        /** \brief Underlying C array size */
        const nano_stl_size_t m_size;

        /** \brief Item count */
        nano_stl_size_t m_count;

        /** \brief Read pointer */
        ItemType* m_read;

        /** \brief Write pointer */
        ItemType* m_write;
};

}

#endif // RINGBUFFERBASE_H
