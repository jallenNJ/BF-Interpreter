#include "Interpreter.h"

using namespace std;




// Entry point to the Interpreter, this function reads the entire file
//	and processes each character by itself.
void Interpreter::interpret() {

	while (!sourceFile.eof()) {
		//Read in the current line
		string line = "";
		getline(sourceFile, line);

		//Process every char on the line
		for (unsigned int i = 0; i < line.length(); i++) {
			processOperator(line[i]);
	}

		debugMemOutput();

	}


}


//This function handles implementing finding out if a char is an operator, and if it is
// implementing its correct function
void Interpreter::processOperator(char op) {

	switch (op) {
	case '<':
		if (pgmPtr <= pgmMem) { //If pointer moved further left than the start of the memory
			cerr << "Pointer moved too far left, program will close until proper error handling";
			exit(-2);
		}
		
		pgmPtr--;
		break;
	case '>':
		if (pgmPtr >= (pgmMem + memSize)) { //If pointer moved further right than the current memory expansion
			expandMemory(EXPANSION_STEP);
		}
		pgmPtr++;
		break;
	case '+':
		//Increment value at location
		(*pgmPtr)++;
		break;
	case '-': 
		//Decrement value at location
		(*pgmPtr)--;
		break;
	case '.':
		break;
	case ',':
		break;
	case '[':
		break;
	case']':
		break;
	default:// Invalid symbol is ignored
		break;


	}


}


void Interpreter::expandMemory(int expansion) {
	if (expansion < 1) {
		cerr << "Invalid pass to expandMemory, value was " << expansion;
		cerr << "\n Function will abort" << endl;
		return;
	}
	char* expandedArr = new char[memSize + expansion];

	for (unsigned int i = 0; i < memSize; i++) {
		expandedArr[i] = pgmMem[i];
	}
	for (unsigned int i = memSize; i < memSize + expansion; i++) {
		expandedArr[i] = 0;
	}

	int offset = pgmPtr - pgmMem;

	delete[] pgmMem;
	pgmMem = expandedArr;
	pgmPtr = pgmMem + offset;
	memSize += expansion;
	expandedArr = NULL;

}
void Interpreter::openFile(string fileName) {

	sourceFile.open(fileName);

	if (!sourceFile.is_open()) {
		cerr << "Failed to open source file";
	}

}