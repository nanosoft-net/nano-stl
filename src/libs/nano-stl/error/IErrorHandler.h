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

#ifndef IERRORHANDLER_H
#define IERRORHANDLER_H

#include "IEvent.h"


/** \brief Macro to trigger a critical error */
#define NANO_STL_CRITICAL_ERROR()  nano_stl::IErrorHandler::getInstance().criticalError()



namespace nano_stl
{


/** \brief Interface for all error handlers implementations */
class IErrorHandler
{
    public:


        /** \brief Notify a critical error */
        virtual void criticalError() = 0;



        // Check C++ version >= C++11
        #if (__cplusplus >= 201103L)

        /** \brief Critical error event */
        virtual IEvent<>& criticalErrorEvent() = 0;

        #else // __cplusplus

        /** \brief Critical error event */
        virtual IEvent<void>& criticalErrorEvent() = 0;

        #endif // __cplusplus


        /** \brief Get the unique instance */
        static IErrorHandler& getInstance();

};

}

#endif // IERRORHANDLER_H
