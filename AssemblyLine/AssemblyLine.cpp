#include "AssemblyLine.h"
#include "Processor.h"
#include "OrderManager.h"
#include "ItemManager.h"
#include "Item.h"
#include "CustomerOrder.h"
#include "CustomerItem.h"
#include "Utilities.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void AssemblyLine::push_back(Processor&& processor) {
	this->vector::push_back(move(processor));
}

void AssemblyLine::validate(std::ostream& os) {
	bool valid = true;
	for (auto& t : *this) {
		bool invalid = true;
		for (auto& n : *this) {
			if (n.validate(t))
				invalid = false;;
		}
		valid = !invalid;
	}

	if (!valid)
		os << "***Not all Tasks have been validated ***\n";
}

void AssemblyLine::validate(const ItemManager& itemManager, std::ostream& os) {
	for (auto& i : itemManager) {

		auto checkTask = [this](const string str) {
			vector<Processor>::const_iterator it;
			it = find_if(this->begin(), this->end(), [&](const Task& t) {
				return str == t.getName();
			});

			if (it == this->end())
				cout << str << "is unavailable\n";

		};

		checkTask(i.getFiller());
		checkTask(i.getRemover());
	}
}

void AssemblyLine::loadItem(ItemManager& itemManager) {
	for (auto& i : *this)
		for (auto& n : itemManager)
			if (i.getName() == n.getFiller() || i.getName() == n.getRemover())
				i.load(n);

}

void AssemblyLine::loadOrders(OrderManager& orderManager, const std::string& entryProcessor, std::ostream& os) {
	vector<Processor>::iterator it;
	it = find_if(this->begin(), this->end(), [&](const Processor& p) {
		return (p.getName() == entryProcessor) ? true : false;
	});

	if (it != this->end()) {
		while (!orderManager.empty()) {
			it->accept(orderManager.extract());
			orderManager.pop_back();
		}
	}
}

bool AssemblyLine::process(OrderManager& finishing, unsigned int n) {
	OrderManager processingLine;

	for (size_t i = 0; i < n; i++) {
		for (auto& p : *this) {
			if (!p.empty()) {
				p.advance();
				if (p.readyToPass()) {
					
					try {
						srand(time(NULL));
						p.pass(rand() % 101);
					}
					catch (const string& msg) {
						p.ship(processingLine);
						loadOrders(processingLine, msg, cerr);
					}
				}

				if (p.readyToShip()) {
					p.ship(finishing);
					Utilities::getLogFile() << "Task Completed\n";
					if (p.empty())
						return true;
				}
			}
		}
	}

	return false;
}

void AssemblyLine::display(std::ostream& os) const {
	for (auto& p : *this)
		p.Processor::display(os);
}