#include "Header.h"
#include <cstdlib>

queue::queue()
{	
	this->first = 0;
	this->last = 0;
	this->memory = 1;
	tab = new symbol[1];
}


//
//Always, when destructor is called size of allocated memory equal 1,
//because resize function decrease size (every time the Result function pop all elements of queue)
//
queue::~queue()
{
	tab = nullptr;
}

void queue::pop()
{
	first++;
	if ((3 * currentUse < memory) && (currentUse > 1))
	{
		resize(memory / 2);
	}
}

bool queue::empty()
{
	return ((last-first) == 0);
}

void queue::resize(int newSize)
{
	memory = newSize;
	symbol* buffer = new symbol[newSize];
	for (int i = first, j = 0; i < last; i++, j++)
	{
		buffer[j] = tab[i];
	}
	last = size();
	first = 0;
	delete[] tab;
	tab = buffer;
}

symbol queue::front()
{
	return tab[first];
}

int queue::size()
{
	return last - first;;
}

void queue::push(symbol newObject)
{
	tab[last] = newObject;
	last++;
	if (last == memory)
	{
		if (((last - first) * 3 < memory) && size() > 1)
		{			
			resize(memory/2);
		}
		else
		{
			resize(memory + 10);
		}
	}

}
