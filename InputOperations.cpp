#include "Header.h"

//
//first line of code. Function get numbers of operation and parse it to int
//
int getLinesOfOperations()
{
	char* inputOfNumberOfLines = (char*)malloc(sizeof(char) * 10);
	dotArray(inputOfNumberOfLines, 10);
	cin >> inputOfNumberOfLines;
	cin.get();
	int size = sizeOfArray(inputOfNumberOfLines, '.');
	return parseToInt(inputOfNumberOfLines, size - 1);
}


//
//Second line of code. Function gets variable names from second line of code and creates array of strings.
//reference value "amountOfVariable" is changes to value which indicate on number of initalized variables
//
char** getVaraibles(int* amountOfVariable)
{	
	
	char* input = (char*)malloc(sizeof(char) * 1000);
	dotArray(input, 1000);
	cin.get(input, 1000);
	int sizeOfInput = sizeOfArray(input, '.');
	int numberOfVariables = 0;
	
	for (int i = 0; i < sizeOfInput-1; i++)
	{
		if (input[i] == ' ' && input[i+1] != ' ')
			numberOfVariables++;
	}
	numberOfVariables++;

	char** variablesArray = (char**)malloc(sizeof(char*) * numberOfVariables);
	for (int i = 0; i < numberOfVariables; i++)
	{
		variablesArray[i] = (char*)malloc(sizeof(char) * 10);
	}

	int i = 0;	
	int count = 0;
	while (i < sizeOfInput)
	{
		int k = 0;
		while (*(input + i) != ' ' && i < sizeOfInput)
		{
			variablesArray[count][k++] = *(input + i++);
		}
		variablesArray[count++][k] = '\0';
		i++;
	}
	*amountOfVariable = numberOfVariables;
	return variablesArray;
}