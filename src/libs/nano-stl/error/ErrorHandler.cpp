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

#include "ErrorHandler.h"


namespace nano_stl
{


/** \brief Unique instance */
ErrorHandler ErrorHandler::m_singleton;



/** \brief Constructor */
ErrorHandler::ErrorHandler()
: m_critial_error_event()
{
    // Check unique instance
    if (this != &m_singleton)
    {
        criticalError();
    }
}


/** \brief Notify a critical error */
void ErrorHandler::criticalError()
{
    // Trigger event
    m_critial_error_event.trigger();

    // Infinite loop
    while(true)
    {}
}

}
