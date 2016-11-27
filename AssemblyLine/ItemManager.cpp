#include "ItemManager.h"
#include "Item.h"
#include <iostream>

using namespace std;

void ItemManager::display(std::ostream& os, bool full) const {
	for (auto& t : *this)
		t.Item::display(os, full);
}