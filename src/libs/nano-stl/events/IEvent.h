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

#ifndef IEVENT_H
#define IEVENT_H


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)

#include "nano-stl-conf.h"
#include "Delegate.h"

namespace nano_stl
{

/** \brief Interface for all events implementations */
template<typename... args>
class IEvent
{
    public:

        /** \brief Trigger the event */
        virtual void trigger(args&&... a) const = 0;

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const Delegate<void, args...>& delegate) = 0;
};

}

#endif // __cplusplus

#endif // IEVENT_H
