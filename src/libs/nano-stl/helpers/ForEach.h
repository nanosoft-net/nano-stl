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

#ifndef FOREACH_H
#define FOREACH_H

#include "IIterable.h"

namespace nano_stl
{

/** \brief Helper class to iterate by the mean of the foreach macros */
template <typename T>
struct ForEachHelper
{
	ForEachHelper(IIterable<T>& _cont)
	: cont(_cont)
	, iter(cont.it())
	, loop(true)
	{}

	IIterable<T>& cont;
	IIterator<T>& iter;
	bool loop;
};

/** \brief Helper class to iterate by the mean of the foreach_const macros */
template <typename T>
struct ForEachConstHelper
{
	ForEachConstHelper(const IIterable<T>& _cont)
	: cont(_cont)
	, iter(cont.const_it())
	, loop(true)
	{}

	const IIterable<T>& cont;
	IConstIterator<T>& iter;
	bool loop;
};

/////// For each macros //////


/** \brief Macro to iterate through a container */
#define foreach(var, container, type) \
for (nano_stl::ForEachHelper<type> foreach_helper((container)); foreach_helper.iter != foreach_helper.cont.end(); ++foreach_helper.iter, foreach_helper.loop = true) \
		for (type& var = (*foreach_helper.iter); foreach_helper.loop; foreach_helper.loop = false)


/** \brief Macro to const iterate through a container */
#define foreach_const(var, container, type) \
for (nano_stl::ForEachConstHelper<type> foreach_helper((container)); foreach_helper.iter != foreach_helper.cont.cend(); ++foreach_helper.iter, foreach_helper.loop = true) \
		for (const type& var = (*foreach_helper.iter); foreach_helper.loop; foreach_helper.loop = false)


}

#endif // FOREACH_H
