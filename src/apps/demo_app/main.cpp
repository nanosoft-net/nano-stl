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

#include "nano-stl.h"
#include <iostream>

using namespace nano_stl;


/** \brief Output the contents of a container on the standard output stream */
template <typename ItemType>
static void DisplayContents(const IIterable<ItemType>& container)
{
	std::cout << "-------------------" << std::endl;
	foreach_const(value, container, ItemType)
	{
		std::cout << value << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}


/** \brief Demo of array container */
static void DEMO_Array()
{
	static StaticArray<uint32_t, 15u> int_array;

	int_array[0u] = 15u;
	int_array[4u] = 321456u;
	int_array[8u] = 456489u;
	int_array[9u]++;

	DisplayContents<uint32_t>(int_array);
}

/** \brief Demo of vector container */
static void DEMO_Vector()
{
	static StaticVector<uint32_t, 10u> int_vect;

	int_vect.pushBack(65497u);
	int_vect.pushBack(23115u);
	int_vect.pushBack(489115u);
	
	uint32_t val = 0u;
	int_vect.popBack(val);
	int_vect.pushBack(val);

	int_vect.pushBack(874561u);

	int_vect[2u]++;

	DisplayContents<uint32_t>(int_vect);
}

/** \brief Demo of list container */
static void DEMO_List()
{
	static StaticList<uint16_t, 10u> int_list;

	int_list.pushBack(45u);
	int_list.pushBack(67u);
	int_list.pushBack(89u);
	int_list.pushFront(23u);
	int_list.pushFront(01u);

	DisplayContents<uint16_t>(int_list);

	IList<uint16_t>::Iterator remove_first_it(int_list);
	IList<uint16_t>::Iterator remove_last_it(int_list);
	int_list.begin(remove_first_it);
	++remove_first_it;
	remove_last_it = remove_first_it;
	++remove_last_it;
	++remove_last_it;
	int_list.remove(remove_first_it, remove_last_it);

	DisplayContents<uint16_t>(int_list);
}

/** \brief Demo of map container */
static void DEMO_Map()
{
	static StaticMap<uint8_t, const char*, 15u> int_map;

	int_map.add(20u, "20");
	int_map.add(10u, "10");
	int_map.add(30u, "30");
	int_map.add(5u, "5");
	int_map.add(15u, "15");
	int_map.add(7u, "7");
	int_map.add(12u, "12");
	int_map.add(17u, "17");
	int_map.add(25u, "25");
	int_map.add(21u, "21");
	int_map.add(35u, "35");

	int_map.remove(25u);
	int_map.remove(10u);

	DisplayContents<const char*>(int_map);
}


int main(void)
{

	DEMO_Array();
	DEMO_Vector();
	DEMO_List();
	DEMO_Map();
int * i = new int();
	return 0;
}

