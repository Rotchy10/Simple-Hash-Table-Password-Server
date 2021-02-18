#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <utility>

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

using namespace std;
namespace COP4530{
template<typename K, typename V>
class HashTable
{    
    public:                 // Public Member Functions ================
    HashTable(size_t size = 101);   // Default Constructor 
    ~HashTable();                   // Destructor
    bool contains(const K & k) const;       // Checks if a key exist in table
    bool match(const pair<K,V> & kv) const;       // Checks if key-value pair exist in table
    bool insert(const pair<K,V> & kv);      // Inserts key-value pair in table (updates value if different value)
    bool insert(const pair<K,V> && kv);     // Move Insert
    bool remove(const K & k);               // Removes entry with corresponding key K, if it exist
    void clear();                           // Empties out the list 
    bool load(const char * filename);       // Loads file of key-value pairs into table
    void dump() const;                      // List all entries in table 
    size_t size() const;                    // Returns # of entries currently in table
    bool write_to_file(const char * filename) const;    // Writes all entries in table to given file

    private:                 // Private Member Functions ===========================
    void makeEmpty();                       // Deletes all contents within the list  
    void rehash();                          // Doubles the size of table and rehases all entries
    size_t myhash(const K & k) const;       // Hashfunction
    unsigned long prime_below(unsigned long n) const;
    void setPrimes(vector<unsigned long> &) const;

    vector<list<std::pair<K,V>>> table;
    size_t numEntries;
    };
}
#include "hashtable.hpp"

#endif
