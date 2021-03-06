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

#include "nano-stl-libc.h"



/** \brief  Writes a character inside the given string */
static int NANO_STL_LIBC_PutChar(char *str, char c);

/** \brief  Writes a string inside the given string */
static int NANO_STL_LIBC_PutString(char *str, const char *source);

/** \brief  Writes an unsigned int inside the given string, using the provided fill &
 *          width parameters */
static int NANO_STL_LIBC_PutUnsignedInt(char *str, char fill, int width, unsigned int value);

/** \brief  Writes a signed int inside the given string, using the provided fill & width
 *          parameters */
static int NANO_STL_LIBC_PutSignedInt(char *str, char fill, int width, int value);

/** \brief  Writes an hexadecimal value into a string, using the given fill, width &
 *          capital parameters */
static int NANO_STL_LIBC_PutHexa(char *str, char fill, int width, unsigned char maj, unsigned int value);



/** \brief Highly portable but non-efficient memset function */
void* NANO_STL_LIBC_Memset(void* const dst, const int val, size_t size)
{
    if (dst != nullptr)
    {
        const uint8_t u8_val = (uint8_t)(val);
        uint8_t* u8_dst = (uint8_t*)(dst);
        while (size != 0u)
        {
            (*u8_dst) = u8_val;
            u8_dst++;
            size--;
        }
    }

    return dst;
}

/** \brief Highly portable but non-efficient memcpy function */
void* NANO_STL_LIBC_Memcpy(void* const dst, const void* const src, size_t size)
{
    if ((dst != nullptr) && (src != nullptr))
    {
        uint8_t* u8_src = (uint8_t*)(src);
        uint8_t* u8_dst = (uint8_t*)(dst);
        while (size != 0u)
        {
            (*u8_dst) = (*u8_src);
            u8_src++;
            u8_dst++;
            size--;
        }
    }

    return dst;
}

/** \brief Highly portable but non-efficient memcmp function */
int NANO_STL_LIBC_Memcmp(const void* const s1, const void* const s2, size_t size)
{
    int ret = 0;

    if ((s1 != nullptr) && (s2 != nullptr))
    {
        uint8_t* u8_s1 = (uint8_t*)(s1);
        uint8_t* u8_s2 = (uint8_t*)(s2);
        while ((size != 0u) && (ret == 0))
        {
            if ((*u8_s1) > (*u8_s2))
            {
                ret = 1;
            }
            else if ((*u8_s1) < (*u8_s2))
            {
                ret = -1;
            }
            else
            {
                u8_s1++;
                u8_s2++;
                size--;
            }
        }
    }

    return ret;
}

/** \brief Highly portable but non-efficient strncmp function */
int NANO_STL_LIBC_Strncmp(const char* s1, const char* s2, size_t size)
{
    int ret = 0;

    if ((s1 != nullptr) && (s2 != nullptr))
    {
        while ((size != 0u) && (ret == 0))
        {
            if ((*s1) > (*s2))
            {
                ret = 1;
            }
            else if ((*s1) < (*s2))
            {
                ret = -1;
            }
            else if ((*s1) == 0)
            {
                size = 0;
            }
            else
            {
                s1++;
                s2++;
                size--;
            }
        }
    }

    return ret;
}

/** \brief Highly portable but non-efficient strnlen function */
size_t NANO_STL_LIBC_Strnlen(const char* s, size_t maxlen)
{
    size_t size = 0;

    if (s != nullptr)
    {
        while (((*s) != 0) && (size != maxlen))
        {
            s++;
            size++;
        }
    }

    return size;
}

/** \brief Highly portable but non-efficient strncat function */
char* NANO_STL_LIBC_Strncat(char *dest, const char *src, size_t size)
{
    char* ret = dest;

    if ((dest != nullptr) && (src != nullptr))
    {
        while ((*dest) != 0)
        {
            dest++;
        }

        while ((size != 0) && ((*src) != 0))
        {
            (*dest) = (*src);
            dest++;
            src++;
            size--;
        }
        (*dest) = 0;
    }

    return ret;

}

/** \brief Highly portable but non-efficient strncpy function */
char* NANO_STL_LIBC_Strncpy(char *dest, const char *src, size_t size)
{
    char* ret = dest;

    if ((dest != nullptr) && (src != nullptr))
    {
        while ((size != 0) && ((*src) != 0))
        {
            (*dest) = (*src);
            dest++;
            src++;
            size--;
        }
        while (size != 0)
        {
            (*dest) = 0;
            dest++;
            size--;
        }
    }

    return ret;

}

