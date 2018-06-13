#include "Interpreter.h"

using namespace std;

void Interpreter::openFile(string fileName) {

	sourceFile.open(fileName);

	if (!sourceFile.is_open()) {
		cerr << "Failed to open source file";
	}

}