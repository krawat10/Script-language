#include "Header.h"

symbol createDigitSymbol(int number)
{
	symbol symb;
	symb.value = number;
	symb._type = digitS;
	symb.isNull = false;
	symb.strenght = 0;
	return symb;
}

symbol createDigitFromArray(char* beginning, int* shift)
{
	char* newNumber = (char*)malloc(sizeof(char) * 10);
	newNumber = dotArray(newNumber, 10);
	int k = 0;
	int i = 0;
	while (beginning[i] == ' ')
	{
		i++;
	}
	while (i < 10 && isDigit(beginning[i]))
	{
		newNumber[k++] = beginning[i++];
	}
	i--;

	int size = sizeOfArray(newNumber, '.');
	int number = parseToInt(newNumber, size);
	*shift += i;

	return createDigitSymbol(number);
}

char* createVarNameFromArray(char* beginning, int* shift)
{
	char* newNumber = (char*)malloc(sizeof(char) * 10);
	newNumber = dotArray(newNumber, 10);
	int k = 0;
	int i = 0;
	while (i < 10 && isVar(beginning[i]))
	{
		newNumber[k++] = beginning[i++];
	}
	newNumber[i] = '\0';
	i--;

	int size = sizeOfArray(newNumber, '\0');
	*shift += i;

	return newNumber;
}

symbol createEmptyVariable()
{
	symbol newSymbol;
	newSymbol.isNull = true;
	newSymbol.strenght = 0;
	newSymbol.value = 0;
	newSymbol._type = variableS;
	return newSymbol;
}

bool isLetter(char letter)
{
	if ((letter >= 'A' && letter <= 'Z') ||
		(letter >= 'a' && letter <= 'z'))
	{
		return true;
	}
	else
		return false;
}



bool compareStrings(char* string1, char* string2)
{	
	int string1Size = sizeOfArray(string1, '\0');
	int string2Size = sizeOfArray(string2, '\0');
	if (string1Size != string2Size)
		return false;
	
	for (int i = 0; i < string1Size; i++)
	{
		if (string1[i] != string2[i])
		{
			return false;
		}		
	}
	return true;
}

bool isInitalizedVariable(char* name, VarVector* container)
{
	int countSymbol = -1;
	bool isEqual = true;
	for (int i = 0; i < container->size(); i++)
	{		
		if (compareStrings(name, container->at(i).name))
			return true;
	}
	return false;
}




int getVariableID(char* name, VarVector* container)
{
	for (int i = 0; i < container->size(); i++)
	{
		if (compareStrings(name, container->at(i).name))
			return i;
	}
	return -1;
}

bool isOperatorSymbol(symbol symbol)
{
	switch (symbol._type)
	{
	case andS:return true;
	case digitS:return false;
	case divideS:return true;
	case equalS:return true;
	case fobbidenS:return false;
	case greatherEqualThenS:return true;
	case greatherThenS:return true;
	case isEqualS:return true;
	case leftBracketS:return false;
	case lessEqualThenS:return true;
	case lessThenS:return true;
	case minusS:return true;
	case minusDigitS:return true;
	case moduloS:return true;
	case multiplicationS:return true;
	case negationS:return true;
	case notEqualS:return true;
	case nullValueS:return false;
	case orS:return true;
	case plusS:return true;
	case rightBracketS:return false;
	case variableS:return false;
	default:
		return false;
		break;
	}
}

bool isOperator(char* symbol)
{
	//= | & (!= ==) (< > <= >=) (+ -) (/ * %) (! -u)
	switch (*symbol)
	{
	case '=':return true;
	case '|':return true;
	case '&':return true;
	case '!':return true;
	case '<':return true;
	case '>':return true;
	case '+':return true;
	case '-':return true;
	case '/':return true;
	case '*':return true;
	case '%':return true;
	default:
		return false;
		break;
	}
}

symbol createMinusVarSymbol()
{
	symbol newSymbol;
	newSymbol._type = minusVarS;
	newSymbol.strenght = 8;
	newSymbol.value = 0;
	newSymbol.isNull = false;
	return newSymbol;
}

symbol createSymbol(char* _symbol)
{
	symbol newSymbol;
	if (_symbol[0] == '=')
	{
		if (_symbol[1] == '=')
		{
			newSymbol._type = equalS;
			newSymbol.strenght = 4;
		}
		else
		{
			newSymbol._type = isEqualS;
			newSymbol.strenght = 1;
		}
	}
	else if (_symbol[0] == '+')
	{
		newSymbol._type = plusS;
		newSymbol.strenght = 6;
	}
	else if (_symbol[0] == '-')
	{
		newSymbol._type = minusS;
		newSymbol.strenght = 6;
	}
	else if (_symbol[0] == '/')
	{
		newSymbol._type = divideS;
		newSymbol.strenght = 7;
	}
	else if (_symbol[0] == '*')
	{
		newSymbol._type = multiplicationS;
		newSymbol.strenght = 7;
	}
	else if (_symbol[0] == '!')
	{
		if (_symbol[1] == '=')
		{
			newSymbol._type = notEqualS;
			newSymbol.strenght = 4;
		}
		else
		{
			newSymbol._type = negationS;
			newSymbol.strenght = 8;
		}
	}
	else if (_symbol[0] == '(')
	{
		newSymbol._type = leftBracketS;
		newSymbol.strenght = 0;
	}
	else if (_symbol[0] == ')')
	{
		newSymbol._type = rightBracketS;
		newSymbol.strenght = 9;
	}
	//it is valid - need to correct
	else if (_symbol[0] == '-')
	{
		newSymbol._type = minusDigitS;
		newSymbol.strenght = 8;
	}
	else if (_symbol[0] == '%')
	{
		newSymbol._type = moduloS;
		newSymbol.strenght = 7;
	}
	else if (_symbol[0] == '<')
	{
		if (_symbol[1] == '=')
		{
			newSymbol._type = lessEqualThenS;
			newSymbol.strenght = 5;
		}
		else
		{
			newSymbol._type = lessThenS;
			newSymbol.strenght = 5;
		}
	}
	else if (_symbol[0] == '>')
	{
		if (_symbol[1] == '=')
		{
			newSymbol._type = greatherEqualThenS;
			newSymbol.strenght = 5;
		}
		else
		{
			newSymbol._type = greatherThenS;
			newSymbol.strenght = 5;
		}
	}
	else if (_symbol[0] == '&')
	{
		newSymbol._type = andS;
		newSymbol.strenght = 3;
	}
	else if (_symbol[0] == '|')
	{
		newSymbol._type = orS ;
		newSymbol.strenght = 2;
	}
	else
	{
		newSymbol._type = fobbidenS;
		newSymbol.strenght = 100;
	}
	newSymbol.value = 0;
	newSymbol.isNull = false;
	return newSymbol;
}