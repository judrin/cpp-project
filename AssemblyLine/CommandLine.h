#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

//the first line - Commander test(argc, &argv);
//the first line(ver2) - Commander test(argc, &argv, "w1 oop345 btp123");

using namespace std;

class Commander{
	vector<string> getter;
	char*** cpy_argv_ref;
	char** argv_ptr;
	int size;
public:
	Commander(int& argc, char*** argv, const char* line = '\0') {
		string input;

		if (line) {
			cout << ">> " << line;
			input = line;
		}
		else {
			cout << ">> ";
			getline(cin, input);
		}

		for (size_t i = 0, j = 0; i < input.size(); i++) {
			j = input.find(' ', i);
			if (j && j != string::npos) {
				getter.push_back(input.substr(i, j - i));
				i = j;
			}
			else if (j == string::npos) {
				getter.push_back(input.substr(i));
				break;
			}
		}

		size = argc = getter.size();

		argv_ptr = *argv;
		*argv = new char*[argc];
		cpy_argv_ref = argv;


		for (int i = 0, size; i < argc; i++) {
			size = getter[i].length();
			(*argv)[i] = new char[size + 1];
			strcpy((*argv)[i], getter[i].c_str());
		}
	}

	~Commander() {
		for (int i = 0; i < size; i++)
			delete (*cpy_argv_ref)[i];
		delete[] * cpy_argv_ref;
		*cpy_argv_ref = argv_ptr;
		argv_ptr = nullptr;
		cpy_argv_ref = nullptr;
	}
};