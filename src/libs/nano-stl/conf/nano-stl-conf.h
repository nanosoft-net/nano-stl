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

#ifndef NANO_STL_CONF_H
#define NANO_STL_CONF_H


#if (__cplusplus < 201103L)
#include "stdint.h"
#else // __cplusplus
#include <cstdint>
#endif // __cplusplus

namespace nano_stl
{

/** \brief Define the maximum size of a container in number of elements */
typedef uint32_t nano_stl_size_t;

}


//////////////////////////////// Options /////////////////////////////////

/* Memory management configuration options */

/** \brief No dynamic memory allocation will be allowed */
#define NANO_STL_DYNAMIC_MEMORY_ALLOCATION_DISABLED     0u
/** \brief Dynamic memory allocation will be performed by C malloc/free functions */
#define NANO_STL_DYNAMIC_MEMORY_ALLOCATION_MALLOC       1u
/** \brief Dynamic memory allocation will be performed by C++ standard new/delete implementation or by another library */
#define NANO_STL_DYNAMIC_MEMORY_ALLOCATION_STANDARD     2u

/** \brief Memory management configuration
 *         Valid values are:
 *         NANO_STL_DYNAMIC_MEMORY_ALLOCATION_DISABLED
 *         NANO_STL_DYNAMIC_MEMORY_ALLOCATION_MALLOC
 *         NANO_STL_DYNAMIC_MEMORY_ALLOCATION_STANDARD
 */
#define NANO_STL_DYNAMIC_MEMORY_ALLOCATION      NANO_STL_DYNAMIC_MEMORY_ALLOCATION_DISABLED





#endif // NANO_STL_CONF_H
