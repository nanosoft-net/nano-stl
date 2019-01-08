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


#include "IDelegate.h"

namespace nano_stl
{


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)



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
        virtual ReturnType invoke(args&&... a) const override
        {
            return (*m_function)(static_cast<args&&>(a)...);
        }

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()(args&&... a) const override
        {
            return (*m_function)(static_cast<args&&>(a)...);
        }

        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const override
        {
            return (m_function == nullptr);
        }

        /** \brief Make the delegate invalid */
        virtual void reset() override
        {
            m_function = nullptr;
        }


        /** \brief Comparison operator */
        bool operator == (const FDelegate<ReturnType, args...>& compareDelegate) const
        {
            const bool ret = (m_function == compareDelegate.m_function);
            return ret;
        }

        /** \brief Comparison operator */
        bool operator != (const FDelegate<ReturnType, args...>& compareDelegate) const
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


#else // __cplusplus


/** \brief Delegate to target a function */
template<typename ReturnType, typename ArgType>
class FDelegate : public IDelegate<ReturnType, ArgType>
{
    public:

        /** \brief Caller method type */
        typedef ReturnType(*fpCall)(ArgType);


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
        virtual ReturnType invoke(ArgType a) const
        {
            return (*m_function)(a);
        }

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()(ArgType a) const
        {
            return (*m_function)(a);
        }

        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const
        {
            return (m_function == nullptr);
        }

        /** \brief Make the delegate invalid */
        virtual void reset()
        {
            m_function = nullptr;
        }


        /** \brief Comparison operator */
        bool operator == (const FDelegate<ReturnType, ArgType>& compareDelegate) const
        {
            const bool ret = (m_function == compareDelegate.m_function);
            return ret;
        }

        /** \brief Comparison operator */
        bool operator != (const FDelegate<ReturnType, ArgType>& compareDelegate) const
        {
            const bool ret = (m_function != compareDelegate.m_function);
            return ret;
        }

        /** \brief Assignment operator */
        FDelegate<ReturnType, ArgType>& operator = (const FDelegate<ReturnType, ArgType>& copy)
        {
            m_function = copy.m_function;
            return (*this);
        }


    private:

        /** \brief Function to call */
        fpCall m_function;

};


/** \brief Delegate to target a function */
template<typename ReturnType>
class FDelegate<ReturnType, void> : public IDelegate<ReturnType, void>
{
    public:

        /** \brief Caller method type */
        typedef ReturnType(*fpCall)();


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
        virtual ReturnType invoke() const
        {
            return (*m_function)();
        }

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()() const
        {
            return (*m_function)();
        }

        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const
        {
            return (m_function == nullptr);
        }

        /** \brief Make the delegate invalid */
        virtual void reset()
        {
            m_function = nullptr;
        }


        /** \brief Comparison operator */
        bool operator == (const FDelegate<ReturnType, void>& compareDelegate) const
        {
            const bool ret = (m_function == compareDelegate.m_function);
            return ret;
        }

        /** \brief Comparison operator */
        bool operator != (const FDelegate<ReturnType, void>& compareDelegate) const
        {
            const bool ret = (m_function != compareDelegate.m_function);
            return ret;
        }

        /** \brief Assignment operator */
        FDelegate<ReturnType, void>& operator = (const FDelegate<ReturnType, void>& copy)
        {
            m_function = copy.m_function;
            return (*this);
        }


    private:

        /** \brief Function to call */
        fpCall m_function;

};


#endif // __cplusplus

}

#endif // FDELEGATE_H
