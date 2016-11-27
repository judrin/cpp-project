#include "TaskManager.h"
#include "Task.h"
#include "ItemManager.h"
#include "Item.h"
#include <iostream>
#include <algorithm>

using namespace std;
void TaskManager::validate(std::ostream& os) {
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

void TaskManager::validate(const ItemManager& item, std::ostream& os) {
	
	for (auto& i : item) {

		auto checkTask = [this](const string str) {
			vector<Task>::const_iterator it;
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

void TaskManager::display(std::ostream& os) const {

	for (auto& t : *this)
		t.Task::display(os);

}