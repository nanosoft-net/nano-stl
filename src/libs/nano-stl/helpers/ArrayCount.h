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

#ifndef ARRAYCOUNT_H
#define ARRAYCOUNT_H


#include "nano-stl-conf.h"

/** \brief Macro to compute the number of elements inside a C-style declared array */
#define ARRAY_COUNT(array, item_type)	static_cast<nano_stl_size_t>(sizeof(array) / sizeof(item_type))



#endif // ARRAYCOUNT_H
