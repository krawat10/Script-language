#include "header.h"

//input - array of data, which begin is where contition starts
//count - current position on array
//endofarray - point where array is end
int conditionLoop(char* input, int count, int sizeOfArray, int* currentnumberofoperation, int maxnumberofoperation, VarVector* variables)
{
	int beginIndex = count;
	count++;


	int shiftOfCondition;
	int shiftOfLoop;


	int rightBracketCounter = 0;
	int leftBracketCounter = 0;
	int whileCount = count;

	//
	//Calculating range of loop (left and right bracket), subfunction also include internal loops and conditions
	//the result is value, which indicate where is ends loop
	while ((whileCount++ < sizeOfArray))
	{
		if (*(input + whileCount) == '{')
			leftBracketCounter++;
		else if (*(input + whileCount) == '}')
			rightBracketCounter++;

		if (leftBracketCounter != 0)
		{
			if (leftBracketCounter == rightBracketCounter)break;
		}
	}
	whileCount++;

	//
	//if has another loop which ends when loop reach '{' bracket. Loop return symbol which can be null/!null symbol.
	//
	if (!condition(input, count, sizeOfArray, currentnumberofoperation, maxnumberofoperation, variables, &shiftOfCondition).isNull)
	{		
		//shift necessary to avoid '{' bracket
		shiftOfCondition++;
		//main loop
		condition(input, shiftOfCondition, sizeOfArray, currentnumberofoperation, maxnumberofoperation, variables, &shiftOfLoop);
	}	
	//
	//each check of contition incements operation counter
	//
	*currentnumberofoperation = *currentnumberofoperation + 1;
	

	return whileCount - beginIndex;
}


//
//Function where loops are interpreted
//
int loop(char* input, int count, int sizeOfArray, int* currentnumberofoperation, int maxnumberofoperation, VarVector* variables)
{
	int beginIndex = count;
	count++;


	int shiftOfCondition;
	int shiftOfLoop;


	int rightBracketCounter = 0;
	int leftBracketCounter = 0;
	int whileCount = count;

	//
	//counting begining and ending of loop
	//
	while ((whileCount++ < sizeOfArray))
	{
		if (*(input + whileCount) == '{')
			leftBracketCounter++;
		else if (*(input + whileCount) == '}')
			rightBracketCounter++;

		if (leftBracketCounter != 0)
		{
			if (leftBracketCounter == rightBracketCounter)break;
		}
	}
	whileCount++;

	//
	//Get "safe" counter for all loops. Counter is not necessary for every loops
	//
	symbol loopConditionCount;
	if (isDigit(*(input + whileCount)))
	{
		loopConditionCount = createDigitFromArray((input + whileCount), &whileCount);
		whileCount++;
	}
	else
	{
		loopConditionCount.isNull = true;
	}


	while (!condition(input, count, sizeOfArray, currentnumberofoperation, maxnumberofoperation, variables, &shiftOfCondition).isNull)
	{		
		if (!loopConditionCount.isNull)
		{
			if (loopConditionCount.value-- <= 0)
				break;
		}
		*currentnumberofoperation = *currentnumberofoperation + 1;
		shiftOfCondition++;
		condition(input, shiftOfCondition, sizeOfArray, currentnumberofoperation, maxnumberofoperation, variables, &shiftOfLoop);
		if (*currentnumberofoperation >= maxnumberofoperation)
			break;
	}
	*currentnumberofoperation = *currentnumberofoperation + 1;
	

	return whileCount - beginIndex;
}


