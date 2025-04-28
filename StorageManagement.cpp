#include "StorageManagement.h"

int main() {
    // TODO: Create StorageManager and test functionality
    auto item1_ptr = std::make_shared<StoredItem>("Item1", "Item1 test", "Aisle 2, Section 3");
    auto item2_ptr = std::make_shared<StoredItem>("Item2", "Item2 test", "Aisle 4, Section 5");

    StorageManager manager;
    manager.addItem(item1_ptr);
    std::cout << "Item 1 added" << std::endl;
    manager.addItem(item2_ptr);
    std::cout << "Item 2 added" << std::endl;
    testDuplicateAddition(manager);
    testItemNotFound(manager);

    auto item3_ptr = std::make_shared<StoredItem>("Item3", "Item3 test", "Aisle 1, Section 2");
    std::cout << "Adding item" << std::endl;
    manager.addItem(item3_ptr);
    std::cout << "Listing items..." << std::endl;
    manager.listItemsByDescription();
    std::cout << "Removing item 'Item2'..." << std::endl;
    manager.removeItem("Item2");
    std::cout << "Listing items with removal..." << std::endl;
    manager.listItemsByDescription();
}

void testDuplicateAddition(StorageManager manager) {
    auto item1_ptr = std::make_shared<StoredItem>("Item1", "Item1 test", "Home");
    std::cout << "Testing adding a duplicate item..." << std::endl;
    manager.addItem(item1_ptr);
}

void testItemNotFound(StorageManager manager) {
    std::cout << "Testing searching for an invalid item..." << std::endl;
    manager.findById("Fail");
}