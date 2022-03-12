
#include <assert.h>
#include <iostream>
#include <string>


//
template <typename T>
class MyVector
{
	public:

		/*******************
		 * Static constants
		 ******************/

		/// Default capacity
		static constexpr size_t DEFAULT_CAPACITY = 64;

		/// Minimum capacity
		static constexpr size_t MINIMUM_CAPACITY = 8;

		/*****************************
		 * Constructors / Destructors
		 ****************************/

		/// Normal constructor
		MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {

		size_ = 0;
		capacity_ = capacity;
		elements_ = new T[capacity]();

      // TODO: Your code here
		}

		/// Copy constructor
		MyVector(const MyVector& other) {

		size_ = other.size_;
		capacity_ = other.capacity_;
		elements_ = new T[other.capacity_]();

			// TODO: Your code here
		}

		/**
		 * Destructor
		 * Should call clear() so each element gets its destructor called.
		 * Then, deallocate the internal array and make it a nullptr, if its not already a nullptr.
		 */
		~MyVector() {

		clear();
		//delete [] elements_;
    //elements_ = nullptr;
			// TODO: Your code here
		}

		/************
		 * Operators
		 ************/

		///	Assignment operator
		MyVector& operator=(const MyVector& rhs) {

			if (this != &rhs)
		{
		// size_ = rhs.size_;
		// capacity_ = rhs.capacity_;
		// elements_  = new T[rhs.capacity_];
    std::copy( rhs.elements_, rhs.elements_ + rhs.size_, elements_ );
    size_ = rhs.size_;
		}
		return *this;
			// TODO: Your code here
		}

		/// Operator overload to at()
		T& operator[](size_t index) const {

			return elements_[index];
			// TODO: Your code here
		}

		/************
		 * Accessors
		 ************/

		/// Return the number of valid elements in our data
		size_t size() const {

      	return size_;
			// TODO: Your code here
		}

		/// Return the capacity of our internal array
		size_t capacity() const {

      	return capacity_;
			// TODO: Your code here
		}

		/**
		 * Check whether our vector is empty
		 * Return true if we have zero elements in our array (regardless of capacity)
		 * Otherwise, return false
		 */
		bool empty() const {

		if(size_ == 0) { return true; }
		else { return false; }
			// TODO: Your code here
		}

		/// Return a reference to the element at an index
		T& at(size_t index) const {

			return elements_[index];
			// TODO: Your code here
		}

		/***********
		 * Mutators
		 ***********/

		/**
		 * Reserve capacity in advance, if our capacity isn't currently large enough.
		 * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
		 */
		void reserve(size_t capacity) {

			if(capacity <= capacity_) { return; }
			T* new_elements_ = new T[capacity]();
      for(size_t i = 0; i < size_; i++)
      {
        new_elements_[i] = elements_[i];
      }
      capacity_ = capacity;
      delete [] elements_;
      elements_ = new_elements_;


			// TODO: Your code here
		}

		/**
		 * Set an element at an index.
		 * Throws range error if outside the size boundary.
		 * Returns a reference to the newly set element (not the original)
		 */
		T& set(size_t index, const T& element) {

      if(index > size_) { throw std::range_error("ERROR: outside the size boundary"); }
      elements_[index] = element;
      return elements_[index];
			// TODO: Your code here
		}

		/**
		 * Add an element onto the end of our vector, increasing the size by 1
		 * Should rely on the insert() function to avoid repeating code.
		 * Returns a reference to the newly inserted element
		 */
  T& push_back(const T& element) {

      return insert(size_, element);
			// TODO: Your code here
		}

		/**
		 * Remove the last element in our vector, decreasing the size by 1
		 * Should rely on the erase() function to avoid repeating code.
		 * Returns the new size.
		 */
		size_t pop_back() {

      // erase(0);
      // return size_;
			// // TODO: Your code here
		}

