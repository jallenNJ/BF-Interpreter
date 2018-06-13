#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Incorrect amount of args recieved" << endl;
		cerr << "Usage: <fileToInterpt>" << endl;
		return -1;
	}

	Interpreter bfInterp(argv[1]);


	//string a_buff;
//	getline(sourceFile, a_buff);
	//cout << a_buff;


	return 0;
}