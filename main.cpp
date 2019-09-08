//@main
#include "hashTable.h"
//using namespace std;
/* Description:
 * Basic program for saving usernames and passwords using hashing
 */

void createUser(HashTable &hashTable);

int main() {
    HashTable hashTable;
    bool keepLooping = true;
    
    while(keepLooping) {
        cout << "==== MENU ====\n";
        cout << "1) Create Username Password Pair\n";
        cout << "2) Exit\n";

        short input;
        cin >> input;
        switch (input) {
            case 1:
                createUser(hashTable);
                break;
                
            case 2:
                cout << "Exiting Program...\n";
                keepLooping = false;
                break;
                
            default:
                cout << "invalid Option\n";
                break;
        }
    }
    hashTable.display();

    return 1;
}

void createUser(HashTable &hashTable) {
    string userName;
    string password;
    
    cout << "\nEnter New Username: ";
    cin >> userName;
    cout << "Enter New Password: ";
    cin >> password;

    hashTable.addUser(userName, password);
}
