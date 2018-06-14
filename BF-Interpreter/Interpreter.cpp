#include "Interpreter.h"

using namespace std;




// Entry point to the Interpreter, this function reads the entire file
//	and processes each character by itself.
void Interpreter::interpret() {

	for (pgmCounter = 0; pgmCounter < instructions.size(); pgmCounter++) {
		processOperator(instructions[pgmCounter]);
	}

	//Memory dump
	debugMemOutput();

}


//This function handles implementing finding out if a char is an operator, and if it is
// implementing its correct function

void Interpreter::processOperator(char op) {
	switch (op) {
	case '<':
		if (pgmPtr <= pgmMem) { //If pointer moved further left than the start of the memory
			expandMemory(-EXPANSION_STEP);
		}
		
		pgmPtr--;
		break;
	case '>':
		if (pgmPtr >= (pgmMem + memSize) - 1) { //If pointer moved further right than the current memory expansion
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

		if (*pgmPtr == 0) {
			map<int, int>::iterator st;
			st = loopBounds.find(pgmCounter);
			if (st == loopBounds.end()) {
				cerr << "End of current loop not found" << endl;
				exit(-6);
			}
			pgmCounter = st->second;
			//Logic for skipping loop
			break;
		}
		loopReturnAddress.push(pgmCounter);

		break;
	case']':
		if (loopReturnAddress.size() == 0) {
			cerr << "Loop return address is zero when ']' encounter" << endl;
			exit(-8);
		}

		if (*pgmPtr == 0) { //Loop ends
			loopReturnAddress.pop();
		}
		else { 
			//START LOOP
			pgmCounter = loopReturnAddress.top();

		}
		break;
	default:// Invalid symbol is ignored
		cerr << "Invalid symbol in process operator, will be ignored" << endl;
		break;

	}



}


//This function will increase the memory that is reserved by the interpreter.
// If expansion < 0, function will add member before the old "Zero" point
void Interpreter::expandMemory(int expansion) {
	if (expansion == 0) {
		return;
	}
	int offset = 0;
	if (expansion < 0) {
		expansion = abs(expansion);
		offset = expansion;
		
	}

	//Create a new array of the correct size
	char* expandedArr = new char[memSize + expansion];

	for (int i = 0; i < offset; i++) { //If negative expansion, zero out values
		expandedArr[i] = 0;
	}
	//Copy over the values
	for (unsigned int i = offset; i < memSize+offset ; i++) { //Copy over  the values to new array
		expandedArr[i] = pgmMem[i-offset];
	}
	//Zero out the rest of the array (postive expansion)
	for (unsigned int i = memSize + offset; i < memSize + expansion ; i++) {
		expandedArr[i] = 0;
	}

	//Find the offset between the pointers
	int ptrOffset = pgmPtr - pgmMem;
	ptrOffset += offset;
	//Delete the old array and move pointer to the new array
	delete[] pgmMem;
	pgmMem = expandedArr;
	//Move the pointer to the correct offset
	pgmPtr = pgmMem + ptrOffset;
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

//This function acts as ====PASS I==== for the interpreter
//It takes the input, and loads it in as the instructions vector, it also
// finds the bounds of loops, and pushes them into appropriate data structures.
void Interpreter::loadInInstructions() {

	stack<int> loopOpenLoc; //Stack to store when loops began

	while (!sourceFile.eof()) { //Loop until EOF
		//Get the current line of the file
		string line = "";
		getline(sourceFile, line);

		for (unsigned int i = 0; i < line.length(); i++) {
			bool addToInstructions = true;
			switch (line[i]) {
				//If valid non loop symbol, just add to list
				case '<':
				case '>':
				case '+':
				case '-':
				case ',':
				case '.':
					//pass;
					break;
				case '[': //Start of loop, add it to the local stack
					loopOpenLoc.push(instructions.size());
					break;
				case ']': //End of a loop found, add its assoicated opening to the map
					
					if (loopOpenLoc.size() == 0) { //If no opening loop, syntax error in file
						cerr << "Syntax error, loop closed without being opened, ignoring char" << endl;
						addToInstructions = false;
						break;
					}
					//Add the starting location as key, and the location of the end bracket as the value
					loopBounds[loopOpenLoc.top()] = instructions.size();
					loopOpenLoc.pop(); //Remove from the map

					break;
				default: //Invalid character in file, discard
					addToInstructions = false;
					break;
			}

			if (addToInstructions) { //If valid symbol, add to file
				instructions.push_back(line[i]);
			}
		}
	}

	if (loopOpenLoc.size() != 0) { //If any remain in stack, syntax error as loop wasn't closed
		cerr << "Syntanx Error: Loop opened and not closed" << endl;
		exit(-4);
	}

}