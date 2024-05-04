#include "cache.h"
#include <sstream>

Cache::Cache() : head(nullptr), tail(nullptr), capacity(CACHE_SIZE) {}

Cache::~Cache() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
unsigned int Cache::hashFunction(const std::string& key) {
    unsigned int hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % tableSize;
}

void Cache::remove(Node* node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    delete node;
}

void Cache::insertFront(Node* node) {
    node->prev = nullptr;
    node->next = head;

    if (head)
        head->prev = node;

    head = node;

    if (!tail)
        tail = head;
}

bool Cache::isFull() {
    return cacheSize() >= capacity;
}

void Cache::add(std::string key, int value) {
    if (isFull()) {
        remove(tail);
    }

    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;

    insertFront(newNode);
}

void Cache::add(std::string key, double value) {
    if (isFull()) {
        remove(tail);
    }

    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;

    insertFront(newNode);
}

bool Cache::get(std::string key, int& value) {
    Node* current = head;
    while (current) {
        if (current->key == key) {
            value = current->value;
            // Move the accessed node to the front
            if (current != head) {
                remove(current);
                insertFront(current);
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

bool Cache::get(std::string key, double& value) {
    Node* current = head;
    while (current) {
        if (current->key == key) {
            value = current->value;
            // Move the accessed node to the front
            if (current != head) {
                remove(current);
                insertFront(current);
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

std::string Cache::toString() {
    std::stringstream ss;
    Node* current = head;
    while (current) {
        ss << "[" << current->key << ": " << current->value << "]";
        if (current->next)
            ss << " -> ";
        current = current->next;
    }
    return ss.str();
}

int Cache::cacheSize() {
    int size = 0;
    Node* current = head;
    while (current) {
        size++;
        current = current->next;
    }
    return size;
}

Cache::Bucket* Cache::createBucket(const std::string& key, int value) {
    Bucket* newBucket = new Bucket;
    newBucket->key = key;
    newBucket->value = value;
    newBucket->next = nullptr;
    return newBucket;
}

Cache::Bucket* Cache::findBucket(const std::string& key) {
    unsigned int index = hashFunction(key);
    Bucket* current = hashTable[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Cache::addToHashTable(const std::string& key, int value) {
    unsigned int index = hashFunction(key);
    Bucket* newBucket = createBucket(key, value);
    newBucket->next = hashTable[index];
    hashTable[index] = newBucket;
}
