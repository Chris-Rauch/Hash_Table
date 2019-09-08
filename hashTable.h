//@hashTable.h

#ifndef HASHTABLE
#define HASHTABLE
#include <cstdint>
#include <string>
#include <cstring>
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
//const long TABLE_SIZE = 2048;

class HashTable {

    public:
        void addUser(const string &userName, const string &password);
        void display();

    private:
        uint64_t hash(const char* message, size_t messageSize); 
        uint64_t mix(uint64_t block, uint64_t initVector);
    private:
        std::vector<std::vector<string>> database;
};


uint64_t HashTable::mix(uint64_t block, uint64_t initVector) {
    return (initVector * block) ^ ((initVector << 3) + (block >> 2));
}

/* Hash Function
 * 1. Initialize an intenral state or a initialization vector (IV)
 * 2. Consume the message N-bits at a time (aka block size typically 32-bits, 64-bits, 128-bits etc..)
 * 3. Perform a mixing operation with the current block and the internal state
 * 4. Update the internal state with the the result of [3]
 * 5. If there are any remaining bytes in the message proceed to [2]
 * 6. Finalize the internal state and return the hash value
 *
 */
uint64_t HashTable::hash(const char* message, size_t messageSize) {
    uint64_t initVector = 0xA5A5A5A5A5A5A5A5;
    uint64_t block = 0;

    while(messageSize >= 5) /*64-bits*/ {
        memcpy(&block, message, sizeof(uint64_t));
        initVector = mix(block, initVector);

        messageSize -= sizeof(block);
        message += sizeof(block);
    }

    //cleanup remaining bits
    if(messageSize > 0) {
        memcpy(&block, message, messageSize);
        initVector = mix(block, initVector);
    }

    return initVector;
}

void HashTable::addUser(const string &userName, const string &password) {
    uint64_t passHash;

    //hash the password and convert it to a string object
    const char* cstr = password.c_str();
    passHash = hash(cstr, sizeof(cstr));
    string hashString = to_string(passHash);

    //add the username/password-hash pair to the datatbase
    vector<string> user = {userName, hashString};
    database.push_back(user);
}

void HashTable::display() {
    for(int x = 0; x < database.size(); ++x) {
        for(int y = 0; y < database[x].size(); ++y) {
            cout << database[x][y] << " ";
        }
        cout << endl;
    }
}

#endif
