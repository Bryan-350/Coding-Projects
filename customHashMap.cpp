/*  Name: Bryan Flores
    Description: 
    This program was an assignment made to test my understanding of CS 
    concepts such as modular code, object-oriented programming, class templates
    hashing functions and memory allocation. This file serves as the basis for a
    custom hash map meant to be plugged in place for the unordered map in the 
    hashTable.cpp file. This map uses separate chaining with an array of linked lists
    of size 1. 
*/

#include "hashMap.h"
#include <cmath>
#include <string>
using namespace std;

template <class t1, class t2>
const hashMap<t1, t2>& hashMap<t1, t2>::operator=(const hashMap<t1, t2>& rhs)
{
	if (this != &rhs)
	{
		//deletes the current map, and then copies rhs into it
		deallocateMap();
		copyMap(rhs);
	}
	return *this;
}

template <class t1, class t2>
t2& hashMap<t1, t2>::operator[](t1 key)
{
	size_t i = 1;

	//if load is past 20%, resize the map
	if(items1 >= capacity * .2  || items2 >= capacity * .2)
	{
		resize(capacity);
	}

	//create the indexes for the map
	size_t index1 = h1(key) % capacity;
	size_t index2 = h2(key) % capacity;

	while (true)
	{
		//loop through the list to see if the key exists
		node* temp = table1[index1];
		while(temp != nullptr)
		{
			if (temp->key == key)
			{
				//if key exists, return it
				return temp->value;
			}
			temp = temp->link;
		}

		// if key didnt exist, this will create it
		if (table1[index1] == nullptr || items1 <= 1)
		{
			node* newNode = new node;

			//sets the fields to the new node
			newNode->key = key;
			newNode->value = t2();
			newNode->link = table1[index1];
			//adds it to the array
			table1[index1] = newNode;

			//returns the nodes value
			return newNode->value;	
			

			if (newNode->link == nullptr)
			{
				items1++;	
				table1[index1]->key = key;
				table1[index1]->value = t2();
				table1[index1]->link = nullptr;
				return table1[index1]->value;
			}					
		}	
		
		//step 5
		temp = table2[index2];
		//loop through the list to see if the key exists
		while (temp != nullptr)
		{
			if (temp->key == key)
			{	
				//if key exists, return it
				return temp->value;
			}
			temp = temp->link;
		}

		if (table2[index2] == nullptr || items2 <= 1) 
		{
			node* newNode = new node;

			//sets the fields to the new node
			newNode->key = key;
			newNode->value = t2();
			newNode->link = table2[index2];
			//sets the node into the table
			table2[index2] = newNode;

			return newNode->value;

			if (newNode->link == nullptr)
			{
				items1++;	
				table2[index2]->key = key;
				table2[index2]->value = t2();
				table2[index2]->link = nullptr;
				return table2[index2]->value;
			}	
		}

		updates the //indexes
		index1 = h1(key) + i * h2(key);
        index2 = h2(key) + i * h1(key);
    }
}

template <class t1, class t2>
void hashMap<t1, t2>::resize(size_t amount)
{
	//creates the new, bigger tables
	node ** newTable1 = new node*[capacity + amount];
	node ** newTable2 = new node*[capacity + amount];

	//sets the tables to nullptr like the constructor
	for (int i = 0; i < capacity; i++)
			newTable1[i] = newTable2[i] = nullptr;

	//sets
	for (size_t i = 0; i < capacity; i++)
	{
		//sets the temp node to the first table to loop
		node* temp = table1[i];
		
		//copies the table1 to newTable 1
		while (temp != nullptr)
		{
			//updates the index
			size_t newIndex1 = h1(temp->key) % (capacity + amount);
			node* next = temp->link;
			//adds node to new table
			temp->link = newTable1[newIndex1];
			newTable1[i] = next;
			temp = temp->link;
		}

		//sets the temp node to the second table to loop
		temp = table2[i];

		//copies the table1 to newTable 1	
		while (temp != nullptr)
		{
			//updates the index
			size_t newIndex2 = h2(temp->key) % (capacity + amount);
			node* next = temp->link;
			//adds node to new table
			next->link = newTable2[newIndex2];
			newTable2[i] = next;
			temp = temp->link;
		}	
	}
	// deletes the old tables
	delete [] table1;
	delete [] table2;

	//sets the old table pointers to the new ones
	table1 = newTable1;
	table2 = newTable2;

	//updates the capacity
	capacity += amount;	
}

