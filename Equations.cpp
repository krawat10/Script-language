#include "Header.h"

symbol resultOfMathEquation(symbol firstVariable, symbol operation, symbol secondVariable, VarVector* variables)
{
	//buffer symbol
	symbol resultValue;
	resultValue._type = digitS;
	resultValue.isNull = false;

	//secure all variable against wrong initalizing new variable
	if (firstVariable.isNull)
		firstVariable.value = 0;
	if (secondVariable.isNull)
		secondVariable.value = 0;

	//
	//Oparation type depends on middle or first symbol (2+2, !a), switch contition is splited into two (arthmetic and logic operations)
	//
	switch (operation._type)
	{
	case orS:
	{
		if ((!firstVariable.isNull) || (!secondVariable.isNull))
			resultValue.isNull = false;
		else
			resultValue.isNull = true;
		resultValue.value = 0;
		break;
	}
	case andS:
	{
		if ((!firstVariable.isNull) && (!secondVariable.isNull))
			resultValue.isNull = false;
		else
			resultValue.isNull = true;
		resultValue.value = 0;
		break;
	}
	case isEqualS:
	{
		firstVariable.value = secondVariable.value;
		firstVariable.isNull = secondVariable.isNull;
		resultValue = firstVariable;
		variables->at(firstVariable.index).value = firstVariable.value;
		variables->at(firstVariable.index).isNull = firstVariable.isNull;
		break;
	}
	//
	//Begin of arythmetic operation
	//If one or two variables is NULL, then result is NULL
	//
	default:
	{
		if (firstVariable.isNull || secondVariable.isNull)
		{
			resultValue.value = 0;
			resultValue.isNull = true;
		}
		else
		{
			resultValue.value = 0;
			resultValue.isNull = false;
			switch (operation._type)
			{
			case plusS:
			{
				resultValue.value = firstVariable.value + secondVariable.value;
				break;
			}
			case minusS:
			{
				resultValue.value = firstVariable.value - secondVariable.value;
				break;
			}
			case multiplicationS:
			{
				resultValue.value = firstVariable.value * secondVariable.value;
				break;
			}
			case divideS:
			{
				if (secondVariable.value == 0)
				{
					resultValue.isNull = true;
					resultValue.value = 0;
				}
				else
				{
					resultValue.value = firstVariable.value / secondVariable.value;
				}
				break;
			}
			case moduloS:
			{
				resultValue.value = firstVariable.value % secondVariable.value;
				break;
			}
			case greatherThenS:
			{
				resultValue.isNull = firstVariable.value <= secondVariable.value;
				resultValue.value = 0;
				break;
			}
			case lessThenS:
			{
				resultValue.isNull = firstVariable.value >= secondVariable.value;
				resultValue.value = 0;
				break;
			}
			case greatherEqualThenS:
			{
				resultValue.isNull = firstVariable.value < secondVariable.value;
				resultValue.value = 0;
				break;
			}
			case lessEqualThenS:
			{
				resultValue.isNull = firstVariable.value > secondVariable.value;
				resultValue.value = 0;
				break;
			}
			case equalS:
			{
				resultValue.isNull = !(firstVariable.value == secondVariable.value);
				resultValue.value = 0;
				break;
			}
			case notEqualS:
			{
				resultValue.isNull = !(firstVariable.value != secondVariable.value);
				resultValue.value = 0;
				break;
			}
			}
		}
	}
	}
	return resultValue;
}