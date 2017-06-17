#include "Header.h"
#include <cstdlib>

VarVector::VarVector()
{
	this->currentUse = 0;
	this->memory = 1;
	tab = new var[1];
	InitalizeHashTable();
}

void VarVector::InitalizeHashTable()
{
	hashTable = (int**)malloc(sizeof(int*) * 172* 2);
	for (int i = 0; i < 172; i++)
	{
		hashTable[i] = (int*)malloc(sizeof(int) * 5);
		hashTable[i][0] = 0;
		hashTable[i][4] = -1;
	}
}


VarVector::~VarVector()
{
	delete[] tab;
	free(hashTable);
}

void VarVector::pop()
{
	currentUse--;
	if ((3 * currentUse < memory) && (currentUse > 1))
	{
		resize(memory / 2);
	}
}

bool VarVector::empty()
{
	return (currentUse == 0);
}

void VarVector::resize(int newSize)
{
	memory = newSize;
	var* buffer = new var[newSize];
	for (int i = 0; i < currentUse; i++)
	{
		buffer[i] = tab[i];
	}
	delete[] tab;
	tab = buffer;
}

var &VarVector::at(int index)
{
	return tab[index];
}

int VarVector::isInitalizedVariable(char* nameToFind)
{
	int position;
	if (isVarLetter(*(nameToFind+1)))
	{
		position = (*nameToFind - 65) + (*(nameToFind + 1) - 65);
	}
	else
	{
		position = (*nameToFind - 65);
	}
	
	int index;
	for (int i = 1; i < hashTable[position][0]; i++)
	{
		index = hashTable[position][i];
		if (compareStrings(tab[index].name, nameToFind))
		{
			return index;
		}
	}
	return -1;
}

int VarVector::size()
{
	return currentUse;
}

void VarVector::clear()
{
	delete[] tab;
	tab = new var[1];
	currentUse = 0;
	memory = 1;
}

void VarVector::push_back(var newObject)
{
	if (newObject.name[0] == NULL)
		return;

	tab[currentUse] = newObject;
	addToHashTable(currentUse);
	currentUse++;
	if (currentUse == memory)
	{
		resize(memory*2);
	}
	addToHashTable(currentUse - 1);
}

void VarVector::addToHashTable(int index)
{
	
	int position;
	if (isVarLetter(tab[index].name[1]))
	{
		position = (tab[index].name[0] - 65) + (tab[index].name[0] - 65);
	}
	else
	{
		position = (tab[index].name[0] - 65);
	}

	int sizeOfParticularHashField = hashTable[position][0];
	if (hashTable[position][sizeOfParticularHashField + 1] == -1)
	{		
		int* newArray = (int*)malloc(sizeof(int*) * (sizeOfParticularHashField + 2) * 2);
		for (int i = 0; i < (sizeOfParticularHashField + 2); i++)
		{
			newArray[i] = hashTable[position][i];
		}
		free(hashTable[position]);
		hashTable[position] = newArray;
		hashTable[position][2*sizeOfParticularHashField - 1] = -1;
	}
	hashTable[position][sizeOfParticularHashField + 1] = index;
	hashTable[position][0]++;
}
