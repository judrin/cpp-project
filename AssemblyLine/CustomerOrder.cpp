#include "CustomerOrder.h"
#include "Utilities.h"
#include "CustomerItem.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

size_t CustomerOrder::field_width = 0;
using namespace std;

CustomerOrder::CustomerOrder(const std::string& str) : nOrders(0), order(nullptr) {
	size_t position = 0;
	bool more = false;
	Utilities getToken;
	vector<string> item;

	name = getToken.nextToken(str, position, more);
	if (more) product = getToken.nextToken(str, position, more);
	while (more) {
		string temp  = getToken.nextToken(str, position, more);
		if (!temp.empty()) {
			item.push_back(temp);
			nOrders++;
		}
	}

	if (nOrders > 0) {
		order = new CustomerItem[nOrders]();
		for (size_t i = 0; i < nOrders; i++)
			order[i] = item[i];
	}

	if (getToken.getFieldWidth() > field_width)
		field_width = getToken.getFieldWidth();
}

CustomerOrder::CustomerOrder(const CustomerOrder& rhs) {
	if (rhs.order && rhs.nOrders) {
		name = rhs.name;
		product = rhs.product;
		nOrders = rhs.nOrders;
		order = new CustomerItem[nOrders];
		for (size_t i = 0; i < nOrders; i++)
			order[i] = rhs.order[i];
	}
}

CustomerOrder::CustomerOrder(CustomerOrder&& rhs) {
	name = rhs.name;
	product = rhs.product;
	nOrders = rhs.nOrders;
	order = rhs.order;
	rhs.name.clear();
	rhs.product.clear();
	rhs.nOrders = 0;
	rhs.order = nullptr;
}

CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& rhs) {
	if (this != &rhs) {
		delete[] order;
		order = nullptr;
		name = rhs.name;
		product = rhs.product;
		nOrders = rhs.nOrders;
		order = rhs.order;
		rhs.name.clear();
		rhs.product.clear();
		rhs.nOrders = 0;
		rhs.order = nullptr;
	}

	return move(*this);
}
CustomerOrder::~CustomerOrder() {
	delete[] order;
}

unsigned int CustomerOrder::noOrders() const {
	return nOrders;
}

const std::string& CustomerOrder::operator[](unsigned int index) const {
	return order[index].getName();
}

void CustomerOrder::fill(Item& item) {
	for (size_t i = 0; i < nOrders; i++)
		if (order[i].getName() == item.getName())
			if (!order[i].isFilled()) {
				order[i].fill(item++);
			}
}

void CustomerOrder::remove(Item& item) {
	for (size_t i = 0; i < nOrders; i++)
		if (order[i].getName() == item.getName()) {
			order[i].clear();
		}
}

bool CustomerOrder::empty() const {
	return !nOrders;
}

void CustomerOrder::display(std::ostream& os) const {
	os << setw(field_width + 2) << setfill(' ') << left << name
		<< ": " << setw(field_width + 2) << setfill(' ') << left << product << "\n";

	for (size_t i = 0; i < nOrders; i++)
		order[i].display(os);
}