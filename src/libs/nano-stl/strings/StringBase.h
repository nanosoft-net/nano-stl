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

#ifndef STRINGBASE_H
#define STRINGBASE_H

#include "IString.h"

#include <string.h>
#include <stdio.h>

namespace nano_stl
{

/** \brief Base class for all strings implementations */
class StringBase : public IString
{
    public:

        

        /** \brief Constructor */
        StringBase(char c_str[], const nano_stl_size_t size, bool initialized = false)
        : m_c_str(c_str)
        , m_size(size - 1u)
        , m_length(0u)

    // Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        , m_begin(*this, IIteratorBase<char>::INVALID_POSITION)
        , m_end(*this, IIteratorBase<char>::INVALID_POSITION)
        , m_it(*this, 0u)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)

#endif // NANO_STL_ITERATORS_ENABLED
        {}

        /** \brief Constructor */
        StringBase(char c_str[], const nano_stl_size_t size, const char init_str[])
        : m_c_str(c_str)
        , m_size(size - 1u)
        , m_length(static_cast<nano_stl_size_t>(NANO_STL_STRNLEN(init_str, size)))

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        , m_begin(*this, IIteratorBase<char>::INVALID_POSITION)
        , m_end(*this, IIteratorBase<char>::INVALID_POSITION)
        , m_it(*this, 0u)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)

#endif // NANO_STL_ITERATORS_ENABLED
        {
            // Update iterators
            if (m_length > m_size)
            {
                m_length = m_size;
            }

            // Check if iterators are enabled
            #if (NANO_STL_ITERATORS_ENABLED == 1)

            if (m_length != 0u)
            {
                m_begin = typename IArray<char>::Iterator(*this, 0u);
                m_const_begin = m_begin;
            }

            #endif // NANO_STL_ITERATORS_ENABLED
        }

        /** \brief Constructor */
        StringBase(char c_str[])
        : m_c_str(c_str)
        , m_size(static_cast<nano_stl_size_t>(NANO_STL_STRNLEN(m_c_str, static_cast<size_t>(0xFFFFFFFFu))))
        , m_length(m_size)

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        , m_begin(*this, IIteratorBase<char>::INVALID_POSITION)
        , m_end(*this, IIteratorBase<char>::INVALID_POSITION)
        , m_it(*this, 0u)
        , m_const_begin(m_begin)
        , m_const_end(m_end)
        , m_const_it(m_it)
        , m_pconst_it(&m_const_it)

