#pragma once
#include <iostream>


#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

enum type {
	digitS, plusS, minusS, divideS, multiplicationS, negationS, minusDigitS, moduloS, greatherEqualThenS,
	greatherThenS, lessEqualThenS, lessThenS, equalS, notEqualS, andS, orS, isEqualS, leftBracketS, rightBracketS, fobbidenS, variableS, nullValueS, minusVarS
};

struct symbol
{
	type _type;
	int value;
	int strenght;
	int index;
	bool isNull;
};

struct var
{
	char* name;
	int value;
	bool isNull;
	bool isInitalized;
};

class stack
{
public:
	stack();
	~stack();
	void push(symbol newObject);
	symbol top();
	int size();
	void pop();
	bool empty();
protected:
	void resize(int newSize);
	int currentUse;
	int memory;
	int topPosition;
	symbol* tab;
};

class queue
{
public:
	queue();
	~queue();
	void push(symbol newObject);
	symbol front();
	int size();
	void pop();
	bool empty();
protected:
	void resize(int newSize);
	int currentUse;
	int memory;
	int first;
	int last;
	symbol* tab;
};

class VarVector
{
public:
	VarVector();
	void InitalizeHashTable();
	~VarVector();
	void push_back(var newObject);
	void addToHashTable(int index);
	int size();
	void pop();
	bool empty();	
	void clear();
	var &at(int index);
	int isInitalizedVariable(char* nameToFind);
protected:
	int** hashTable;
	void resize(int newSize);	
	int currentUse;
	int memory;
	int topPosition;
	var* tab;
};

bool isMinusVar(symbol lastSymbol, char* input);
symbol createMinusVarSymbol();
void showResult(VarVector* variablesContainer, int numberOfOperation);
symbol resultOfEquation(queue* data, stack* operatorStack, VarVector* resultVar, VarVector* variablesContainer, int* operationCount, int maxOperation);
int nextSymbolShift(char* tab, int nsymbol);
bool isMinusDigit(char* tab, symbol lastSymbol);
char nextSymbol(char* tab, int nsymbol);
bool isVarLetter(char letter);
symbol createEmptyVariable();
//bool isInitalizedVariable(char* name, VarVector* container);
symbol createSymbol(char* _symbol);
bool isOperator(char* symbol);
bool isOperatorSymbol(symbol symbol);
int getVariableID(char* name, VarVector* container);
bool isDigit(char symbol);
int chatToInt(char symbol);
bool compareStrings(char* string1, char* string2);
char* dotArray(char* table, int size);
int sizeOfArray(char* table, char symbolOfEnd);
int parseToInt(char* table, int size);
symbol createDigitFromArray(char* beginning, int* shift);
int getLinesOfOperations();
char** getVaraibles(int* amountOfVariable);
bool isVar(char string);
symbol createDigitSymbol(int number);
symbol resultOfMathEquation(symbol firstVariable, symbol operation, symbol secondVariable, VarVector* variables);
VarVector* charToVar(char** variables, int amountOfVariable);
char* createVarNameFromArray(char* beginning, int* shift);
int conditionLoop(char* input, int count, int sizeOfArray, int* currentnumberofoperation, int maxnumberofoperation, VarVector* variables);
symbol condition(char* data, int count, int sizeOfArray, int* numberOfOperation, int maxnumberofoperation, VarVector* variables, int* shift);
int loop(char* input, int count, int sizeOfArray, int* currentnumberofoperation, int maxnumberofoperation, VarVector* variables);
