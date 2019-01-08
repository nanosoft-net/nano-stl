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

#include "nano-stl-conf.h"
#include "IErrorHandler.h"

#include <new>


#if (NANO_STL_DYNAMIC_MEMORY_ALLOCATION == NANO_STL_DYNAMIC_MEMORY_ALLOCATION_DISABLED)

// Dynamic memory allocation won't be allowed

void* operator new (std::size_t size)
{
    NANO_STL_CRITICAL_ERROR();
    return nullptr;
}

void operator delete (void* ptr)
{
    NANO_STL_CRITICAL_ERROR();
}

void* operator new[] (std::size_t size)
{
    NANO_STL_CRITICAL_ERROR();
    return nullptr;
}

void operator delete[] (void* ptr)
{
    NANO_STL_CRITICAL_ERROR();
}


#elif (NANO_STL_DYNAMIC_MEMORY_ALLOCATION == NANO_STL_DYNAMIC_MEMORY_ALLOCATION_MALLOC)

// Dynamic memory allocation will be performed by C functions malloc/free

#include <malloc.h>

void* operator new (std::size_t size)
{
    return malloc(size);
}

void operator delete (void* ptr)
{
    free(ptr);
}

void* operator new[] (std::size_t size)
{
    return malloc(size);
}

void operator delete[] (void* ptr)
{
    free(ptr);
}

#else

// Dynamic memory allocation will be performed by C++ standard new/delete implementation or by another library

#endif // NANO_STL_DYNAMIC_MEMORY_ALLOCATION
