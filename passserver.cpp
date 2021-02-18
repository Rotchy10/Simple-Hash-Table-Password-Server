#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <crypt.h>
#include <utility>
#include "passserver.h"

using namespace std;

PassServer::PassServer(size_t size) : tableOfUsers(size){
}       // Constructor

PassServer::~PassServer(){  // Destructor
    tableOfUsers.clear();
}

bool PassServer::load(const char * filename){
    return tableOfUsers.load(filename); // load file
}

bool PassServer::addUser(std::pair<string,string> & kv){
    std::pair<string,string> userInfo = kv;    
    userInfo.second = encrypt(userInfo.second); // Encrypting password before
    return tableOfUsers.insert(userInfo);       // inserting to hash table
}

bool PassServer::addUser(std::pair<string,string> && kv){
    return addUser(std::move(kv));
}

bool PassServer::removeUser(const string & K){  // removes specified user from list, if it exist
    return tableOfUsers.remove(K);
}

bool PassServer::changePassword(const std::pair<string,string> & p, const string & newpassword){

    std::pair<string,string> userInfo = p;
    userInfo.second = encrypt(userInfo.second); // encrypts passwords

    if(!tableOfUsers.contains(userInfo.first)){    // Checks if the user exist
        return false;
    }
    else if(!tableOfUsers.match(userInfo)){     // Checks if the password is the same
        return false;
    }
    else if(userInfo.second == encrypt(newpassword)){  // Checks if old & new passwords are the same
        return false;
    }

    userInfo.second = encrypt(newpassword);
    tableOfUsers.insert(userInfo);  // Will update password instead of inserting 
    return true;                    // brand new pair
}

bool PassServer::find(const string & user) const{   // checks if user exist
    return tableOfUsers.contains(user);
}

void PassServer::dump() const{  // prints entire hashTable to standard output
    tableOfUsers.dump();
}

size_t PassServer::size()const{
    return tableOfUsers.size();     // returning # of entries within the table
}

bool PassServer::write_to_file(const char * filename) const{
    tableOfUsers.write_to_file(filename);       // writes hashTable to file
}

string PassServer::encrypt(const string & str) const{
    char salt[] = "$1$########";                // GNU C Library encryption 
    string newPass(crypt(str.c_str(), salt));
    return newPass.erase(0,12);     // Erasing the salt from encryption
}