//
//Main part of program, function interpreting each symbol from whole array.
//
symbol condition(char* data, int count, int sizeOfArray, int* numberOfOperation,
	int maxnumberofoperation, VarVector* variables, int* shift)
{
	bool isPossibleEndEquation = false;
	queue equationQueue;
	stack operatorStack;
	symbol resultValue = symbol();
	VarVector resultVar = VarVector();

	symbol lastSymbol;
	lastSymbol.isNull = true;
	lastSymbol.strenght = 0;
	lastSymbol._type = fobbidenS;

	for (count; count < sizeOfArray; count++)
	{
		//
		//skip next symbol if it is space of tab
		//
 		if (*(data + count) == ' ' || *(data + count) == '\t')
		{
			isPossibleEndEquation = true;
			continue;
		}
		//
		//It happens when interpreter find whitesoace. Interpreter must find out, that it is end of equation, or just ordinary space
		//
		else if (isPossibleEndEquation)
		{
			symbol nextSymbol = createSymbol(data + count);
			if (isMinusDigit((data + count), lastSymbol) || isDigit(*(data + count)) || isVar(*(data + count)) || *(data + count) == '(')
			{
				if (lastSymbol._type == digitS || lastSymbol._type == variableS || lastSymbol._type == rightBracketS)
				{
					resultValue = resultOfEquation(&equationQueue, &operatorStack, &resultVar, variables, numberOfOperation, maxnumberofoperation);								
					operatorStack = stack();
					equationQueue = queue();
					resultVar.clear();
					if (*numberOfOperation > maxnumberofoperation)
					{
						break;
					}
				}
			}
			else if (isOperatorSymbol(nextSymbol) && isOperatorSymbol(lastSymbol))
			{
				if (!(nextSymbol._type == negationS || nextSymbol._type == minusS))
				{
					resultValue = resultOfEquation(&equationQueue, &operatorStack, &resultVar, variables, numberOfOperation, maxnumberofoperation);
					operatorStack = stack();
					equationQueue = queue();
					resultVar.clear();
				if (*numberOfOperation > maxnumberofoperation)
				{
					break;
				}
				}
			}			
		}


		if (*(data + count) == '?')
		{
			count += conditionLoop(data, count, sizeOfArray, numberOfOperation, maxnumberofoperation, variables);
			continue;
		}
		else if (*(data + count) == '@')
		{
			count += loop(data, count, sizeOfArray, numberOfOperation, maxnumberofoperation, variables);
			continue;
		}
		else if (*(data + count) == '{')
		{
			break;
		}
		else if (*(data + count) == '}')
		{
			count++;
			break;
		}
		

		if (isMinusDigit((data + count), lastSymbol))
		{
			count++;
			symbol newDigit = createDigitFromArray(data + count, &count);
			newDigit.value = -newDigit.value;
			equationQueue.push(newDigit);
			lastSymbol = newDigit;
		}
		else if (isDigit(*(data + count)))
		{
			symbol newDigit = createDigitFromArray(data + count, &count);
			equationQueue.push(newDigit);
			lastSymbol = newDigit;
		}
		else if (isVar(*(data + count)))
		{
			char* name = createVarNameFromArray((data + count), &count);
			symbol newVar = createEmptyVariable();
			//
			//check whether the variable is initalized before
			//If it is true - new symbol/var gets past value
			//
			int index = variables->isInitalizedVariable(name);
			if (index != -1)
			{
				newVar.index = getVariableID(name, variables);
				newVar.isNull = variables->at(newVar.index).isNull;
				newVar.value = variables->at(newVar.index).value;
			}
			else
			{
				newVar.index = variables->size();
				var newVariable;
				newVariable.isInitalized = false;
				newVariable.isNull = true;
				newVariable.name = name;
				newVariable.value = 0;
				variables->push_back(newVariable);
			}
			//
			//when after variable is symbol '=', it indicates that this is the result of operation and it isn't included to equation
			//
			if (nextSymbol((data + count), 1) == '=' && nextSymbol((data + count), 2) != '=' && equationQueue.empty() && operatorStack.empty())
			{
				resultVar.push_back(variables->at(newVar.index));
				count += nextSymbolShift((data + count), 1) - 1;
				lastSymbol = createSymbol((data + count));
			}
			else
			{
				equationQueue.push(newVar);
				lastSymbol = newVar;
			}
		}
		else
		{
			symbol newSymbol;
			if (isMinusVar(lastSymbol, data + count))
			{
				newSymbol = createMinusVarSymbol();				
			}
			else
			{
				newSymbol = createSymbol(data + count);
			}
			
						
			if (newSymbol._type == equalS || newSymbol._type == notEqualS || newSymbol._type == lessEqualThenS
				|| newSymbol._type == greatherEqualThenS)
			{
				count++;
			}

			//
			//Special condition for one parameter operators
			//
			if (newSymbol._type == leftBracketS || newSymbol._type == minusVarS || newSymbol._type == negationS)
			{
				operatorStack.push(newSymbol);
			}
			//
			//If interpreter finds right bracket then all operator on stack (until left bracket) are poped and pushed to queue.
			//
			else if (newSymbol._type == rightBracketS)
			{
				while (operatorStack.top()._type != leftBracketS)
				{
					symbol buffsymbol = operatorStack.top();
					operatorStack.pop();
					equationQueue.push(buffsymbol);
				}
				operatorStack.pop();
			}
			else if (!operatorStack.empty() && operatorStack.top().strenght >= newSymbol.strenght)
			{
				int size = operatorStack.size();
				for (int a = 0; a < size; a++)
				{
					symbol buffsymbol = operatorStack.top();
					if (buffsymbol._type == leftBracketS || (buffsymbol.strenght < newSymbol.strenght))
						break;

					operatorStack.pop();
					equationQueue.push(buffsymbol);
				}
				operatorStack.push(newSymbol);
			}
			else
			{
				operatorStack.push(newSymbol);
			}
			lastSymbol = newSymbol;

		}
	}
	*shift = count;
	//
	//Sometimes loop is ending and stack or queue isn't empty (brackets or end of size). Before return of function all equation must be done. 
	//
	if (equationQueue.size() != 0)
	{
		resultValue = resultOfEquation(&equationQueue, &operatorStack, &resultVar, variables, numberOfOperation, maxnumberofoperation);
		operatorStack = stack();
		equationQueue = queue();
		resultVar.clear();		
	}
	return resultValue;
}