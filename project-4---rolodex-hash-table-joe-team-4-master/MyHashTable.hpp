#ifndef MY_HASH_TABLE_HPP
#define MY_HASH_TABLE_HPP


/**
 * TODO: Complete this class!
 */


/// Your welcome
#include <forward_list>
#include <functional>
#include <memory>
#include <string>


//	More includes ... ?
#include <stdexcept>
#include <iostream>


///	Begin our class namespace
namespace CPSC131::MyHashTable
{
	//
	template<class VTYPE>
	class MyHashTable
	{
		//
		public:

			//
			static constexpr size_t DEFAULT_CAPACITY = 1024;
			static constexpr size_t ULLONG_WRAP_AT = 4294967295;

			/**
			 * Constructor
			 *
			 * Probably easiest to do the following:
			 *
			 *   1. Call on setCapacity() to set the table's capacity
			 */
			MyHashTable(size_t capacity = MyHashTable::DEFAULT_CAPACITY)
			{
        setCapacity(capacity);
			}

			/**
			 * Copy constructor
			 */
			MyHashTable(const MyHashTable& other)
			{
        capacity_ = other.capacity_;
        size_ = other.size_;
        n_collisions_ = other.n_collisions_;
        table_ = other.table_;
			}

			/**
			 * Destructor
			 *
			 * Deallocate the table (array of std::forward_list 's), and set the table to nullptr
			 * Don't double-deallocate if the table is already a null pointer
			 */
			~MyHashTable()
			{
        if(table_ != nullptr)
        {
          clear();
          table_ = nullptr;
        }
			}

			/**
			 * Should return the capacity_ of this hash table
			 * Meaning, the total number of rows in this hash table
			 * Doesn't discern between used/unused/collided rows
			 */
			size_t capacity()
			{
        return capacity_;
			}

			/**
			 * Should return the number of items currently in the hash table
			 */
			size_t size()
			{
        return size_;
			}

			/**
			 * Return true if the table is empty, false otherwise
			 */
			bool empty()
			{
        if(size_ == 0) { return true; }
				return false;
			}

			/**
			 * Should return the number of collisions currently present in the hash table
			 */
			size_t n_collisions()
			{
        return n_collisions_;
			}

			/**
			 * Set the capacity for this table.
			 * Changes the total number of hash table rows available.
			 *
			 * Existing entries should survive the change,
			 * 	so you probably want to do the following:
			 *
			 *  1. Keep the existing table array pointer in a temporary pointer
			 *
			 *  2. Re-initialize 'this' to contain a new empty table of the right capacity
			 *
			 *  3. The temporary pointer should now contain the OLD data (old table),
			 *     while 'this' contains the brand new table of the new size.
			 *
			 *  4. Iterate through all key/value pairs in the old data (temp pointer).
			 *
			 *  5. For each key/value pair in the old data, call this->add() to insert
			 *     properly into the new table.
			 *
			 *  6. Deallocate the old table by calling `delete []` on the temporary pointer.
			 *
			 * Don't forget to check whether the current table is a nullptr before you
			 *  decide to do iterations!
			 */
			void setCapacity(size_t c)
			{
        std::forward_list<std::pair<std::string, VTYPE>> * temp = table_;         // create a temp hash table and assign it the old
        size_t tempCap = capacity_;                                               // copy the old capacity to temp
        this->table_ = new std::forward_list<std::pair<std::string, VTYPE>>[c];   // create new hash table
        this->capacity_ = c;                                                      // change capacity of new hash table
        this->n_collisions_ = 0;
        if(temp != nullptr)                                                       // check if the old table is null before iterating
        {
          for(size_t i = 0; i < tempCap; i++)                                     // iterate throw every row
          {
            for(auto itr = temp[i].begin(); itr != temp[i].end(); itr++)          // in each row, iterate through forward list
            {
              this->add((*itr).first, (*itr).second);                             // add pair elements into new table from temp table
            }
          }
        }
        delete [] temp;                                                           // delete the temp hash table
			}

			///	Your welcome
			unsigned long long int hash(std::string key) const
			{
				return this->midSquareHash(key);
			}

			/**
			 * Implement the "modified mid square" hash function,
			 * as described in the instructions.
			 */
			unsigned long long int midSquareHash(std::string key) const
			{
        unsigned long long int sum = 1;

        for(unsigned long int i = 0; i < key.length(); i++)
        {
          unsigned long long int temp = (unsigned long long int)key[i];
          sum *= temp;
          sum %= ULLONG_WRAP_AT;
        }
        sum *= sum;

        std::string temp = std::to_string(sum);

        std::string hashCode = temp.substr(temp.length()/4, temp.length()/2);   // shrink the hash code
        unsigned long long int hash = std::stoull(hashCode, nullptr, 10);       // turn string to ull
        return hash;
			}

