//@main
#include "hashTable.h"

int main() {
    HashTable testHash;
    const char* str = "Test String";

    uint64_t hashVal_i = testHash.hash(str, sizeof(str));
    
    std::bitset<64> hashVal_b(hashVal_i);

    std::cout << hashVal_b << std::endl;
    const char* otherStr = "test String";

    uint64_t intHashVal = testHash.hash(otherStr, sizeof(otherStr));
    
    std::bitset<64> bitHashVal(intHashVal);

    std::cout << bitHashVal << std::endl;

    

    return 1;
}
