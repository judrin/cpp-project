#include "Utilities.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char Utilities:: delimiter = '\0'; 
std::ofstream Utilities::logFile;

Utilities::Utilities() {
	field_width = 1;
}

void Utilities::setFieldWidth(size_t fw) {
	field_width = fw;
}

size_t Utilities::getFieldWidth() const {
	return field_width;
}

const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more) {

	string token;
	bool start_pos = !next_pos ? true : false;

	for (more = false; next_pos < str.size() && str[next_pos] != delimiter; next_pos++) {
		token += str[next_pos];
	}

	if (str[next_pos] == delimiter) {
		more = true;
	}
	
	next_pos++;

	size_t p = token.find_first_not_of(" \t");
	if (p == string::npos)
		token.clear();
	else
		token.erase(0, p);
	p = token.find_last_not_of(" \t");
	if (p != string::npos)
		token.erase(p + 1);

	if (token.empty() && more)
		throw str + "<-- *** no token found before the delimiter ***";

	if (start_pos && token.size() > field_width)
		field_width = token.size();

	return token;
}

void Utilities::setDelimiter(const char _delimeter) {
	delimiter = _delimeter;
}

void Utilities::setLogFile(const char* logfile) {
	logFile.open(logfile, ios::trunc);
}

std::ofstream& Utilities::getLogFile() {
	return logFile;
}