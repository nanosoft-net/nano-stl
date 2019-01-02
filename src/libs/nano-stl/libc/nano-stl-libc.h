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

#ifndef NANO_STL_LIBC_H
#define NANO_STL_LIBC_H

#include "nano-stl-conf.h"


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/** \brief Highly portable but non-efficient memset function */
void* NANO_STL_LIBC_Memset(void* const dst, const int val, size_t size);

/** \brief Highly portable but non-efficient memcpy function */
void* NANO_STL_LIBC_Memcpy(void* const dst, const void* const src, size_t size);

/** \brief Highly portable but non-efficient memcmp function */
int NANO_STL_LIBC_Memcmp(const void* const s1, const void* const s2, size_t size);

/** \brief Highly portable but non-efficient strncmp function */
int NANO_STL_LIBC_Strncmp(const char* s1, const char* s2, size_t size);

/** \brief Highly portable but non-efficient strnlen function */
size_t NANO_STL_LIBC_Strnlen(const char* s, size_t maxlen);

/** \brief Highly portable but non-efficient strncat function */
char* NANO_STL_LIBC_Strncat(char *dest, const char *src, size_t size);

/** \brief Highly portable but non-efficient strncpy function */
char* NANO_STL_LIBC_Strncpy(char *dest, const char *src, size_t size);

/** \brief Highly portable but non-efficient vsnprintf function */
int NANO_STL_LIBC_Vsnprintf(char *str, size_t size, const char *format, va_list ap);

/** \brief Highly portable but non-efficient snprintf function */
int NANO_STL_LIBC_Snprintf(char *str, size_t size, const char *format, ...);

/** \brief Higly portable but non-efficient atoi function */
int NANO_STL_LIBC_Atoi(const char* str);

/** \brief Higly portable but non-efficient itoa function */
char* NANO_STL_LIBC_Itoa(int value, char * str, int base);

/** \brief Highly portable but non-efficient atof function */
double NANO_STL_LIBC_Atof(const char* nptr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NANO_STL_LIBC_H */
