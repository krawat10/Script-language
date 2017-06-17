#include "Header.h"
#include <cstdlib>

stack::stack()
{
	this->currentUse = 0;
	this->memory = 1;
	tab = new symbol[1];
}

//
//Always, when destructor is called size of allocated memory equal 1,
//because resize function decrease size (every time the Result function pop all elements of stack)
//
stack::~stack()
{
	tab = nullptr;
}

void stack::pop()
{
	currentUse--;
	if ((3 * currentUse < memory) && (currentUse > 1))
	{
		resize(memory / 2);
	}
}

bool stack::empty()
{
	return (currentUse == 0);
}

void stack::resize(int newSize)
{
	memory = newSize;
	symbol* buffer = new symbol[newSize];
	for (int i = 0; i < currentUse; i++)
	{
		buffer[i] = tab[i];
	}
	delete[] tab;
	tab = buffer;	
}

symbol stack::top()
{
	return tab[currentUse - 1];
}

int stack::size()
{
	return currentUse;
}

void stack::push(symbol newObject)
{
	tab[currentUse] = newObject;
	currentUse++;
	if (currentUse == memory)
	{
		resize(memory + 10);
	}
	
}
