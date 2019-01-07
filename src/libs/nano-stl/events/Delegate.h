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

#ifndef DELEGATE_H
#define DELEGATE_H


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)

#include "IDelegate.h"

namespace nano_stl
{

/** \brief Delegate to target a method of an object */
template<typename ReturnType, typename... args>
class Delegate : public IDelegate<ReturnType, args...>
{
    public:

        /** \brief Constructor */
        Delegate()
        : m_obj(NULL)
        , m_method(nullptr)
        {}

        /** \brief Copy constructor */
        Delegate(const Delegate& copy)
        : m_obj(copy.m_obj)
        , m_method(copy.m_method)
        {}

        /** \brief Create a delegate */
        template <typename ObjType, ReturnType(ObjType::*MethodType)(args...)>
        static Delegate create(ObjType& obj)
        {
            Delegate<ReturnType, args...> deleg(&obj, &callMethod<ObjType, MethodType>);
            return deleg;
        }

        /** \brief Invoke the target function or method */
        virtual ReturnType invoke(args&&... a) const
        {
            return (*m_method)(m_obj, static_cast<args&&>(a)...);
        }

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()(args&&... a) const
        {
            return (*m_method)(m_obj, static_cast<args&&>(a)...);
        }

        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const
        {
            return ((m_obj == NULL) || (m_method == NULL));
        }

        /** \brief Make the delegate invalid */
        virtual void reset()
        {
            m_obj = NULL;
            m_method = NULL;
        }


        /** \brief Comparison operator */
        bool operator == (Delegate<ReturnType, args...>& compareDelegate) const
        {
            const bool ret = ((m_obj == compareDelegate.m_obj) && (m_method == compareDelegate.m_method));
            return ret;
        }

        /** \brief Comparison operator */
        bool operator != (Delegate<ReturnType, args...>& compareDelegate) const
        {
            const bool ret = !((m_obj == compareDelegate.m_obj) && (m_method == compareDelegate.m_method));
            return ret;
        }

        /** \brief Assignment operator */
        Delegate<ReturnType, args...>& operator = (const Delegate<ReturnType, args...>& copy)
        {
            m_obj = copy.m_obj;
            m_method = copy.m_method;
            return (*this);
        }


    private:

        /** \brief Caller method type */
        typedef ReturnType(*fpCall)(void* const obj, args...);

        /** \brief Object to call */
        void* m_obj;

        /** \brief Method to call */
        fpCall m_method;


        /** \brief Constructor */
        Delegate(void* const obj, const fpCall method)
        : m_obj(obj)
        , m_method(method)
        {}

        /** \brief Caller method */
        template <typename ObjType, ReturnType(ObjType::*MethodType)(args...)>
        static ReturnType callMethod(void* const obj, args... params)
        {
            ObjType* const obj_call = static_cast<ObjType*>(obj);
            return (obj_call->*MethodType)(static_cast<args&&>(params)...);
        }
};

}

#endif // __cplusplus

#endif // DELEGATE_H
