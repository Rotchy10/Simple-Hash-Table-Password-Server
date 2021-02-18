#include <vector>
#include <list>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>

using namespace std;
using namespace COP4530;

// ==================== CONSTRUCTOR and DESTRUCTOR ======================
template<typename K, typename V>
HashTable<K,V>::HashTable(size_t size){

  table.resize(prime_below(size));    // Using prime_below to set the size of
                                      // the vector
  numEntries = 0;                     // Setting # of Entries to 0
}
template<typename K, typename V>
HashTable<K,V>::~HashTable(){         // Desctructor will call clear function to 
  clear();                            // empty out the list
}

// ===================== PUBLIC MEMBER FUNCTIONS ===================
template<typename K, typename V>
bool HashTable<K,V>::contains(const K & k) const{
  auto & currentList = table[myhash(k)];
  auto itr = currentList.begin();

  while(itr != currentList.end()){    // Uses iterator to go through each linked
    if((*itr).first == k)             // list, and checks if the key is present
      return true;
    else 
      itr++;
  }
  return false;
}
template<typename K, typename V>
bool HashTable<K,V>::match(const pair<K,V> & kv) const{
  auto & currentList = table[myhash(kv.first)];
  auto itr = currentList.begin();

  while(itr != currentList.end()){                                  // Uses iterator and checks if each 
    if(((*itr).second == kv.second) && ((*itr).first == kv.first))  // individual node matches the given paramters
      return true;
    else{                                                       // Will return true if a match has been found,
      itr++;                                                    // false otherwise 
    }
  }
  return false;
}
template<typename K, typename V>
bool HashTable<K,V>::insert(const pair<K,V> & kv){

  auto & currentList = table[myhash(kv.first)];
  
  if(!match(kv)){                             // <-- This first checks if the pair being inserted is already
    auto itr = currentList.begin();           // within the hashTable
    while(itr != currentList.end()){
      if(((*itr).first == kv.first) && ((*itr).second != kv.second)){
        (*itr).second = kv.second;            // Will update the value if Key is already in the 
        return true;                          // table but holds a diff value
      }
      itr++;
    }

    currentList.push_back(kv);

    if(++numEntries > table.size())       // Checking to see if a rehash of entire table
      rehash();                           // is necassary after insert

    return true;
  }
  else{
    return false;       // Will return false if pair already exist within the list
  }
}
template<typename K, typename V>
bool HashTable<K,V>::insert(const pair<K,V> && kv){
  return insert(std::move(kv));
}
template<typename K, typename V>
bool HashTable<K,V>::remove(const K & k){

  auto & currentList = table[myhash(k)];  
  auto itr = currentList.begin();
                                    // Uses iterator to move through table
  while(itr != currentList.end()){  
    if((*itr).first == k){      // Continuously checks if itr is at the specified
      currentList.erase(itr);   // key to remove
      numEntries--;       // Will remove entry when found and decrement # of entries
      return true;
    }
    itr++;
  }
  return false;
}
template<typename K, typename V>
void HashTable<K,V>::clear(){
  makeEmpty();      // called private member function makeEmpty;
}
template<typename K, typename V>
bool HashTable<K,V>::load(const char * filename){
  ifstream fin;

  fin.open(filename);
  std::pair<K,V> p1;      // Reading in key value pairs from file
                          // and inserts them within the hashtable
  if(!fin.is_open())
    return false;
    
  while(!fin.eof()){
    fin >> p1.first;
    fin >> p1.second;
    insert(p1);
  }
  fin.close();
  return true;
}
template<typename K, typename V>
void HashTable<K,V>::dump() const{

  for(int i=0; i < table.size(); i++)
  {
    cout << "v[" << i << "]: ";   // Prints entire hashTable to standard output
                                  // with the following format
    if(!table[i].empty()){              // v[index]: 'key' 'value' : 'key' 'value' : ...
      auto itr = table[i].begin();      // If multiple intries exist in same list, they will be
      while(itr != table[i].end())      // seperated by a : 
      {
        cout << (*itr).first 
        << " " << (*itr).second;
        
        if(++itr != table[i].end())
          cout << " : ";
      }
    } 
    cout << endl;
  }
}
template<typename K, typename V>
size_t HashTable<K,V>::size() const{
  return numEntries;    // Return # intries within the table
}
template<typename K, typename V>
bool HashTable<K,V>::write_to_file(const char * filename) const
{
  ofstream fout;
  fout.open(filename);

  if(!fout.is_open())     // Checking is file was opened or not
    return false;

  for(int i=0; i < table.size(); i++)
  {
    if(!table[i].empty()){          // Prints to file in same format as the load
      auto itr = table[i].begin();  // function
      while(itr != table[i].end())
      {
        fout << (*itr).first 
        << " " << (*itr).second << endl;
        itr++;
      }
    } 
  }
  fout.close();
  return true;
}

//======================== PRIVATE FUNCTIONS ======================================
template<typename K, typename V>
void HashTable<K,V>::makeEmpty(){       // Goes each linked-list in hashtable to delete 
  for(int i = 0; i < table.size(); i++) // all the nodes
    table[i].clear();
  numEntries = 0;                   // Also resets # entries back to zero
}
template<typename K, typename V>
void HashTable<K,V>::rehash(){
  auto myOldVector = table;               // Copies vector over
  auto & currentOldList = myOldVector[0];

  makeEmpty();                                  // Clears current Vecotr
  table.resize(prime_below(table.size() * 2));  // Doubles the size of the vector (also finds prime)

  for(int i = 0; i < myOldVector.size(); i++){  // This loop iterates through the copy vector and
    auto & currentOldList = myOldVector[i];     // rehashes everything, and inserts into the new vector
    
    if(!currentOldList.empty()){                
      auto itr = currentOldList.begin();

      while(itr != currentOldList.end()){
        insert(*itr);
        itr = currentOldList.erase(itr);
      }
    }
  }
}
template<typename K, typename V>
size_t HashTable<K,V>::myhash(const K & k) const{   // Returns which intex value K maps to
  static hash<K> hf;
  return hf(k) % table.size();                      // mod by table size making sure value
}                                                   // stays within bounds

// ============================================================================
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n) const
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
return n;
      --n;
    }

  return 2;
}
//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes) const
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

