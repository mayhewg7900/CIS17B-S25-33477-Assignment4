#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>

// Duplicate item exception class, using the std::runtime_error base, displays a runtime_error string
class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};


// Item not found exception class
class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};


// StoredItem class definition, contains ID, description, and location private strings
class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;


// Public methods for construction, as well as getters for private members
public:
    StoredItem(std::string id, std::string desc, std::string loc)
        : id(id), description(desc), location(loc) {}

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
};


// StorageManager class definition, with a private unordered_map and map reference, for demonstration and practical application purposes
class StorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;


// Public methods
public:
    // Adding an item to both the unordered_map and maps
    void addItem(const std::shared_ptr<StoredItem>& item) {
        // Trying to add item...
        try {
            for (const auto& map_item : itemById) {
                // If ID already exists... throw an exception error
                if (map_item.first == item->getId()) {
                    throw DuplicateItemException("Error, duplicate items");
                }
            }
            // If ID does not exist, insert them into both private map type members
            itemById.insert({ item->getId(), item });
            itemByDescription.insert({ item->getDescription(), item });
        }
        // Catching the error, using the DuplicateItemException class
        catch (DuplicateItemException &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    // Trying to find an item by ID...
    std::shared_ptr<StoredItem> findById(const std::string& id) const {
        auto foundId = itemById.find(id);
        try {
            // If item is found, return its description
            if (foundId != itemById.end()) {
                return foundId->second;
            }
            // If item is not found, throw an error
            else {
                throw ItemNotFoundException("Item not found, cannot be removed");
            }
        }
        // Error caught, displaying error message and returning a nullptr
        catch(ItemNotFoundException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            return nullptr;
        }       
    }
    // Trying to remove item...
    void removeItem(const std::string& id) {
        auto foundId = itemById.find(id);
        try {
            // If the item to remove is not found, throw an error
            if (foundId == itemById.end()) {
                throw ItemNotFoundException("Item not found, cannot be removed");
            }
            // Removing the found ID
            std::shared_ptr<StoredItem> item = foundId->second;
            itemById.erase(foundId);
            // Searching for the found ID in the second map
            for (auto& map_item : itemByDescription) {
                // If item found... remove it and break out of the loop
                if (item == map_item.second) {
                    itemByDescription.erase(map_item.first);
                    break;
                }
            }
        }
        // Error caught, displaying ItemNotFoundException message
        catch (ItemNotFoundException& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    // listItemsByDescription definition, lists all the items in order using the sorted map type
    void listItemsByDescription() const {
        std::cout << "List of items in description order:" << std::endl;
        // Looping through the map items, displaying its description and location
        for (const auto& map_item : itemByDescription) {
            std::cout << map_item.first << " at " << map_item.second->getLocation() << std::endl;
        }
    }
};

// Function prototypes for testDuplicateAddition and testItemNotFound, implemented in the .cpp file
void testDuplicateAddition(StorageManager manager);
void testItemNotFound(StorageManager manager);

