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

#ifndef EVENTHELPER_H
#define EVENTHELPER_H


#include "Event.h"
#include "StaticArray.h"

namespace nano_stl
{

// Check C++ version >= C++11
#if (__cplusplus >= 201103L)


/** \brief Helper for event instanciation */
template<uint32_t MAX_DELEGATE_COUNT, typename... args>
class EventHelper : public Event<args...>
{
    public:

        /** \brief Constructor */
        EventHelper()
        : Event<args...>(m_delegates)
        , m_delegates()
        {
            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                m_delegates[i] = NULL;
            }
        }


    private:

        /** \brief Delegates to receive the event */
        StaticArray< const IDelegate<void, args...>*, MAX_DELEGATE_COUNT > m_delegates;
};


#else // __cplusplus


/** \brief Helper for event instanciation */
template<uint32_t MAX_DELEGATE_COUNT, typename ArgType>
class EventHelper : public Event<ArgType>
{
    public:

        /** \brief Constructor */
        EventHelper()
        : Event<ArgType>(m_delegates)
        , m_delegates()
        {
            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                m_delegates[i] = NULL;
            }
        }


    private:

        /** \brief Delegates to receive the event */
        StaticArray< const IDelegate<void, ArgType>*, MAX_DELEGATE_COUNT > m_delegates;
};


#endif // __cplusplus

}

#endif // EVENTHELPER_H
