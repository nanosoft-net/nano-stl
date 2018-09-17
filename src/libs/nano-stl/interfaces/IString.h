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

#ifndef ISTRING_H
#define ISTRING_H

#include "IArray.h"


namespace nano_stl
{

/** \brief Interface for all strings implementations */
class IString : public IArray<char>
{
    public:

        /** \brief Get the length in number of chars of the string */
        virtual nano_stl_size_t getLenght() const = 0;

        /** \brief Get the underlying C string */
        virtual const char* cStr() const = 0;

        /** \brief Get the underlying C string */
        virtual char* cStr() = 0;


        /** \brief Format a string */
        virtual void format(const char* format, ...) = 0;

        /** \brief Format a string */
        virtual void format(const char* format, va_list arg_list) = 0;

        
        /** \brief Copy operator */
        virtual IString& operator = (const IString& copy) = 0;

        /** \brief Concatenate operator */
        virtual IString& operator + (const IString& str) = 0;


        /** \brief Compare operator */
        virtual bool operator == (const IString& str) const = 0;

        /** \brief Compare operator */
        virtual bool operator != (const IString& str) const = 0;

        /** \brief Compare operator */
        virtual bool operator > (const IString& str) const = 0;

        /** \brief Compare operator */
        virtual bool operator < (const IString& str) const = 0;


};

}

#endif // ISTRING_H
