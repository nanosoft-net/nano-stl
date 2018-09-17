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

#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include "StringBase.h"

namespace nano_stl
{

/** \brief String view implementation 
 *         The string memory (including extra null terminator) is allocated outside the class.
*/
class StringView : public StringBase
{
    public:

        /** \brief Constructor */
        StringView(char* c_str) : StringBase(c_str)
        {}

        /** \brief Copy operator */
        StringView& operator = (const StringView& copy) { StringBase::operator=(static_cast<const IString&>(copy)); return (*this); }

        /** \brief Concatenate operator */
        StringView& operator + (const StringView& str) { StringBase::operator+(static_cast<const IString&>(str)); return (*this); }

    private:

};

}

#endif // STRINGVIEW_H
