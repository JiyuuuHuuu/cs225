/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
  ++elems;
  if (shouldResize()) resizeTable();
  size_t index = hashes::hash(key, size);
  while (table[index]!= NULL) index = (index+1)%size;

    table[index] = new std::pair<K,V>(key, value);
    should_probe[index] = true;
    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
(void) key;
(void) value;
  // prevent warnings... When you implement this function, remove this line.
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
  int removeIndex = findIndex(key);
  if(removeIndex != -1){
    delete table[removeIndex];
    table[removeIndex] = NULL;
    --elems;
  }
    /**
     * @todo: implement this function
     */
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
  size_t i = hashes::hash(key,size);
  size_t start = i;
  while(should_probe[i]){
    if (table[i] != NULL && table[i]->first == key) {
      return i;
    }
    i = (i+1)%size;
    if(start == i) break;
  }
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */

    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int index = findIndex(key);
    if (index != -1)
        return table[index]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int index = findIndex(key);
    if (index == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        index = findIndex(key);
    }
    return table[index]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
  size_t newSize = findPrime(size*2);
  delete[] should_probe;
  should_probe = new bool[newSize];
  std::pair<K,V>** newTable = new std::pair<K,V>*[newSize];
  for (size_t i = 0; i < newSize; i++){
    newTable[i] = NULL;
    should_probe[i] = false;
  }
  for(size_t j = 0; j < size; j++){
    if (table[j] != NULL){
      size_t index = hashes::hash(table[j]->first, newSize);
      while(newTable[index] != NULL) index = (index+1)%size;
      newTable[index] = table[j];
      should_probe[index] = true;
    }
  }
  delete[] table;
  table = newTable;
  size = newSize;
    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
}