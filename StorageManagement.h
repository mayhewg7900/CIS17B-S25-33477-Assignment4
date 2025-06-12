#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>

class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};

class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public:
    StoredItem(std::string id, std::string desc, std::string loc)
        : id(id), description(desc), location(loc) {}

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
};

class StorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;

public:
    void addItem(const std::shared_ptr<StoredItem>& item) {
        // TODO: Add item to both maps, throw if ID already exists
        try {
            for (const auto& map_item : itemById) {
                if (map_item.first == item->getId()) {
                    throw DuplicateItemException("Error, duplicate items");
                }
            }
            itemById.insert({ item->getId(), item });
            itemByDescription.insert({ item->getDescription(), item });
        }
        catch (DuplicateItemException &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::shared_ptr<StoredItem> findById(const std::string& id) const {
        // TODO: Return item if found or throw ItemNotFoundException
        auto foundId = itemById.find(id);
        try {
            if (foundId != itemById.end()) {
                return foundId->second;
            }
            else {
                throw ItemNotFoundException("Item not found, cannot be removed");
            }
        }
        catch(ItemNotFoundException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            return nullptr;
        }       
    }

    void removeItem(const std::string& id) {
        // TODO: Remove from both maps, throw if not found
        auto foundId = itemById.find(id);
        try {
            if (foundId == itemById.end()) {
                throw ItemNotFoundException("Item not found, cannot be removed");
            }
            std::shared_ptr<StoredItem> item = foundId->second;
            itemById.erase(foundId);
            for (auto& map_item : itemByDescription) {
                if (item == map_item.second) {
                    itemByDescription.erase(map_item.first);
                    break;
                }
            }
        }
        catch (ItemNotFoundException& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    void listItemsByDescription() const {
        // TODO: Iterate over itemByDescription and print info
        std::cout << "List of items in description order:" << std::endl;
        for (const auto& map_item : itemByDescription) {
            std::cout << map_item.first << " at " << map_item.second->getLocation() << std::endl;
        }
    }
};

void testDuplicateAddition(StorageManager manager);
void testItemNotFound(StorageManager manager);

