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


/** \brief Callback for delegate 1 */
static uint16_t DELEGATE1_Callback(uint32_t event_data)
{
	std::cout << "DELEGATE1_Callback : " << event_data << std::endl;
	return 4321u;
}

/** \brief Callback for delegate 2 */
static bool DELEGATE2_Callback(const char* event_data)
{
	std::cout << "DELEGATE2_Callback : " << event_data << std::endl;
	return true;
}

/** \brief Callback for delegate 3 */
class Delegate3Callback
{
	public:

		/** \brief Callback for delegate 3 */
		bool DELEGATE3_Callback(const char* event_data)
		{
			std::cout << "Delegate3Callback::DELEGATE3_Callback : " << event_data << std::endl;
			return false;
		}		
};

/** \brief Callback for delegate 4 */
static void DELEGATE4_Callback()
{
	std::cout << "DELEGATE4_Callback!" << std::endl;
}

/** \brief Callback for delegate 5 */
static char DELEGATE5_Callback(uint32_t a, const char* b, uint16_t c)
{
	std::cout << "DELEGATE5_Callback : " << a << ", " << b << ", " << c << std::endl;
	return 'k';
}

/** \brief Callback for delegate 6 */
class Delegate6Callback
{
	public:

		/** \brief Callback for delegate 6 */
		char DELEGATE6_Callback(uint32_t a, const char* b, uint16_t c)
		{
			std::cout << "Delegate6Callback::DELEGATE6_Callback : " << a << ", " << b << ", " << c << std::endl;
			return 'o';
		}		
};

/** \brief Demo of delegates objects */
static void DEMO_Delegates()
{
	std::cout << "-------------------" << std::endl;

	FDelegate<uint16_t, uint32_t> delegate_1(DELEGATE1_Callback);
	const uint16_t ret_1 = delegate_1.invoke(456789);
	std::cout << "delegate_1 : " << ret_1 << std::endl;

	FDelegate<bool, const char*> delegate_2(DELEGATE2_Callback);
	const bool ret_2 = delegate_2.invoke("hop!");
	std::cout << "delegate_2 : " << ret_2 << std::endl;

	Delegate3Callback delegate3_callback;
	Delegate<bool, const char*> delegate_3 = Delegate<bool, const char*>::create<Delegate3Callback, &Delegate3Callback::DELEGATE3_Callback>(delegate3_callback);
	const bool ret_3 = delegate_3.invoke("hop!");
	std::cout << "delegate_3 : " << ret_3 << std::endl;


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)

	FDelegate<void> delegate_4(DELEGATE4_Callback);

#else

	FDelegate<void, void> delegate_4(DELEGATE4_Callback);

#endif // __cplusplus

	delegate_4.invoke();


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)

	FDelegate<char, uint32_t, const char*, uint16_t> delegate_5(DELEGATE5_Callback);
	const char ret_5 = delegate_5.invoke(56789u, "hop!", 1234u);
	std::cout << "delegate_5 : " << ret_5 << std::endl;

	Delegate6Callback delegate6_callback;
	Delegate<char, uint32_t, const char*, uint16_t> delegate_6 = Delegate<char, uint32_t, const char*, uint16_t>::create<Delegate6Callback, &Delegate6Callback::DELEGATE6_Callback>(delegate6_callback);
	const char ret_6 = delegate_6.invoke(56789u, "hop!", 1234u);
	std::cout << "delegate_6 : " << ret_6 << std::endl;

#else

	std::cout << "Delegate with multiple parameters not supported in C++ versions < 11" << std::endl;

#endif // __cplusplus


	std::cout << "-------------------" << std::endl;
}


/** \brief Callback for event 1 */
static void EVT1_Callback(uint32_t event_data)
{
	std::cout << "EVT1_Callback : " << event_data << std::endl;
}

/** \brief Callback for event 2 */
static void EVT2_Callback(const char* event_data)
{
	std::cout << "EVT2_Callback : " << event_data << std::endl;
}

/** \brief Callback class for event 2 */
class Evt2Callback
{
	public:

		/** \brief Callback for event 2 */
		void EVT2_Callback(const char* event_data)
		{
			std::cout << "Evt2Callback::EVT2_Callback : " << event_data << std::endl;
		}		
};

/** \brief Callback for event 3 */
static void EVT3_Callback()
{
	std::cout << "EVT3_Callback!" << std::endl;
}

/** \brief Demo of events objects */
static void DEMO_Events()
{
	std::cout << "-------------------" << std::endl;

	EventHelper<1u, uint32_t> evt1;
	IEvent<uint32_t>::EventHandlerF event_handler1(EVT1_Callback);
	evt1.bind(event_handler1);
	evt1.trigger(123456);

	EventHelper<2u, const char*> evt2;
	IEvent<const char*>::EventHandlerF event_handler2(EVT2_Callback);
	evt2.bind(event_handler2);
	Evt2Callback evt2_callback;
	IEvent<const char*>::EventHandlerM event_handler3 = IEvent<const char*>::EventHandlerM::create<Evt2Callback, &Evt2Callback::EVT2_Callback>(evt2_callback);
	evt2.bind(event_handler3);
	evt2.trigger("hop!");


// Check C++ version >= C++11
#if (__cplusplus >= 201103L)

	EventHelper<1u> evt3;
	IEvent<>::EventHandlerF event_handler4(EVT3_Callback);

#else

	EventHelper<1u, void> evt3;
	IEvent<void>::EventHandlerF event_handler4(EVT3_Callback);

#endif // __cplusplus

	evt3.bind(event_handler4);
	evt3.trigger();

	std::cout << "-------------------" << std::endl;
}


int main(void)
{

	DEMO_Array();
	DEMO_Vector();
	DEMO_List();
	DEMO_Map();

	DEMO_Delegates();
	DEMO_Events();

	return 0;
}

