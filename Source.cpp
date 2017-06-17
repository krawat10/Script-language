#include "Header.h"
#include <cstdio>



int main()
{
	int amountOfVariable;
	int numberOfOperation = 0;
	int maxNumberOfOperation = getLinesOfOperations();
	char** variables = getVaraibles(&amountOfVariable);
	char* fullArray = (char*)malloc(sizeof(char) * 1);
	int initalizedVariable = amountOfVariable;
	cin.get();

	//buffer array (get data form each line)
	char* kola = (char*)malloc(sizeof(char) * 1000);

	int fullSize = 0;
	int fullLine = 0;
	int h = 1 / 2;
	while (!cin.eof())
	{
		cin.getline(kola, 1000);
		while (kola[fullLine++] != '\0');
		kola[fullLine - 1] = ' ';
		kola[fullLine] = '\0';
		fullArray = (char*)realloc(fullArray, fullSize + fullLine);

		for (int i = 0; i < fullLine; i++)
		{
			fullArray[fullSize + i] = kola[i];
		}

		fullSize += fullLine;
		fullLine = 0;
	}
	//secured against memory leak
	fullArray = (char*)realloc(fullArray, fullSize + 2);
	fullArray[fullSize] = '\0';

	//free buffer line
	free(kola);

	//initalize first variable using second line of code
	VarVector* variablesContainer = charToVar(variables, amountOfVariable);
	int i = 0;
	int shift;

	//main loop
	condition(fullArray, i, fullSize, &numberOfOperation, maxNumberOfOperation, variablesContainer, &shift);
	
	//secured against additional counting (leaving from loops)
	if (numberOfOperation > maxNumberOfOperation)
	{
		numberOfOperation = maxNumberOfOperation;
	}	

	//show result on terminal
	showResult(variablesContainer, numberOfOperation);

	//free memory
	free(variables);
	delete variablesContainer;
	free(fullArray);
	}




