#include "Interpreter.h"

using namespace std;




// Entry point to the Interpreter, this function reads the entire file
//	and processes each character by itself.
void Interpreter::interpret() {

	vector<char> loopOps; //Stores all operations in the current loop
	while (!sourceFile.eof()) {
		//Read in the current line
		string line = "";
		getline(sourceFile, line);

		if (!inLoop) { //Reset loop operations if not in a loop
			loopOps.clear();
		}

		//Process every char on the line
		for (unsigned int i = 0; i < line.length(); i++) {
			bool result = processOperator(line[i] );
			if (!result) { //If not valid, skip past it
				continue;
			}
			if (inLoop || doLoop) { //If in a loop record the operation
				loopOps.push_back(line[i]);
			}

			while (doLoop) { //If the loop is proc'd process all operations

				for (unsigned int j = 0; j < loopOps.size(); j++) {
					processOperator(loopOps[j]);
				}
			}
			if (!inLoop) { //If loop ended, clear opps
				loopOps.clear();
			}
			
		}


	}

	//Memory dump
	debugMemOutput();

}


//This function handles implementing finding out if a char is an operator, and if it is
// implementing its correct function

//RETURNS true if input was a valid operator
//		false if the operator was not valid
bool Interpreter::processOperator(char op) {
	bool validOperator = true;
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
		cout << *pgmPtr;
		break;
	case ',':
		//Get first letter of input
		char input;
		cin.get(input);
		//Ingore and clear anything else user inputed
		cin.ignore(INT_MAX, '\n');
		cin.clear();
		fflush(stdin);

		//Store recieved byte
		*pgmPtr = input;
		break;
	case '[':
		inLoop = true;

		break;
	case']':
		if (inLoop = false) {
			cerr << "Syntax error: Loop ended without being started";
			cerr << "\n Will ignore character" << endl;
			break;
		}

		if (*pgmPtr == 0) { //Loop ends
			inLoop = false;
			doLoop = false;
			
			
		}
		else { //Run all loop operations
			doLoop = true;
		}


		break;
	default:// Invalid symbol is ignored
		validOperator = false;
		break;

	}

	//Return if valid operator was found
	return validOperator;

}


//This function will increase the memory that is reserved by the interpreter.
// If expansion <= 0, function will return without changing size of memory
void Interpreter::expandMemory(int expansion) {
	if (expansion < 1) {
		cerr << "Invalid pass to expandMemory, value was " << expansion;
		cerr << "\n Function will abort" << endl;
		return;
	}
	//Create a new array of the correct size
	char* expandedArr = new char[memSize + expansion];

	//Copy over the values
	for (unsigned int i = 0; i < memSize; i++) {
		expandedArr[i] = pgmMem[i];
	}
	//Zero out the rest of the array
	for (unsigned int i = memSize; i < memSize + expansion; i++) {
		expandedArr[i] = 0;
	}

	//Find the offset between the pointers
	int offset = pgmPtr - pgmMem;

	//Delete the old array and move pointer to the new array
	delete[] pgmMem;
	pgmMem = expandedArr;
	//Move the pointer to the correct offset
	pgmPtr = pgmMem + offset;
	//Update size of memory
	memSize += expansion;
	expandedArr = NULL;

}

//This function opens the file, and 
void Interpreter::openFile(string fileName) {

	sourceFile.open(fileName);

	if (!sourceFile.is_open()) {
		cerr << "Failed to open source file";
		cerr << "Program will abort until proper error handling" << endl;
		exit(-3);
	}

}