#endif // NANO_STL_ITERATORS_ENABLED
        {

            // Check if iterators are enabled
            #if (NANO_STL_ITERATORS_ENABLED == 1)

            // Update iterators
            if (m_length != 0u)
            {
                m_begin = typename IArray<char>::Iterator(*this, 0u);
                m_const_begin = m_begin;
            }

            #endif // NANO_STL_ITERATORS_ENABLED
        }

        ////// Implementation of IContainer interface //////


        /** \brief Get the number of objects that the container can handle */
        virtual nano_stl_size_t getCapacity() const { return m_size; }

        /** \brief Get the number of objects that the container contains */
        virtual nano_stl_size_t getCount() const { return m_length; }

        /** \brief Check if the container contains an item */
        virtual bool contains(const char& item) const
        {
            bool found = false;

            for (nano_stl_size_t index = 0u; !found && (index < m_length); index++)
            {
                if (item == m_c_str[index])
                {
                    found = true;
                }
            }

            return found;
        }


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        ////// Implementation of IIterable interface //////

        
        /** \brief Get the iterator which points to the start of the container */
        virtual const IIterator<char>& begin() const { return m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        virtual const IIterator<char>& end() const { return m_end; }

        /** \brief Get the iterator of the container */
        virtual IIterator<char>& it() { begin(m_it); return m_it; }

        /** \brief Get the const iterator which points to the start of the container */
        virtual const IConstIterator<char>& cbegin() const { return m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        virtual const IConstIterator<char>& cend() const { return m_const_end; }

        /** \brief Get the const iterator of the container */
        virtual IConstIterator<char>& const_it() const { cbegin(*m_pconst_it); return (*m_pconst_it); }

#endif // NANO_STL_ITERATORS_ENABLED


        ////// Implementation of IArray interface //////


        /** \brief Get an item at a specified index */
        virtual char& operator [] (const nano_stl_size_t index)
        {
            return m_c_str[index];
        }

        /** \brief Get an item at a specified index */
        virtual const char& operator [] (const nano_stl_size_t index) const
        {
            return m_c_str[index];
        }


        ////// Implementation of IString interface //////


        /** \brief Get the length in number of chars of the string */
        virtual nano_stl_size_t getLenght() const { return m_length; }

        /** \brief Get the underlying C string */
        virtual const char* cStr() const { return m_c_str; }

        /** \brief Get the underlying C string */
        virtual char* cStr() { return m_c_str; }


        /** \brief Format a string */
        virtual void format(const char* format, ...)
        {
            va_list arg_list;
            va_start(arg_list, format);
            this->format(format, arg_list);
            va_end(arg_list);
        }

        /** \brief Format a string */
        virtual void format(const char* format, va_list arg_list)
        {
            int ret = NANO_STL_VSNPRINTF(m_c_str, m_size + 1u, format, arg_list);
            if (ret <= 0)
            {
                m_length = 0u;
                m_c_str[0u] = 0;

                // Check if iterators are enabled
                #if (NANO_STL_ITERATORS_ENABLED == 1)

                m_begin = typename IArray<char>::Iterator(*this, IIteratorBase<char>::INVALID_POSITION);
                m_const_begin = m_begin;

                #endif // NANO_STL_ITERATORS_ENABLED
            }
            else
            {
                // Check if iterators are enabled
                #if (NANO_STL_ITERATORS_ENABLED == 1)

                if (m_length == 0u)
                {
                    m_begin = typename IArray<char>::Iterator(*this, 0u);
                    m_const_begin = m_begin;
                }

                #endif // NANO_STL_ITERATORS_ENABLED
                
                m_length = static_cast<nano_stl_size_t>(ret);
            }
        }

        
        /** \brief Copy operator */
        virtual IString& operator = (const IString& copy)
        {
            // Compute new string length
            if (copy.getLenght() > m_size)
            {
                m_length = m_size;
            }
            else
            {
                m_length = copy.getLenght();
            }

            // Copy new string
            NANO_STL_MEMCPY(m_c_str, copy.cStr(), m_length);

            // Terminate string
            m_c_str[m_length] = 0;

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

            // Update iterators
            if (m_length == 0u)
            {
                m_begin = typename IArray<char>::Iterator(*this, IIteratorBase<char>::INVALID_POSITION);
                m_const_begin = m_begin;
            }
            else
            {
                m_begin = typename IArray<char>::Iterator(*this, 0u);
                m_const_begin = m_begin;
            }

#endif // NANO_STL_ITERATORS_ENABLED

            return (*this);
        }

        /** \brief Concatenate operator */
        virtual IString& operator + (const IString& str)
        {
            // Compute new string length
            nano_stl_size_t copy_size = str.getLenght();
            if ((m_size - m_length) < copy_size)
            {
                m_length = m_size;
                copy_size = m_size - m_length;
            }
            else
            {
                m_length += copy_size;
            }

            // Copy new string
            NANO_STL_MEMCPY(&m_c_str[m_length], str.cStr(), copy_size);

            // Terminate string
            m_c_str[m_length] = 0;

// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

            // Update iterators
            if (m_length == 0u)
            {
                m_begin = typename IArray<char>::Iterator(*this, IIteratorBase<char>::INVALID_POSITION);
                m_const_begin = m_begin;
            }
            else
            {
                m_begin = typename IArray<char>::Iterator(*this, 0u);
                m_const_begin = m_begin;
            }

#endif // NANO_STL_ITERATORS_ENABLED

            return (*this);
        }


        /** \brief Compare operator */
        virtual bool operator == (const IString& str) const
        {
            bool ret = false;

            // Check length
            if (str.getLenght() == m_length)
            {
                // Compare strings
                ret = (NANO_STL_STRNCMP(m_c_str, str.cStr(), m_size) == 0);
            }

            return ret;
        }


        /** \brief Compare operator */
        virtual bool operator != (const IString& str) const { return !(this->operator==(str)); }

        /** \brief Compare operator */
        virtual bool operator > (const IString& str) const
        {
            return (NANO_STL_STRNCMP(m_c_str, str.cStr(), m_size) > 0);
        }

        /** \brief Compare operator */
        virtual bool operator < (const IString& str) const { return !(this->operator>(str)); }


        ////// Implementation of StringBase methods //////


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)

        /** \brief Get the iterator which points to the start of the container */
        const void begin(typename IArray<char>::Iterator& it) const { it = m_begin; }

        /** \brief Get the iterator which points to the end of the container */
        const void end(typename IArray<char>::Iterator& it) const { it = m_end; }

        /** \brief Get the const iterator which points to the start of the container */
        const void cbegin(typename IArray<char>::ConstIterator& it) const { it = m_const_begin; }

        /** \brief Get the const iterator which points to the end of the container */
        const void cend(typename IArray<char>::ConstIterator& it) const { it = m_const_end; }

#endif // NANO_STL_ITERATORS_ENABLED


    private:

        /** \brief Underlying C string */
        char* const m_c_str;

        /** \brief Underlying C string size */
        const nano_stl_size_t m_size;

        /** \brief String length */
        nano_stl_size_t m_length;


// Check if iterators are enabled
#if (NANO_STL_ITERATORS_ENABLED == 1)
        
        /** \brief Iterator to the beginning of the array */
        typename IArray<char>::Iterator m_begin;

        /** \brief Iterator to the end of the array */
        const typename IArray<char>::Iterator m_end;

        /** \brief Iterator of the container */
        typename IArray<char>::Iterator m_it;

        /** \brief Iterator to the beginning of the array */
        typename IArray<char>::ConstIterator m_const_begin;

        /** \brief Iterator to the end of the array */
        const typename IArray<char>::ConstIterator m_const_end;

        /** \brief Const iterator of the container */
        typename IArray<char>::ConstIterator m_const_it;

        /** \brief Pointer to the const iterator of the container */
        typename IArray<char>::ConstIterator* const m_pconst_it;

#endif // NANO_STL_ITERATORS_ENABLED

};

}

#endif // STRINGBASE_H
