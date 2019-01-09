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


/** \brief Macro to help to instanciate an event handler method object */ 
#define NANO_STL_EVENT_HANDLER_M(class_name, method, ...)   nano_stl::IEvent<__VA_ARGS__>::EventHandlerM::create<class_name, &class_name::method>(*this);


template<typename ReturnType, typename... args>
class FDelegate;

template<typename ReturnType, typename... args>
class Delegate;

/** \brief Interface for all events implementations */
template<typename... args>
class IEvent
{
    public:


        /** \brief Generic Event handler */
        typedef IDelegate<void, args...> EventHandler;

        /** \brief Event handler method */
        typedef Delegate<void, args...> EventHandlerM;

        /** \brief Event handler function */
        typedef FDelegate<void, args...> EventHandlerF;


        /** \brief Trigger the event */
        virtual void trigger(args&&... a) const = 0;

        /** \brief Bind a handler to receive event notifications */
        virtual bool bind(const EventHandler& event_handler) = 0;

        /** \brief Unbind a handler from event notifications */
        virtual bool unbind(const EventHandler& event_handler) = 0;
};


#else // __cplusplus


template<typename ReturnType, typename ArgType>
class FDelegate;

template<typename ReturnType, typename ArgType>
class Delegate;

/** \brief Interface for all events implementations */
template<typename ArgType>
class IEvent
{
    public:


        /** \brief Generic Event handler */
        typedef IDelegate<void, ArgType> EventHandler;

        /** \brief Event handler method */
        typedef Delegate<void, ArgType> EventHandlerM;

        /** \brief Event handler function */
        typedef FDelegate<void, ArgType> EventHandlerF;


        /** \brief Trigger the event */
        virtual void trigger(ArgType a) const = 0;

        /** \brief Bind a handler to receive event notifications */
        virtual bool bind(const EventHandler& event_handler) = 0;

        /** \brief Unbind a handler from event notifications */
        virtual bool unbind(const EventHandler& event_handler) = 0;
};


/** \brief Interface for all events implementations */
template<>
class IEvent<void>
{
    public:


        /** \brief Generic Event handler */
        typedef IDelegate<void, void> EventHandler;

        /** \brief Event handler method */
        typedef Delegate<void, void> EventHandlerM;

        /** \brief Event handler function */
        typedef FDelegate<void, void> EventHandlerF;


        /** \brief Trigger the event */
        virtual void trigger() const = 0;

        /** \brief Bind a handler to receive event notifications */
        virtual bool bind(const EventHandler& event_handler) = 0;

        /** \brief Unbind a handler from event notifications */
        virtual bool unbind(const EventHandler& event_handler) = 0;
};


#endif // __cplusplus

}

#endif // IEVENT_H
