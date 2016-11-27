#include "CustomerItem.h"
#include "Item.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

CustomerItem::CustomerItem(const std::string& str) : filled(false), code(0) {
	if (!str.empty())
		name = str;
}

bool CustomerItem::asksFor(const Item& item) const {
	return name == item.getName();
}

bool CustomerItem::isFilled() const {
	return filled;
}

void CustomerItem::fill(const unsigned int c) {
	code = c;
	filled = true;
}

void CustomerItem::clear() {
	code = 0;
	filled = false;
}

const std::string& CustomerItem::getName() const {
	return name;
}

void CustomerItem::display(std::ostream& os) const {
	if (filled)
		os << " + ";
	else
		os << " - ";

	os << "[" << setw(CODE_WIDTH) << setfill('0') << right << code << "] " << name << "\n";
}