/** \brief Highly portable but non-efficient vsnprintf function */
int NANO_STL_LIBC_Vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    char          fill;
    unsigned char width;
    signed int    num = 0;
    signed int    current_size = 0;

    /* Clear the string */
    if (str) {

        *str = 0;
    }

    /* Phase string */
    while ((*format != 0) && ((size_t)(current_size) < size)) {

        /* Normal character */
        if (*format != '%') {

            *str++ = *format++;
            current_size++;
        }
        /* Escaped '%' */
        else if (*(format+1) == '%') {

            *str++ = '%';
            format += 2;
            current_size++;
        }
        /* Token delimiter */
        else {

            fill = ' ';
            width = 0;
            format++;

            /* Parse filler */
            if (*format == '0') {

                fill = '0';
                format++;
            }

            /* Parse width */
            while ((*format >= '0') && (*format <= '9')) {

                width = (width*10) + *format-'0';
                format++;
            }

            /* Check if there is enough space */
            if ((size_t)(current_size + (signed int)(width)) > size) {

                width = (unsigned char)(size - current_size);
            }

            /* Parse type */
            switch (*format) {
            case 'd':
            case 'i': num = NANO_STL_LIBC_PutSignedInt(str, fill, width, va_arg(ap, signed int)); break;
            case 'u': num = NANO_STL_LIBC_PutUnsignedInt(str, fill, width, va_arg(ap, unsigned int)); break;
            case 'x': num = NANO_STL_LIBC_PutHexa(str, fill, width, 0, va_arg(ap, unsigned int)); break;
            case 'X': num = NANO_STL_LIBC_PutHexa(str, fill, width, 1, va_arg(ap, unsigned int)); break;
            case 's': num = NANO_STL_LIBC_PutString(str, va_arg(ap, char *)); break;
            case 'c': num = NANO_STL_LIBC_PutChar(str, va_arg(ap, unsigned int)); break;
            default:
                return -1;
            }

            format++;
            str += num;
            current_size += num;
        }
    }

    /* nullptr-terminated (final \0 is not counted) */
    if ((size_t)(current_size) < size) 
    {
        *str = 0;
    }
    else 
    {
        *(--str) = 0;
        current_size--;
    }

    return current_size;
}

/** \brief Highly portable but non-efficient snprintf function */
int NANO_STL_LIBC_Snprintf(char *str, size_t size, const char *format, ...)
{
    va_list    ap;
    int rc;

    va_start(ap, format);
    rc = NANO_STL_VSNPRINTF(str, size, format, ap);
    va_end(ap);

    return rc;
}

/** \brief Highly portable but non-efficient atoi function */
int NANO_STL_LIBC_Atoi(const char* str)
{
    return NANO_STL_LIBC_Antoi(str, 10u, static_cast<size_t>(0xFFFFFFFFu));
}

/** \brief Highly portable but non-efficient itoa function */
char* NANO_STL_LIBC_Itoa(int value, char * str, int base)
{
    static const char ascii_base[] = "0123456789abcdef";
    char tmp;
    int q, r;
    char* inv_str;
    char* ret = str;

    if (str != nullptr)
    {
        if (value < 0)
        {
            (*str) = '-';
            str++;
            value = -1 * value;
        }

        inv_str = str;
        while (value >= base)
        {
            q = value / base;
            r = value - q * base;
            (*inv_str) = ascii_base[r];
            inv_str++;
            value = q;
        }
        (*inv_str) = ascii_base[value];
        (*(inv_str + 1u)) = 0;

        while (inv_str > str)
        {
            tmp = (*str);
            (*str) = (*inv_str);
            (*inv_str) = tmp;

            inv_str--;
            str++;
        }
    }

    return ret;
}

/** \brief Highly portable but non-efficient atof function */
double NANO_STL_LIBC_Atof(const char* nptr)
{
	int count = 0;
	double res = 0.;
	double int_part = 0;
	const char* int_part_str = nptr;
	double dec_part = 0;
	const char* dec_part_str;
	unsigned char negative = 0u;

	if ((nptr != nullptr) && ((*nptr) != 0))
	{
		if ((*nptr) == '-')
		{
			negative = 1u;
			nptr++;
			int_part_str++;
		}

		while (((*nptr) != 0) && ((*nptr) != '.'))
		{
			count++;
			nptr++;
		}
		int_part = static_cast<double>(NANO_STL_LIBC_Antoi(int_part_str, 10, count));

		if ((*nptr) == '.')
		{
			nptr++;
		}
		count = 0;
		dec_part_str = nptr;
		while ((*nptr) != 0)
		{
			count++;
			nptr++;
		}
		dec_part = static_cast<double>(NANO_STL_LIBC_Antoi(dec_part_str, 10, count));
		int dec_count = NANO_STL_STRNLEN(dec_part_str, count);
		while (dec_count != 0)
		{
			dec_part /= 10.;
			dec_count--;
		}

		res = int_part + dec_part;

		if (negative == 1u)
        {
            res = -1. * res;
        }
	}

	return res;
}

