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


#include "nano-stl-conf.h"
#include "IDelegate.h"

namespace nano_stl
{

// Check C++ version >= C++11
#if (__cplusplus >= 201103L)


/** \brief Interface for all events implementations */
template<typename... args>
class IEvent
{
    public:

        /** \brief Trigger the event */
        virtual void trigger(args&&... a) const = 0;

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const IDelegate<void, args...>& delegate) = 0;

        /** \brief Unbind a delegate from event notifications */
        virtual bool unbind(const IDelegate<void, args...>& delegate) = 0;
};


#else // __cplusplus


/** \brief Interface for all events implementations */
template<typename ArgType>
class IEvent
{
    public:

        /** \brief Trigger the event */
        virtual void trigger(ArgType a) const = 0;

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const IDelegate<void, ArgType>& delegate) = 0;

        /** \brief Unbind a delegate from event notifications */
        virtual bool unbind(const IDelegate<void, ArgType>& delegate) = 0;
};


/** \brief Interface for all events implementations */
template<>
class IEvent<void>
{
    public:

        /** \brief Trigger the event */
        virtual void trigger() const = 0;

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const IDelegate<void, void>& delegate) = 0;

        /** \brief Unbind a delegate from event notifications */
        virtual bool unbind(const IDelegate<void, void>& delegate) = 0;
};


#endif // __cplusplus

}

#endif // IEVENT_H
