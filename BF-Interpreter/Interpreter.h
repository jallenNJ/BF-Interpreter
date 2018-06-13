#ifndef INTERPRETER_H
#define INTREPRETER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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

		inLoop = false;
		doLoop = false;

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

	void expandMemory(int);
	
	bool processOperator(char);


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


	ifstream sourceFile;
	char* pgmMem;
	char* pgmPtr;
	unsigned int memSize;
	bool inLoop;
	bool doLoop;

};

#endif // !INTERPRETER_H

