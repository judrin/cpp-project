#include "Processor.h"
#include "Task.h"
#include "Item.h"
#include "OrderManager.h" 
#include "Utilities.h"
using namespace std;

Processor::Processor(const std::string& record, std::function<Task::Quality(int)> inspector_) 
	: item_(nullptr), inspector(move(inspector_)), is_a_filler(true), Task(record) {
	num_end_slots = getSlots();
}

void Processor::load(Item& item) {
	item_ = &item;
	is_a_filler = (this->getName() == item_->getFiller()) ? true : false;
}

void Processor::accept(CustomerOrder&& order) {
	waiting.push_back(order);
}

void Processor::pass(int n) {
	auto checkQuality = getNextTask(passed) && getNextTask(redirect) ? inspector(n) : passed;

	string taskName = getNextTask(checkQuality)->getName();

	if (checkQuality == passed)
		Utilities::getLogFile() << "Passed to ";
	else
		Utilities::getLogFile() << "Redirect to ";
	Utilities::getLogFile() <<"[" << taskName << "]\n";
	throw taskName;
}

void Processor::advance() {
		if (!process.empty() && num_end_slots) {
			num_end_slots--;
			
			is_a_filler ? process.back().fill(*item_) : process.back().remove(*item_);
		}

		if (!num_end_slots) {
			complete.push_back(process.front());
			process.pop_front();

			process.empty() ? num_end_slots = getSlots() : num_end_slots++;
		}

		if (!waiting.empty()) {
			process.push_back(waiting.front());
			waiting.pop_front();
		}
}

bool Processor::empty() const {
	return (waiting.empty() && process.empty() && complete.empty()) ? true : false;
}

bool Processor::readyToShip() const {
	return !complete.empty() && !getNextTask(passed);
}

bool Processor::readyToPass() const {
	return !complete.empty() && getNextTask(passed);
}

void Processor::ship(OrderManager& finished) {
	if (!complete.empty()) {
		finished.push_back(complete.front());
		complete.pop_front();
	}
}

void Processor::display(std::ostream& os) const {
	this->Task::display(os);
	os << " Item to add : ";

	if (item_ && is_a_filler) {
		item_->display(os);
	}
	else {
		os << "---";
	}
	os << endl;
}