			/**
			 * Implement your own custom hash functions to compete on the Gradescope Leaderboard!
			 * Four stubs are provided to make experimentation a little easier.
			 * Only the best hash function will count towards the leaderboard.
			 */
			unsigned long long int myCustomHashFunction1(std::string key) const
			{
				return 0;
			}
			unsigned long long int myCustomHashFunction2(std::string key) const
			{
				return 0;
			}
			unsigned long long int myCustomHashFunction3(std::string key) const
			{
				return this->midSquareHash(key);
			}
			unsigned long long int myCustomHashFunction4(std::string key) const
			{
				return 0;
			}

			/**
			 * Return true if a key exists in the table, or false otherwise.
			 */
			bool exists(std::string key) const
			{
        unsigned long long int hashKey = hash(key);                               // hash code
        size_t index = (size_t)hashKey % capacity_;                               // hash code used for index
        for(auto itr = table_[index].begin(); itr != table_[index].end(); itr++)
        {
          if((*itr).first == std::to_string(hashKey)) { return true; }            // if key inside pair matches, return true
        }
        return false;
			}

			/**
			 * Add a key/value pair to this table.
			 * If the key already exists, throw a runtime_error.
			 */
			void add(std::string key, VTYPE value)
			{
        // if(exists(key)) { throw std::runtime_error("ERROR: key already exists"); }  // throws error

        unsigned long long int hashKey = hash(key);
        size_t index = (size_t)hashKey % capacity_;                               // hash code used for index
        if(exists(key))
        {
          ++n_collisions_;
          ++hashKey;
        }
        std::string strHashKey = std::to_string(hashKey);                         // hash code to string for pair
        std::pair pair = std::make_pair(strHashKey, value);
        table_[index].push_front(pair);
        size_++;
			}

			/**
			 * Should return a reference to the VTYPE value associated to the provided key.
			 * If the key/value pair isn't in the table, a runtime_error should be thrown.
			 */
			VTYPE& get(std::string key) const
			{
        if(exists(key) == false) { throw std::runtime_error("ERROR: pair does not exist"); }

        unsigned long long int hashKey = hash(key);
        size_t index = (size_t)hashKey % capacity_;
        return table_[index].front().second;
			}

			/**
			 * Remove a key/value pair that corresponds to the provided key.
			 * If no such key exists, throw a runtime_error.
			 */
			void remove(std::string key)
			{
        if(exists(key) == false) { throw std::runtime_error("ERROR: key does not exist"); }

        // auto hashKey = hash(key);
        // size_t index = (size_t)hashKey % capacity_;

        // auto itr = table_[index].before_begin();
        // auto temp = itr;
        // for(; itr != table_[index].end(); itr++)
        // {
        //   if(temp->first == key) { table_[index].erase_after(itr); }
        //   // if(++temp != table_[index].end()) { ++temp; }
        // }
        // // n_collisions_--;
        // size_--;
			}

			/**
			 * Remove all entries in this table
			 * Iterate over each table row and call clear on the row's list
			 */
			void clear()
			{
        for(size_t i = 0; i < capacity_; i++)
        {
          table_[i].clear();
        }
        size_ = 0;
			}

			/**
			 * Assignment Operator
			 */
			MyHashTable<VTYPE>& operator=(const MyHashTable<VTYPE>& other)
			{
        if(this != &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        n_collisions_ = other.n_collisions_;
        table_ = other.table_;
        }
        return *this;
			}

		//
		private:

			/**
			 * Keeps track of the capacity of this hash table
			 * (total number of rows in the table, whether used or not)
			 * (does not care about collisions)
			 */
			size_t capacity_ = 0;

			/**
			 * Keeps track of the total number of items currently in
			 * the hash table
			 */
			size_t size_ = 0;

			/**
			 * Keeps track of the number of collisions currently present in the table
			 */
			size_t n_collisions_ = 0;

			/**
			 * The actual hash table.
			 * We'll make this a fixed-sized array,
			 *   but dynamically allocated so we can resize whenever we need.
			 *
			 * Try to imagine each table row is actually a complete forward_list.
			 * In a perfect situation where a table has no collisions, each list
			 *   will simply contain one item.
			 *
			 * One "item" in this case refers to an std::pair<std::string, VTYPE>,
			 *   where the first part of the pair is the key and the second
			 *   is the value (of type VTYPE).
			 */
			std::forward_list<std::pair<std::string, VTYPE>> * table_ = nullptr;

	};
}













#endif
