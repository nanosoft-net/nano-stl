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

namespace nano_stl
{

/** \brief Event implementation */
template<typename... args>
class Event : public IEvent<args...>
{
    public:

        /** \brief Trigger the event */
        virtual void trigger(args&&... a) const
        {
            m_delegate.invoke(static_cast<args&&>(a)...);
        }

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const Delegate<void, args...>& delegate)
        {
            m_delegate = delegate;
            return true;
        }


    private:

        /** \brief Delegate */
        Delegate<void, args...> m_delegate;
};

}

#endif // __cplusplus

#endif // EVENT_H
