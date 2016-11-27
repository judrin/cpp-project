#include "OrderManager.h"
#include "CustomerOrder.h"
#include "ItemManager.h"
#include "Item.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

CustomerOrder&& OrderManager::extract() {
	return move(this->back());
}

void OrderManager::validate(const ItemManager& im, std::ostream& os) {
	vector<Item>::const_iterator it;
	for (auto& t : *this) {
		for (size_t i = 0; i < t.noOrders(); i++) {
			it = find_if(im.begin(), im.end(), [&](const Item& item) {
				return t[i] == item.getName();
			});

			if (it == im.end())
				cout << t[i] << " is unavailable\n";

		}
	}
}

void OrderManager::display(std::ostream& os) const {
	for (auto& t : *this)
		t.CustomerOrder::display(os);
}