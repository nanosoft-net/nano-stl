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

#ifndef STATICSTRING_H
#define STATICSTRING_H

#include "StringBase.h"

namespace nano_stl
{

/** \brief Static string implementation 
 *         The string memory (including extra null terminator) is statically allocated by the class.
*/
template <nano_stl_size_t MAX_CHAR_COUNT>
class StaticString : public StringBase
{
    public:

        /** \brief Constructor */
        StaticString() : StringBase(m_c_str, MAX_CHAR_COUNT + 1u)
        {}

        /** \brief Constructor */
        StaticString(const char init_str[]) : StringBase(m_c_str, MAX_CHAR_COUNT + 1u, init_str)
        {}


        /** \brief Copy operator */
        StaticString<MAX_CHAR_COUNT>& operator = (const StaticString<MAX_CHAR_COUNT>& copy) { StringBase::operator=(static_cast<const IString&>(copy)); return (*this); }

        /** \brief Concatenate operator */
        StaticString<MAX_CHAR_COUNT>& operator + (const StaticString<MAX_CHAR_COUNT>& str) { StringBase::operator+(static_cast<const IString&>(str)); return (*this); }


    private:

        /** \brief Internal C string */
        char m_c_str[MAX_CHAR_COUNT + 1u];

};

}

#endif // STATICSTRING_H
