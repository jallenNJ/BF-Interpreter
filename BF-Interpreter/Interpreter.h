#ifndef INTERPRETER_H
#define INTREPRETER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Interpreter {
public: 
	Interpreter(string fileName) {
		openFile(fileName);
	}



private: 
	void openFile(string);

	ifstream sourceFile;
};

#endif // !INTERPRETER_H

