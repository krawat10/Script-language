#include "Header.h"

bool isDigit(char symbol)
{	
	return (symbol >= 48 && symbol <= 57);
}

bool isVarLetter(char letter)
{
	return(letter >= 'A' && letter <= 'Z' && letter >= 'a' && letter <= 'z');
}

bool isMinusDigit(char* tab, symbol lastSymbol)
{
	char s = nextSymbol(tab, 1);
	if (lastSymbol._type == digitS || lastSymbol._type == variableS)
	{
		return false;
	}	
	else if (*tab == '-' && isDigit(s) )
	{
		return true;
	}
	return false;
}

//
//function return number of shift (how far is next symbol, not space) to n symbol from begining 
//
int nextSymbolShift(char* tab, int nsymbol)
{
	int count = 1;
	int currentNSymbol = 0;
	char result;
	while (currentNSymbol != nsymbol)
	{
		if (*(tab + count) == '\0')
		{
			return -1;
		}
		else if (*(tab + count) != ' ')
		{
			result = *(tab + count);
			currentNSymbol++;
		}
		count++;
	}
	return count;
}


//
//function return next chr value (avoid spaces and other space symbols)
//
char nextSymbol(char* tab, int nsymbol)
{
	int count = 1;
	int currentNSymbol = 0;
	char result;
	while (currentNSymbol != nsymbol)
	{
		if (*(tab + count) == '\0')
		{
			return *(tab + count);
		}
		else if (*(tab + count) != ' ')
		{
			result = *(tab + count);
			currentNSymbol++;
		}		
		count++;
	}
	return result;
 }

bool isVar(char string)
{
	return (!isDigit(string) && (createSymbol(&string)._type == fobbidenS) && (string != ' '));	
}

bool isMinusVar(symbol lastSymbol, char* input)
{
	if (*input != '-')
		return false;
	else
	{
		char symbolAfterMinus = nextSymbol(input, 1);
		if (isVar(symbolAfterMinus) && (isOperatorSymbol(lastSymbol) || lastSymbol._type == fobbidenS))
		{
			return true;
		}
	}
	return false;
}


//
//function return string which contain name of variable
//reference variable *shift is increase by size of string
//
char* getVarName(char* input, int* shift)
{
	int i = 0;
	char* varName = (char*)malloc(sizeof(char) * 10);
	while (isVar(*(input + i)))
	{	
			varName[i] = *(input + i++);	
	}
	varName[i] = '\0';
	*shift += i - 1;
	return varName;
}

//
//Function return Variable container with null values and full names
//
VarVector* charToVar(char** variables, int amountOfVariable)
{
	VarVector* variablesContainer = new VarVector();
	for (int i = 0; i < amountOfVariable; i++)
	{
		var newVariable;
		newVariable.name = variables[i];
		newVariable.value = NULL;
		newVariable.isInitalized = true;
		newVariable.isNull = true;
		variablesContainer->push_back(newVariable);
	}
	return variablesContainer;
}


//
//It is a function which is necessary to change char '1' to int 1
//
int chatToInt(char symbol)
{
	int number = symbol - 48;
	return number;
}


//
//Function dots all array (clean array from trash symbols) and ends it whit '\0' symbol
//
char* dotArray(char* table, int size)
{
	for (int i = 0; i < size; i++)
	{
		table[i] = '.';
	}
	table[size - 1] = '\0';
	return table;
}

int sizeOfArray(char* table, char symbolOfEnd)
{
	int i = 0;
	while (table[i++] != symbolOfEnd);
	return i - 1;
}

//
//Parse n-digit char array to number ('12' -> 12)
//
int parseToInt(char* table, int size)
{
	int index = 0;
	int number = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		number *= 10;
		number += (table[index++] - 48);

	}
	return number;
}