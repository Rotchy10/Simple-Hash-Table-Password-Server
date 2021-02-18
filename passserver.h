#include <iostream>
#include <utility>
#include <string>
#include "hashtable.h"

using namespace std;

class PassServer {
public:
    PassServer(size_t size = 101);      // Default Constructor
    ~PassServer();                      // Destructor
    bool load(const char * filename);       // Loads given file into the server
    bool addUser(std::pair<string,string> & kv);    // Adds user(key-val pair) to list
    bool addUser(std::pair<string,string> && kv);   // Move addUser Function
    bool removeUser(const string & k);              // Removes given user from list if exist
    bool changePassword(const std::pair<string,string> & p, const string & newpassword);   // Updates password of user
    bool find(const string & user) const;   // Checks if a user exist within the list
    void dump() const;                      // Prints out all users within the server
    size_t size() const;                    // Prints out the number of users within the server
    bool write_to_file(const char * filename) const;    // Writes list of users to a file
    
private:
    HashTable<string,string> tableOfUsers;
    string encrypt(const string & str) const;   // This function encrpyts the given string
};