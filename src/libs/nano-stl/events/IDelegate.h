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

#ifndef IDELEGATE_H
#define IDELEGATE_H


#include "nano-stl-conf.h"


namespace nano_stl
{

// Check C++ version >= C++11
#if (__cplusplus >= 201103L)


/** \brief Interface for all delegates implementations */
template<typename ReturnType, typename... args>
class IDelegate
{
    public:

        /** \brief Invoke the target function or method */
        virtual ReturnType invoke(args&&... a) const = 0;

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()(args&&... a) const = 0;


        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const = 0;

        /** \brief Make the delegate invalid */
        virtual void reset() = 0;
};


#else // __cplusplus


/** \brief Interface for all delegates implementations */
template<typename ReturnType, typename ArgType>
class IDelegate
{
    public:

        /** \brief Invoke the target function or method */
        virtual ReturnType invoke(ArgType a) const = 0;

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()(ArgType a) const = 0;


        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const = 0;

        /** \brief Make the delegate invalid */
        virtual void reset() = 0;
};


/** \brief Interface for all delegates implementations */
template<typename ReturnType>
class IDelegate<ReturnType, void>
{
    public:

        /** \brief Invoke the target function or method */
        virtual ReturnType invoke() const = 0;

        /** \brief Call operator to invoke the target function or method */
        virtual ReturnType operator()() const = 0;


        /** \brief Indicate if the delegate points to a valid target function or method */
        virtual bool isNull() const = 0;

        /** \brief Make the delegate invalid */
        virtual void reset() = 0;
};


#endif // __cplusplus

}

#endif // IDELEGATE_H
