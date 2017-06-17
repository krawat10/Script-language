#include "Header.h"




symbol resultOfEquation(queue* data, stack* operatorStack, VarVector* resultVar, VarVector* variablesContainer, int* operationCount, int maxOperation)
{
	int count = operatorStack->size();
	for (int i = 0; i < count; i++)
	{
		data->push(operatorStack->top());
		operatorStack->pop();
	}
	stack result;
	while ((data->size() != 0) && (*operationCount <= maxOperation))
	{
		symbol buffer = data->front();
		data->pop();
		if (buffer._type == digitS || buffer._type == variableS)
		{
			if (buffer._type == variableS)
			{
				if (variablesContainer->at(buffer.index).isNull)
				{
					buffer.isNull = true;
					buffer.value = 0;
				}
				else
				{
					buffer.value = variablesContainer->at(buffer.index).value;
					buffer.isNull = false;
				}
			}
			result.push(buffer);
		}
		else if (buffer._type == negationS)
		{
			symbol firstVatiable = result.top();
			result.pop();
			firstVatiable._type = digitS;
			firstVatiable.isNull = !firstVatiable.isNull;
			if (firstVatiable.isNull)
			{
				firstVatiable.value = 0;
			}
			*operationCount = *operationCount + 1;

			result.push(firstVatiable);
		}
		else if (buffer._type == minusVarS)
		{
			symbol firstVatiable = result.top();
			result.pop();
			firstVatiable._type = digitS;
			firstVatiable.value = -firstVatiable.value;
			*operationCount = *operationCount + 1;
			result.push(firstVatiable);
		}
		else
		{
			symbol secondVariable = result.top();
			result.pop();
			symbol firstVatiable = result.top();
			result.pop();
			symbol newDigitSymbol = resultOfMathEquation(firstVatiable, buffer, secondVariable, variablesContainer);
			*operationCount = *operationCount + 1;
			result.push(newDigitSymbol);
		}
	}

	for (int i = resultVar->size() - 1; i >= 0; i--)
	{
		var newValueVar = resultVar->at(i);
		int index = variablesContainer->isInitalizedVariable(newValueVar.name);
	
			if (index != -1)
			{
				variablesContainer->at(index).value = result.top().value;
				variablesContainer->at(index).isNull = result.top().isNull;
				*operationCount = *operationCount + 1;
			}
			if (*operationCount >= maxOperation)
				break;
		
	}
	if (result.size() == 0)
	{
		symbol nullVal;
		nullVal._type = digitS;
		nullVal.value = 0;
		nullVal.isNull = true;
		result.push(nullVal);
	}
	return result.top();

}

void showResult(VarVector* variablesContainer, int numberOfOperation)
{
	if (variablesContainer->size() != 0)
	{
		cout << numberOfOperation << endl;
		for (int i = 0; i < variablesContainer->size(); i++)
		{
			if (variablesContainer->at(i).isInitalized)
			{
				if (variablesContainer->at(i).isNull)
				{
					cout << variablesContainer->at(i).name << " " << "Nul" << endl;
				}
				else
				{
					cout << variablesContainer->at(i).name << " " << variablesContainer->at(i).value << endl;
				}

			}
			variablesContainer->empty();
		}
	}

}
