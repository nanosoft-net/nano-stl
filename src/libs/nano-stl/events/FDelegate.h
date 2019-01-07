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

#ifndef FDELEGATE_H
#define FDELEGATE_H


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)

#include "IDelegate.h"

namespace nano_stl
{

/** \brief Delegate to target a function */
template<typename ReturnType, typename... args>
class FDelegate : public IDelegate<ReturnType, args...>
{
    public:

        /** \brief Caller method type */
        typedef ReturnType(*fpCall)(args...);


        /** \brief Constructor */
        FDelegate()
        : m_function(nullptr)
        {}

        /** \brief Constructor */
        FDelegate(const fpCall function)
        : m_function(function)
        {}

        /** \brief Copy constructor */
        FDelegate(const FDelegate& copy)
        : m_function(copy.m_function)
        {}

   
        /** \brief Invoke the target function or method */
        virtual ReturnType invoke(args&&... a) const
        {
            return (*m_function)(static_cast<args&&>(a)...);
        }

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()(args&&... a) const
        {
            return (*m_function)(static_cast<args&&>(a)...);
        }

        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const
        {
            return (m_function == NULL);
        }

        /** \brief Make the delegate invalid */
        virtual void reset()
        {
            m_function = NULL;
        }


        /** \brief Comparison operator */
        bool operator == (FDelegate<ReturnType, args...>& compareDelegate) const
        {
            const bool ret = (m_function == compareDelegate.m_function);
            return ret;
        }

        /** \brief Comparison operator */
        bool operator != (FDelegate<ReturnType, args...>& compareDelegate) const
        {
            const bool ret = (m_function != compareDelegate.m_function);
            return ret;
        }

        /** \brief Assignment operator */
        FDelegate<ReturnType, args...>& operator = (const FDelegate<ReturnType, args...>& copy)
        {
            m_function = copy.m_function;
            return (*this);
        }


    private:

        /** \brief Function to call */
        fpCall m_function;

};

}

#endif // __cplusplus

#endif // FDELEGATE_H
