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

#ifndef EVENT_H
#define EVENT_H


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)

#include "IEvent.h"
#include "IArray.h"

namespace nano_stl
{

/** \brief Event implementation */
template<typename... args>
class Event : public IEvent<args...>
{
    public:

        /** \brief Constructor */
        Event(IArray< const IDelegate<void, args...>* >& delegates)
        : m_delegates(delegates)
        {}


        /** \brief Trigger the event */
        virtual void trigger(args&&... a) const
        {
            for (nano_stl_size_t i = 0; i < m_delegates.getCount(); i++)
            {
                if (m_delegates[i] != NULL)
                {
                    m_delegates[i]->invoke(static_cast<args&&>(a)...);
                }
            }
        }

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const IDelegate<void, args...>& delegate)
        {
            bool found = false;

            for (nano_stl_size_t i = 0; (i < m_delegates.getCount()) && !found; i++)
            {
                if (m_delegates[i] == NULL)
                {
                    m_delegates[i] = &delegate;
                    found = true;
                }
            }
            
            return found;
        }

        /** \brief Unbind a delegate from event notifications */
        virtual bool unbind(const IDelegate<void, args...>& delegate)
        {
            bool found = false;

            for (nano_stl_size_t i = 0; (i < m_delegates.getCount()) && !found; i++)
            {
                if (m_delegates[i] == &delegate)
                {
                    m_delegates[i] = NULL;
                    found = true;
                }
            }
            
            return found;
        }


    private:

        /** \brief Delegates to receive the event */
        IArray< const IDelegate<void, args...>* >& m_delegates;
};

}

#endif // __cplusplus

#endif // EVENT_H