		/**
		 * Insert an element at some index in our vector, increasing the size by 1
		 * Returns a reference to the newly added element (not the original).
		 */
		T& insert(size_t index, const T& element) {

      if(size_ >= capacity_)
      {
        reserve(capacity_ + 1);
      }
      if(index > size_)
      {
        index = size_;
      }
      // ++size_;
      // for(uint i = size_; i > index; i--)
      // {
      //   elements_[i] = elements_[i - 1];
      // }

      // elements_[index] = element;
      // return elements_[index];

      std::move_backward(elements_ + index, elements_ + size_, elements_ + size_ + 1);
      elements_[index] = element;
      ++size_;
      return elements_[index];
			// TODO: Your code here
		}

		/**
		 * Erase one element in our vector at the specified index, decreasing the size by 1
		 * Throws std::range_error if the index is out of bounds.
		 * Calls the erased element's destructor.
		 * Returns the new size.
		 */
		size_t erase(size_t index) {

      if(index > size_) { throw std::range_error("ERROR: outside the size boundary"); }

      // for(size_t i = index; i < size_; i++)
      // {
      //   elements_[i] = elements_[i + 1];
      // }

      std::move(elements_ + index + 1, elements_ + size_, elements_ + index);
      //--size_;
      return size_;
			// TODO: Your code here
		}

		/**
		 * Calls each element's destructor, then clears our internal
		 * data by setting size to zero and resetting the capacity.
		*/
		void clear() {

      while(size_ != 0) elements_[--size_].~T();
      // for(int i = size_; i >= 0; i--)
      // {}
      size_ == 0;
      capacity_ = MyVector::DEFAULT_CAPACITY;
			// TODO: Your code here
		}

	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
	private:

		/// Number of valid elements currently in our vector
		size_t size_ = 0;

		/// Capacity of our vector; The actual size of our internal array
		size_t capacity_ = 0;

		/**
		 * Our internal array of elements of type T.
		 * Starts off as a null pointer.
		 */
		T* elements_ = nullptr;

		/**
		 * Increases the size of our vector by 1 element.
		 * If more capacity is needed, it is doubled.
		 */
		void increaseSize() {

      	if(size_ + 1 <= capacity_)
        {
          size_++;
        }
        else if(size_ + 1 > capacity_)
        {
          size_t new_capacity_ = capacity_ * 2;
          T* new_elements_ = new T[new_capacity_];

          for(size_t i = 0; i < (size() - 1); i++)
          {
            new_elements_[i] = elements_[i];
          }
          size_++;
        }
			// TODO: Your code here
		}

		/**
		 * Decreases the size of our vector by 1 element.
		 * If our size is less than a third of our capacity, cuts our capacity in half.
		 * Capacity should always be at least MyVector::MINIMUM_CAPACITY
		 */
		void decreaseSize() {

      	size_--;

			// TODO: Your code here
		}

		/**
		 * Helper function that is called whenever we need to change the capacity of our vector
		 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
		 */
		void changeCapacity(size_t c) {

     	if(size_ > c) { throw std::range_error("ERROR: cannot change to a capacity that cannot hold existing elements"); }

			T* new_elements_ = new T[c]();
      for(size_t i = 0; i < size_; i++)
      {
        new_elements_[i] = elements_[i];
      }
      capacity_ = c;
      delete [] elements_;
      elements_ = new_elements_;

			// TODO: Your code here
		}

		/**
		 * Copy another vector's elements into our own, by value.
		 * Does not simply copy the other vector's array's pointer
		 * Does not care about matching the capacity exactly.
		 * This is a helper function relied upon by the copy constuctor and the assignment operator
		 */
		void copyOther(const MyVector& other) {

			// TODO: Your code here
		}

		/**
		 * Receives a pointer to an array of elements, and their size.
		 * Throw an std::range_error if we don't already have enough capacity.
		 * Then, create a new temporary array, and copy each element by value.
		 * Next, delete our internal array if it wasn't a null pointer.
		 * Next, assign the new temporary array pointer to our internal array pointer.
		 * Finally, change our size attribute to match.
		 */
		void copyElements(T* pElements, size_t size) {

			// TODO: Your code here
		}

		//
		void assertCapacity(size_t c) const {

      assert(c == capacity_);
			// TODO: Your code here
		}

		//
		void assertBounds(size_t index, std::string message = "") const {

      assert((message, index < capacity_));
			// TODO: Your code here
		}
};
