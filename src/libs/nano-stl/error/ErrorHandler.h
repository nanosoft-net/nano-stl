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

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include "nano-stl-conf.h"
#include "EventHelper.h"

namespace nano_stl
{


/** \brief Macro to trigger a critical error */
#define NANO_STL_CRITICAL_ERROR()  ErrorHandler::getInstance().criticalError()




/** \brief Error handler */
class ErrorHandler
{
    public:


        /** \brief Constructor */
        ErrorHandler();


        /** \brief Notify a critical error */
        void criticalError();



        // Check C++ version >= C++11
        #if (__cplusplus >= 201103L)

        /** \brief Critical error event */
        IEvent<>& criticalErrorEvent() { return m_critial_error_event; }

        #else // __cplusplus

        /** \brief Critical error event */
        IEvent<void>& criticalErrorEvent() { return m_critial_error_event; }

        #endif // __cplusplus


        /** \brief Get the unique instance */
        static ErrorHandler& getInstance() { return m_singleton; }


    private:



        // Check C++ version >= C++11
        #if (__cplusplus >= 201103L)

        /** \brief Critical error event */
        EventHelper<NANO_STL_MAX_ERROR_HANDLER_LISTENERS> m_critial_error_event;

        #else // __cplusplus

        /** \brief Critical error event */
        EventHelper<NANO_STL_MAX_ERROR_HANDLER_LISTENERS, void> m_critial_error_event;

        #endif // __cplusplus


        /** \brief Unique instance */
        static ErrorHandler m_singleton;

};

}

#endif // ERRORHANDLER_H