/** \brief Highly portable but non-efficient atoi function with radix and string length check */
int NANO_STL_LIBC_Antoi(const char* str, const int radix, size_t size)
{
    int res = 0;
    unsigned char negative = 0u;

    if ((str != nullptr) && (radix >= 2) && (radix <= 16) && (size != 0))
    {
        if ((*str) == '-')
        {
            negative = 1u;
            str++;
			size--;
        }

        while (((*str) != 0) && (size != 0))
        {
            int val = 0;
            if (((*str) >= '0') && ((*str) <= '9'))
            {
                val = (*str) - '0';
            }
            else if (((*str) >= 'a') && ((*str) <= 'f'))
            {
                val = (*str) - 'a' + 10;
            }
            else
            {
                val = (*str) - 'A' + 10;
            }
            res = (res * radix) + val;
            str++;
			size--;
        }

        if (negative == 1u)
        {
            res = -1 * res;
        }
    }

    return res;
}


/** \brief  Writes a character inside the given string */
static int NANO_STL_LIBC_PutChar(char *str, char c)
{
    *str = c;
    return 1;
}


/** \brief  Writes a string inside the given string */
static int NANO_STL_LIBC_PutString(char *str, const char *source)
{
    int num = 0;

    while (*source != 0)
    {
        *str++ = *source++;
        num++;
    }

    return num;
}


/** \brief  Writes an unsigned int inside the given string, using the provided fill &
 *          width parameters */
static int NANO_STL_LIBC_PutUnsignedInt(char *str, char fill, int width, unsigned int value)
{
    int num = 0;

    /* Take current digit into account when calculating width */
    width--;

    /* Recursively write upper digits */
    if ((value / 10u) > 0)
    {
        num = NANO_STL_LIBC_PutUnsignedInt(str, fill, width, value / 10u);
        str += num;
    }
    else
    {
    	/* Write filler characters */
        while (width > 0)
        {
        	NANO_STL_LIBC_PutChar(str, fill);
            str++;
            num++;
            width--;
        }
    }

    /* Write lower digit */
    num += NANO_STL_LIBC_PutChar(str, (value % 10u) + '0');

    return num;
}


/** \brief  Writes a signed int inside the given string, using the provided fill & width
 *          parameters */
static int NANO_STL_LIBC_PutSignedInt(char *str, char fill, int width, int value)
{
    int num = 0;
    unsigned int absolute;

    /* Compute absolute value */
    if (value < 0)
    {
        absolute = -value;
    }
    else
    {
        absolute = value;
    }

    /* Take current digit into account when calculating width */
    width--;

    /* Recursively write upper digits */
    if ((absolute / 10u) > 0)
    {
        if (value < 0)
        {
            num = NANO_STL_LIBC_PutSignedInt(str, fill, width, -(int)((absolute / 10u)));
        }
        else
        {
            num = NANO_STL_LIBC_PutSignedInt(str, fill, width, absolute / 10u);
        }
        str += num;
    }
    else
    {
        /* Reserve space for sign */
        if (value < 0)
        {
            width--;
        }

        /* Write filler characters */
        while (width > 0)
        {
        	NANO_STL_LIBC_PutChar(str, fill);
            str++;
            num++;
            width--;
        }

        /* Write sign */
        if (value < 0)
        {
            num += NANO_STL_LIBC_PutChar(str, '-');
            str++;
        }
    }

    /* Write lower digit */
    num += NANO_STL_LIBC_PutChar(str, (absolute % 10u) + '0');

    return num;
}


/** \brief  Writes an hexadecimal value into a string, using the given fill, width &
 *          capital parameters */
static int NANO_STL_LIBC_PutHexa(char *str, char fill, int width, unsigned char maj, unsigned int value)
{
    int num = 0;

    /* Decrement width */
    width--;

    /* Recursively output upper digits */
    if ((value >> 4) > 0)
    {
        num += NANO_STL_LIBC_PutHexa(str, fill, width, maj, value >> 4);
        str += num;
    }
    else
    {
    	/* Write filler chars */
        while (width > 0)
        {
        	NANO_STL_LIBC_PutChar(str, fill);
            str++;
            num++;
            width--;
        }
    }

    /* Write current digit */
    if ((value & 0x0Fu) < 10u)
    {
    	NANO_STL_LIBC_PutChar(str, (value & 0x0Fu) + '0');
    }
    else if (maj)
    {
    	NANO_STL_LIBC_PutChar(str, (value & 0x0Fu) - 10u + 'A');
    }
    else
    {
    	NANO_STL_LIBC_PutChar(str, (value & 0x0Fu) - 10u + 'a');
    }
    num++;

    return num;
}
