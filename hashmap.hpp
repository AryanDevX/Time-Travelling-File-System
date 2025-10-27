#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <vector>
#include <string>
#include <iostream>
#include <utility>
using namespace std;

inline int customHash(const int& key, int capacity) {
    return key % capacity;
}

inline int customHash(const string& key, int capacity) {
    const int p = 31;
    const long long m = 1e9 + 7;
    long long hash_val = 0;
    long long p_pow = 1;

    for (char c : key) {
        hash_val = (hash_val + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return (abs(hash_val)) % capacity;
}

inline bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

inline int nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

template <typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    vector<Node*> table;
    int capacity;
    int size;
    bool inRehash;

    int hashFunc(const K &key) {
        return customHash(key, capacity);
    }

    double loadFactor() {
        return (double) size / capacity;
    }

    void rehash() {
        int oldCapacity = capacity;
        vector<Node*> oldTable = table;

        capacity = nextPrime(capacity * 2);
        table.clear();
        table.resize(capacity, nullptr);
        size = 0;

        inRehash = true;

        for (int i = 0; i < oldCapacity; i++) {
            Node* curr = oldTable[i];
            while (curr) {
                insert(curr->key, curr->value);
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        inRehash = false;
    }

public:
    HashMap(int cap = 1000) {
        capacity = nextPrime(cap);
        size = 0;
        table.resize(capacity, nullptr);
        inRehash = false;
    }
    HashMap(const HashMap& other) {
        this->capacity = other.capacity;
        this->size = other.size;
        this->table.resize(this->capacity, nullptr);

        for (int i = 0; i < other.capacity; i++) {
            Node* curr_other = other.table[i]; 
            Node* curr_this = nullptr;

            while (curr_other) {
                Node* newNode = new Node(curr_other->key, curr_other->value);

                if (!curr_this) {
                    this->table[i] = newNode;
                    curr_this = newNode;
                } else {
                    curr_this->next = newNode;
                    curr_this = newNode;
                }

                curr_other = curr_other->next;
            }
        }
    }
    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node* curr = table[i];
            while (curr) {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
        }
    }

    void insert(K key, V value) {
        int idx = hashFunc(key);
        
        Node* curr = table[idx];
        
        while (curr) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = table[idx];
        table[idx] = newNode;
        size++;

        if (!inRehash && loadFactor() > 0.7) {
            rehash();
        }
    }

    bool get(K key, V &value) {
        int idx = hashFunc(key);
        Node* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                value = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool contains(K key) {
        V dummy;
        return get(key, dummy);
    }

    void remove(K key) {
        int idx = hashFunc(key);
        Node* curr = table[idx];
        Node* prev = nullptr;

        while (curr) {
            if (curr->key == key) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    table[idx] = curr->next;
                }
                delete curr;
                size--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    int getSize() { return size; }
    int getCapacity() { return capacity; }
};

#endif