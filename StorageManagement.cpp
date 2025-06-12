#include "StorageManagement.h"

int main() {
    // Creating items for testing
    auto item1_ptr = std::make_shared<StoredItem>("Item1", "Item1 test", "Aisle 2, Section 3");
    auto item2_ptr = std::make_shared<StoredItem>("Item2", "Item2 test", "Aisle 4, Section 5");

    // StorageManager object instance creation
    StorageManager manager;

    // Adding the test items to the StorageManager
    manager.addItem(item1_ptr);
    std::cout << "Item 1 added" << std::endl;
    manager.addItem(item2_ptr);
    std::cout << "Item 2 added" << std::endl;

    // Testing adding duplicate items
    testDuplicateAddition(manager);

    // Testing item not being found
    testItemNotFound(manager);

    // Creating a third test item and adding
    auto item3_ptr = std::make_shared<StoredItem>("Item3", "Item3 test", "Aisle 1, Section 2");
    std::cout << "Adding item" << std::endl;
    manager.addItem(item3_ptr);

    // Listing all current items
    std::cout << "Listing items..." << std::endl;
    manager.listItemsByDescription();

    // Removing item
    std::cout << "Removing item 'Item2'..." << std::endl;
    manager.removeItem("Item2");

    // Listing items following removal, to display updated list
    std::cout << "Listing items with removal..." << std::endl;
    manager.listItemsByDescription();
}


// Test duplicate addition definition, creates an item with the same name as one previously created in main
void testDuplicateAddition(StorageManager manager) {
    auto item1_ptr = std::make_shared<StoredItem>("Item1", "Item1 test", "Home");
    std::cout << "Testing adding a duplicate item..." << std::endl;
    manager.addItem(item1_ptr);
}


// Test item not found, with an id that doesn't exist in the current implementation
void testItemNotFound(StorageManager manager) {
    std::cout << "Testing searching for an invalid item..." << std::endl;
    manager.findById("Fail");
}