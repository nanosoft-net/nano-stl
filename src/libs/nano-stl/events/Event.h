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


#include "IEvent.h"
#include "IArray.h"

namespace nano_stl
{

// Check C++ version >= C++11
#if (__cplusplus >= 201103L)


/** \brief Event implementation */
template<typename... args>
class Event : public IEvent<args...>
{
    public:

        /** \brief Constructor */
        Event(IArray< const typename IEvent<args...>::EventHandler* >& event_handlers)
        : m_event_handlers(event_handlers)
        {}


        /** \brief Trigger the event */
        virtual void trigger(args&&... a) const override
        {
            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                const typename IEvent<args...>::EventHandler*& event_handler = m_event_handlers[i];
                if (event_handler != nullptr)
                {
                    event_handler->invoke(static_cast<args&&>(a)...);
                }
            }
        }

        /** \brief Bind a handler to receive event notifications */
        virtual bool bind(const typename IEvent<args...>::EventHandler& event_handler) override
        {
            bool found = false;

            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const typename IEvent<args...>::EventHandler*& event_handler_i = m_event_handlers[i];
                if (event_handler_i == nullptr)
                {
                    event_handler_i = &event_handler;
                    found = true;
                }
            }
            
            return found;
        }

        /** \brief Unbind a handler from event notifications */
        virtual bool unbind(const typename IEvent<args...>::EventHandler& event_handler) override
        {
            bool found = false;

            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const typename IEvent<args...>::EventHandler*& event_handler_i = m_event_handlers[i];
                if (event_handler_i == &event_handler)
                {
                    event_handler_i = nullptr;
                    found = true;
                }
            }
            
            return found;
        }


    private:

        /** \brief Handlers to receive the event */
        IArray< const typename IEvent<args...>::EventHandler* >& m_event_handlers;
};


#else // __cplusplus


/** \brief Event implementation */
template<typename ArgType>
class Event : public IEvent<ArgType>
{
    public:

        /** \brief Constructor */
        Event(IArray< const typename IEvent<ArgType>::EventHandler* >& event_handlers)
        : m_event_handlers(event_handlers)
        {}


        /** \brief Trigger the event */
        virtual void trigger(ArgType a) const
        {
            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                const typename IEvent<ArgType>::EventHandler*& event_handler = m_event_handlers[i];
                if (event_handler != nullptr)
                {
                    event_handler->invoke(a);
                }
            }
        }

        /** \brief Bind a handler to receive event notifications */
        virtual bool bind(const typename IEvent<ArgType>::EventHandler& event_handler)
        {
            bool found = false;

            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const typename IEvent<ArgType>::EventHandler*& event_handler_i = m_event_handlers[i];
                if (event_handler_i == nullptr)
                {
                    event_handler_i = &event_handler;
                    found = true;
                }
            }
            
            return found;
        }

        /** \brief Unbind a handler from event notifications */
        virtual bool unbind(const typename IEvent<ArgType>::EventHandler& event_handler)
        {
            bool found = false;

            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const typename IEvent<ArgType>::EventHandler*& event_handler_i = m_event_handlers[i];
                if (event_handler_i == &event_handler)
                {
                    event_handler_i = nullptr;
                    found = true;
                }
            }
            
            return found;
        }


    private:

        /** \brief Handlers to receive the event */
        IArray< const typename IEvent<ArgType>::EventHandler* >& m_event_handlers;
};


/** \brief Event implementation */
template<>
class Event<void> : public IEvent<void>
{
    public:

        /** \brief Constructor */
        Event(IArray< const typename IEvent<void>::EventHandler* >& event_handlers)
        : m_event_handlers(event_handlers)
        {}


        /** \brief Trigger the event */
        virtual void trigger() const
        {
            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                const typename IEvent<void>::EventHandler*& event_handler = m_event_handlers[i];
                if (event_handler != nullptr)
                {
                    event_handler->invoke();
                }
            }
        }

        /** \brief Bind a handler to receive event notifications */
        virtual bool bind(const typename IEvent<void>::EventHandler& event_handler)
        {
            bool found = false;

            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const typename IEvent<void>::EventHandler*& event_handler_i = m_event_handlers[i];
                if (event_handler_i == nullptr)
                {
                    event_handler_i = &event_handler;
                    found = true;
                }
            }
            
            return found;
        }

        /** \brief Unbind a handler from event notifications */
        virtual bool unbind(const typename IEvent<void>::EventHandler& event_handler)
        {
            bool found = false;

            const nano_stl_size_t size = m_event_handlers.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const typename IEvent<void>::EventHandler*& event_handler_i = m_event_handlers[i];
                if (event_handler_i == &event_handler)
                {
                    event_handler_i = nullptr;
                    found = true;
                }
            }
            
            return found;
        }


    private:

        /** \brief Handlers to receive the event */
        IArray< const typename IEvent<void>::EventHandler* >& m_event_handlers;
};


#endif // __cplusplus

}

#endif // EVENT_H