template <class t1, class t2>
void hashMap<t1, t2>::copyMap(const hashMap<t1, t2>& map)
{
	//copy the fields from map
	capacity = map.capacity;
	items1 = map.items1;
	items2 = map.items2;	

	//initiliaze the tables
	table1 = new node*[capacity];
	table2 = new node*[capacity];

	//set each index in the arrays to null
	for (size_t i = 0; i < capacity; i++)
	{
		table1[i] = table2[i] = nullptr;
	}

	//copies the old map to the current one
	for (size_t i = 0; i < items1; ++i)
	{
		if(map.table1[i] != nullptr)
		{
			node* newNode = new node;
            
			//copy the fields
            newNode->key = map.table1[i]->key;
            newNode->value = map.table1[i]->value;
			//set newNode into the table
            table1[i] = newNode;

			//hard coded like Jimi suggested, if link isnt null then theres another node
            if(map.table1[i]->link != nullptr)
            {
				//repeat the steps above
                node* newNode = new node;
                newNode->link = nullptr;
                newNode->key = map.table1[i]->key;
                newNode->value = map.table1[i]->value;
                table1[i]->link = newNode;
				
            }
			//otherwise newNode will point to null as its the end
			else
				newNode->link = nullptr;
		}

			
	}	
	for (size_t i = 0; i < items2; ++i)
	{
		if(map.table2[i] != nullptr)
		{
			node* newNode = new node;
            //copy the fields
            newNode->key = map.table2[i]->key;
            newNode->value = map.table2[i]->value;
			//set newNode into the table
            table2[i] = newNode;
			//hard coded like Jimi suggested, if link isnt null then theres another node
            if(map.table2[i]->link != nullptr)
            {
				//repeat the steps above
                node* newNode = new node;
                newNode->link = nullptr;
                newNode->key = map.table2[i]->key;
                newNode->value = map.table2[i]->value;
                table2[i]->link = newNode;
            }
			//otherwise newNode will point to null as its the end
			else
				newNode->link = nullptr;
		}		
	}
}

template <class t1, class t2>
void hashMap<t1, t2>::deallocateMap()
{
	//if the table isnt empty we will deallocate it
	if(table1 != nullptr)
	{
	
		for (size_t i = 0; i < capacity; ++i)
		{
			
			node* temp = table1[i];
			//loop through to delete each node
			while(temp != nullptr)
			{
				node* next = temp->link;
				delete temp;
				temp = next;
			}		
			//sets temp to nullptr so that there is no mem leak
			temp = nullptr;	
		}

		//deletes the table pointer and sets to null to avoid memory leaks
		delete [] table1;
		table1 = nullptr;
	}

	//if the table isnt empty we will deallocate it
	if(table2 != nullptr)
	{
		for (size_t i = 0; i < capacity; ++i)
		{
			node * temp = table2[i];
			//loop through to delete each node
			while(temp != nullptr)
			{
				node* next = temp->link;
				delete temp;
				temp = next;
			}
			//sets temp to nullptr so that there is no mem leak
			temp = nullptr;
		}
		//deletes the table pointer and sets to null to avoid memory leaks
		delete [] table2;	
		table2 = nullptr;
	}
}

template <class t1, class t2>
size_t hashMap<t1, t2>::h1(const string& s) const
{
	size_t result = 0;
	for (size_t i = 0; i < s.length() - 1; i++)
	{	
		//stores the sumation into result
		result += (pow(10, i) * s[i]);
	}
	return result;
}

template <class t1, class t2>
size_t hashMap<t1, t2>::h2(const string& s) const
{
	size_t result = 0;
	for (size_t i = 0; i < s.length() - 1; i++)
	{
		//stores the sumation into result
		result += (pow(10, i) * s[s.length() - 1 - i]);
	}
	return result;	
}
