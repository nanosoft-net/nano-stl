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
        Event(IArray< const IDelegate<void, args...>* >& delegates)
        : m_delegates(delegates)
        {}


        /** \brief Trigger the event */
        virtual void trigger(args&&... a) const
        {
            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                const IDelegate<void, args...>*& delegate = m_delegates[i];
                if (delegate != NULL)
                {
                    delegate->invoke(static_cast<args&&>(a)...);
                }
            }
        }

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const IDelegate<void, args...>& delegate)
        {
            bool found = false;

            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const IDelegate<void, args...>*& delegate_i = m_delegates[i];
                if (delegate_i == NULL)
                {
                    delegate_i = &delegate;
                    found = true;
                }
            }
            
            return found;
        }

        /** \brief Unbind a delegate from event notifications */
        virtual bool unbind(const IDelegate<void, args...>& delegate)
        {
            bool found = false;

            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const IDelegate<void, args...>*& delegate_i = m_delegates[i];
                if (delegate_i == &delegate)
                {
                    delegate_i = NULL;
                    found = true;
                }
            }
            
            return found;
        }


    private:

        /** \brief Delegates to receive the event */
        IArray< const IDelegate<void, args...>* >& m_delegates;
};


#else // __cplusplus


/** \brief Event implementation */
template<typename ArgType>
class Event : public IEvent<ArgType>
{
    public:

        /** \brief Constructor */
        Event(IArray< const IDelegate<void, ArgType>* >& delegates)
        : m_delegates(delegates)
        {}


        /** \brief Trigger the event */
        virtual void trigger(ArgType a) const
        {
            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                const IDelegate<void, ArgType>*& delegate = m_delegates[i];
                if (delegate != NULL)
                {
                    delegate->invoke(a);
                }
            }
        }

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const IDelegate<void, ArgType>& delegate)
        {
            bool found = false;

            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const IDelegate<void, ArgType>*& delegate_i = m_delegates[i];
                if (delegate_i == NULL)
                {
                    delegate_i = &delegate;
                    found = true;
                }
            }
            
            return found;
        }

        /** \brief Unbind a delegate from event notifications */
        virtual bool unbind(const IDelegate<void, ArgType>& delegate)
        {
            bool found = false;

            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const IDelegate<void, ArgType>*& delegate_i = m_delegates[i];
                if (delegate_i == &delegate)
                {
                    delegate_i = NULL;
                    found = true;
                }
            }
            
            return found;
        }


    private:

        /** \brief Delegates to receive the event */
        IArray< const IDelegate<void, ArgType>* >& m_delegates;
};


/** \brief Event implementation */
template<>
class Event<void> : public IEvent<void>
{
    public:

        /** \brief Constructor */
        Event(IArray< const IDelegate<void, void>* >& delegates)
        : m_delegates(delegates)
        {}


        /** \brief Trigger the event */
        virtual void trigger() const
        {
            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; i < size; i++)
            {
                const IDelegate<void, void>*& delegate = m_delegates[i];
                if (delegate != NULL)
                {
                    delegate->invoke();
                }
            }
        }

        /** \brief Bind a delegate to receive event notifications */
        virtual bool bind(const IDelegate<void, void>& delegate)
        {
            bool found = false;

            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const IDelegate<void, void>*& delegate_i = m_delegates[i];
                if (delegate_i == NULL)
                {
                    delegate_i = &delegate;
                    found = true;
                }
            }
            
            return found;
        }

        /** \brief Unbind a delegate from event notifications */
        virtual bool unbind(const IDelegate<void, void>& delegate)
        {
            bool found = false;

            const nano_stl_size_t size = m_delegates.getCount();
            for (nano_stl_size_t i = 0; (i < size) && !found; i++)
            {
                const IDelegate<void, void>*& delegate_i = m_delegates[i];
                if (delegate_i == &delegate)
                {
                    delegate_i = NULL;
                    found = true;
                }
            }
            
            return found;
        }


    private:

        /** \brief Delegates to receive the event */
        IArray< const IDelegate<void, void>* >& m_delegates;
};


#endif // __cplusplus

}

#endif // EVENT_H
