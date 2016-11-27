#include "Item.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <iomanip>

size_t Item::field_width = 0;
using namespace std;

Item::Item(const std::string& str) : code(1), description("no detailed description") {
	size_t position = 0;
	bool more = false;
	Utilities getToken;

	name = getToken.nextToken(str, position, more);
	if (more) filler = getToken.nextToken(str, position, more);
	if (more) remover = getToken.nextToken(str, position, more);
	if (more) code = atoi(getToken.nextToken(str, position, more).c_str());
	if (more) description = getToken.nextToken(str, position, more);

	if (getToken.getFieldWidth() > field_width)
		field_width = getToken.getFieldWidth();
}

bool Item::empty() const {
	return name.empty();
}

int Item::operator++(int) {
	int oldCode = getCode();
	++code;
	return oldCode;
}

unsigned int Item::getCode() const {
	return code;
}

const std::string& Item::getName() const {
	return name;
}

const std::string& Item::getFiller() const {
	return filler;
}

const std::string& Item::getRemover() const {
	return remover;
}

void Item::display(std::ostream& os, bool full) const {
	os << setw(field_width + 2) << setfill(' ') << left << name
		<< "[" << setw(CODE_WIDTH) << setfill('0') << right << code << "]";
	
	if (full) {
		os << " From " << setw(field_width + 2) << setfill(' ') << left << filler
			<< "To " << setw(field_width + 2) << setfill(' ') << left << remover << "\n"
			<< setw(field_width + CODE_WIDTH + 5) << right << ": ";
		if (description.empty())
			os << "no detailed description";
		else
			os << description;
	}

	os << "\n";
	
}