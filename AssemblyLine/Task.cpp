#include "Task.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;
size_t Task::field_width = 0;

Task::Task(const std::string& str) {
	pNextTask[passed] = nullptr;
	pNextTask[redirect] = nullptr;

	Utilities getToken;
	bool more = false;
	size_t i = 0;

	name = getToken.nextToken(str, i, more);

	if (more)
		slots = getToken.nextToken(str, i, more);
	else
		slots = "1";

	if (more)
		nextTask[passed] = getToken.nextToken(str, i, more);

	if (more)
		nextTask[redirect] = getToken.nextToken(str, i, more);

	if ((getToken.getFieldWidth() > field_width) && !nextTask[0].empty())
		field_width = getToken.getFieldWidth();
}

bool Task::validate(const Task& task) {
	bool valid = false;

	if (!nextTask[passed].empty() || !nextTask[redirect].empty()) {
		if (nextTask[passed] == task.name) {
			pNextTask[passed] = &task;
		}

		if (nextTask[redirect] == task.name) {
			pNextTask[redirect] = &task;
		}
	}


	if (nextTask[redirect].empty()) {
		if (pNextTask[passed])
			valid = true;
	}
	else if (pNextTask[passed] && pNextTask[redirect]) {
		valid = true;
	}

	if (nextTask[passed].empty() && nextTask[redirect].empty())
		valid = true;

	return valid;
}

const std::string& Task::getName() const {
	return name;
}

unsigned int Task::getSlots() const {
	return atoi(slots.c_str());
}

const Task* Task::getNextTask(Quality quantity) const {

	if (!nextTask[quantity].empty() && pNextTask[quantity])
		return pNextTask[quantity];
	else if (nextTask[quantity].empty() && !pNextTask[quantity])
		return nullptr;
	else
		throw "*** Validate [" + nextTask[quantity] + "] @ [" + name + "] ***";
}

void Task::display(std::ostream& os) const {
	os << "Task Name    : [" << setw(field_width + 2) << setfill(' ') << left << name + "]" << "[" << slots << "]\n";

	if (!nextTask[passed].empty()) {
		os << " Continue to : [" << setw(field_width + 2) << setfill(' ') << left << nextTask[passed] + "]";

		if (!pNextTask[passed])
			os << "*** to be validated ***\n";
		else
			os << endl;
	}

	if (!nextTask[redirect].empty()) {
		os << " Redirect to : [" << setw(field_width + 2) << setfill(' ') << left << nextTask[redirect] + "]";

		if (!pNextTask[redirect])
			os << "*** to be validated ***\n";
		else
			os << endl;
	}
}

size_t Task::getFieldWidth() {
	return field_width;
}

bool operator==(const Task& task_a, const Task& task_b) {
	return &task_a == &task_b ? true : false;
}