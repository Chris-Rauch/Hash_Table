//@hashTable.h

#ifndef HASHTABLE
#define HASHTABLE
#include <cstdint>
#include <cstring>
#include <iostream>
#include <bitset> 
#include <cmath>
using namespace std;
const long TABLE_SIZE = 2048;
const int KEY_SIZE = 64;


class HashTable {

    public:
        bitset<KEY_SIZE> hash(const char* message, size_t messageSize); 
        uint64_t mix(bitset<KEY_SIZE> block, bitset<KEY_SIZE> initVector);
    private:
        char* hashTable_[TABLE_SIZE];
        size_t size_;
};


uint64_t HashTable::mix(bitset<KEY_SIZE> block, bitset<KEY_SIZE> initVector) {
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
bitset<KEY_SIZE> HashTable::hash(const char* message, size_t messageSize) {
    //uint64_t initVector = 0xA5A5A5A5;
    //uint64_t block = 0;
    bitset<KEY_SIZE> initVector(0xA5A5A5A5);
    bitset<KEY_SIZE> block(0);
    
    //log(64) / log(2) = 5
    //5 for 64 bits because sizeof includes null
    while(messageSize >= ((log(KEY_SIZE) / log(2)) - 1)) {
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

/*
void HashTable::insert(T hashKey) {
    //calc key-value pair... call hashFunc
    //check for collisions
    //add to vector
}
*/
#endif
