#ifndef INTERPRETER_H
#define INTREPRETER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
//#include <cmath>

using namespace std;

class Interpreter {
public: 

	const int DEFAULT_SIZE = 20;	 //Size of the starting memory
	const int EXPANSION_STEP = 10;	//SIze the memory is increased when bounds are exceeded

	//Constructor opens the file and intialized the memory
	Interpreter(string fileName) {

		openFile(fileName);
		memSize = DEFAULT_SIZE;
		pgmMem = new char[memSize];

		pgmPtr = pgmMem;
		for (unsigned int i = 0; i < memSize; i++) {
			pgmMem[i] = 0;
		}

		pgmCounter = 0;

		loadInInstructions();
	}

	~Interpreter() {
		delete[]pgmMem;
		pgmMem = NULL;
		pgmPtr = NULL;
		memSize = 0;
		sourceFile.close();
	}

	void interpret();

private: 
	void openFile(string);

	void loadInInstructions();

	void expandMemory(int);
	
	void processOperator(char);


	//Debug function to output the entire contents of memory in a nicer view than the debugger
	void debugMemOutput() {

		cout << "\n";
		//DEBUG
		for (unsigned int i = 0; i < memSize; i++) {
			cout << i<<": " << (int)pgmMem[i] << "\t";
			if (i % 5 == 0 && i != 0) {
				cout << endl;
			}
		}
	}


	ifstream sourceFile; //The file containing the instructions
	char* pgmMem;	//The contents of the program memory
	char* pgmPtr;	//The pointer that the instructions modify
	unsigned int memSize;	//The size of the program's memory
	unsigned int pgmCounter; //The instruction being executed


	vector<char> instructions; //All the instruction the program needs to run
	stack<int> loopReturnAddress; //The location of the start of loops
	map<int, int> loopBounds; //The map which associates the loops to their start and end

};

#endif // !INTERPRETER_H

