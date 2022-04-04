#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 *
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 *
 * You may add or remove methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * Although, it may be more difficult to do so. Your choice!
 *
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 *
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom !
 */
namespace CPSC131
{
	/**
	 * Namespace to hold all things related to our DLL
	 */
	namespace DoublyLinkedList
	{
		/**
		 * Node class, which our DLL will use
		 *
		 * The Professor realizes he could have made this an inline class (like the Iterator),
		 * but he is lazy.
		 */
		template <class T>
		class Node
		{
			public:

				/// CTORS: YOUR WELCOME
				Node() : prev_(nullptr), next_(nullptr) {}
				Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}
				Node(T element, Node* prev, Node* next) : element_(element), prev_(prev), next_(next) {}

				/// Set the pointer to the previous element
				// void setPrevious(Node* prev) {}

				/// Set the pointer to the previous element
				void setPrev(Node* prev) {this->prev_ = prev;}

				/// Get a pointer to the previous element
				// Node* getPrevious() {}

				/// Get a pointer to the previous element
				Node* getPrev() {return prev_;}

				/// Set the pointer to the next node
				void setNext(Node* next) {this->next_ = next;}

				/// Get a pointer to the next node
				Node* getNext() { return next_; }

				/// Set the element this node holds
				void setElement(T element) {element_ = element;}

				/// Get the element this node holds
				T& getElement() {return element_;}

				/// Return a reference to the element
				T& operator*() {return &element_;}

			private:
				T element_;
				Node* prev_;
				Node* next_;
		};

		/**
		 * Implement our DoublyLinkedList class !
		 */
		template <class T>
		class DoublyLinkedList
		{
			public:

				/**
				 * Nested Iterator class.
				 * This allows user code to refer to the Iterator's type as:
				 *
				 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
				 *
				 * (as opposed to specifying the template argument two times)
				 */
				class Iterator
				{
					public:

						///	Constructor taking a head and tail pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail) : head_(head), tail_(tail)
						{
							this->cursor_ = this->end();
						}

						///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail, Node<T>* cursor) : head_(head), tail_(tail), cursor_(cursor) {}

						///	Get a pointer to the head node, or end() if this list is empty
						Node<T>* begin()
						{
              if(empty() == true) { return this->end(); }
              return this->head_;
						}

						///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
						Node<T>* end()
						{
              // tail_->getNext() = nullptr;
              // return tail_->getNext();
              return nullptr;
						}

						///	Get the node this iterator is currently pointing to
						Node<T>* getCursor()
						{
              return this->cursor_;
						}

						/**
						 * Assignment operator
						 * Return a copy of this Iterator, after modification
						 *///
						Iterator& operator=(const Iterator& other)
						{
              if(this != &other)
              {
                head_ = other.head_;
                tail_ = other.tail_;
                cursor_ = other.cursor_;
              }
              return *this;
						}

						///	Comparison operator
						bool operator==(const Iterator& other)
						{
              if(cursor_ == other.cursor_) {
                return true;
              } else {
                return false;
              }
						}
						///	Inequality comparison operator
						bool operator!=(const Iterator& other)
						{
              if(*this == other) {
                return false;
              } else {
                return true;
              }
						}

						/**
						 * Prefix increment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator++()
						{
              // if(cursor_ == nullptr) { throw std::invalid_argument("Error: cursor is null"); }
              cursor_ = cursor_->getNext();
              return *this;
						}

						/**
						 * Postfix increment
						 * Return a copy of this Iterator, BEFORE it was modified
						 */
						Iterator operator++(int)
						{
              // Iterator temp( *this );
              // operator++();
              // return temp;
						}

						/**
						 * Prefix decrement operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator--()
						{
              // cursor_ = cursor_->getPrev();
              // return *this;

						}

						/**
						 * Postfix decrement operator
						 * Return a copy of this Iterator BEFORE it was modified
						 */
						Iterator operator--(int)
						{
              // Iterator temp( *this );
              // operator--();
              // return temp;

              // Iterator temp = *this;
              // --(*this);
              // return temp;
						}

						/**
						 * AdditionAssignment operator
						 * Return a copy of the current iterator, after modification
						*/
						Iterator operator +=(size_t add)
						{
              // for(int i = 0; i < add; i++)
              // {
              //   cursor_ = cursor_->getnext();
              // }
						}
						/**
						 * SubtractionAssignment operator
						 * Return a copy of the current iterator, after modification
						 */
						Iterator operator -=(size_t add)
						{
              // for(int i = 0; i < add; i++)
              // {
              //   cursor_ = cursor_->getPrev();
              // }
              // return *this;
              // cursor_ = cursor_ - add;
              // return *this;
						}

						/**
						 * AdditionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator +=(int add)
						{
              // cursor_ = cursor_ + add;
              // return *this;
						}

						/**
						 * SubtractionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator -=(int subtract)
						{
              // cursor_ = cursor_ - subtract;
              // return *this;
						}

						/**
						 * Dereference operator returns a reference to the ELEMENT contained with the current node
						 */
						T& operator*()
						{
              // if(cursor_ == nullptr) throw std::invalid_argument("ERROR: cursor points to null");
              // return cursor_->getElement();
						}

					private:

						/// Pointer to the head node
						Node<T>* head_ = nullptr;

						/// Pointer to the tail node
						Node<T>* tail_ = nullptr;

						/**
						 * Pointer to the cursor node.
						 * This is only one way of letting the iterator traverse the linked list.
						 * You can change to a different method if you wish (and can still pass unit tests)
						 */
						Node<T>* cursor_ = nullptr;

					/// YOUR WELCOME
					friend class DoublyLinkedList;
				};

				/// Your welcome
				DoublyLinkedList() {}

				///	Copy Constructor
				DoublyLinkedList(DoublyLinkedList& other)
				{
          head_ = other.head_;
          tail_ = other.tail_;
          size_ = other.size_;
				}

				/// DTOR: Your welcome
				~DoublyLinkedList()
				{
					this->clear();
				}

				/**
				 * Clear the list and assign the same value, count times.
				 * If count was 5, T was int, and value was 3,
				 * 	we'd end up with a list like {3, 3, 3, 3, 3}
				 */
				void assign(size_t count, const T& value)
				{
          // this->clear();
          // for(size_t i = 0; i < count; i++) {
          //   push_front(value);
          // }
				}

				/**
				 * Clear the list and assign values from another list.
				 * The 'first' iterator points to the first item copied from the other list.
				 * The 'last' iterator points to the last item copied from the other list.
				 *
				 * Example:
				 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
				 * 	Suppose first points to the 4
				 *	Suppose last points to the 7
				 * 	We should end up with our list becoming: {4, 3, 2, 7}
				 *
				 * If the user code sends out-of-order iterators,
				 * 	just copy from 'first' to the end of the source list
				 * Example: first=7, last=4 from the list above would give us:
				 * 	{7, 1}
				 */
				void assign(Iterator first, Iterator last)
				{
          // this->clear();
          // Node<T>* newNode = new Node<T>;

          // for(; first != last; first++){
          //   newNode.setElement(*first);
          // }
          // this = newNode;
				}

				/// Return a pointer to the head node, if any
				Node<T>* head() {
          return head_;
        }

				/// Return a pointer to the tail node, if any
				Node<T>* tail() {
          return tail_;
        }

				/**
				 * Return an iterator that points to the head of our list
				 */
				Iterator begin()
				{
          // auto itr = begin();
          return Iterator(nullptr, nullptr, head_);
				}

				/**
				 * Return an iterator that points to the last element (tail) of our list
				 */
				Iterator last()
				{
          // auto itr = begin();
          // for(; begin() != end(); itr++) {}
          // return itr;
          return Iterator(nullptr, nullptr, tail_);
				}

				/**
				 * Should return an iterator that represents being past the end of our nodes,
				 * or just that we are finished.
				 * You can make this a nullptr or use some other scheme of your choosing,
				 * 	as long as it works with the logic of the rest of your implementations.
				 */
				Iterator end()
				{
          // return end();
          return Iterator(nullptr, nullptr, nullptr);
          // return nullptr;
				}

				/**
				 * Returns true if our list is empty
				 */
				bool empty() const
				{
          if(size_ == 0) {
            return true;
          } else {
            return false;
          }
				}

				/**
				 * Returns the current size of the list
				 * Should finish in constant time!
				 * (keep track of the size elsewhere)
				 */
				size_t size() const
				{
          return size_;
				}

				/**
				 * Clears our entire list, making it empty
				 * Remember: All removal operations should be memory-leak free.
				 */
				void clear()
				{
          // while(size_ != 0) {
          //   pop_front();
          // }
				}

				/**
				 * Insert an element after the node pointed to by the pos Iterator
				 *
				 * If the list is currently empty,
				 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
				 *
				 * If the incoming iterator is this->end(), insert the element at the tail
				 *
				 * Should return an iterator that points to the newly added node
				 *
				 * To avoid repeated code, it might be a good idea to have other methods
				 * 	rely on this one.
				 */
				Iterator insert_after(Iterator pos, const T& value)
				{
          Node<T>* newNode = new Node<T>;
          newNode->setElement(value);
          if(empty()) {head_ = tail_ = newNode;}

          else if(pos.getCursor() == head_) {
            // newNode->setNext(pos.getCursor()->getNext());
            // newNode->setPrev(pos.getCursor());
            // pos.getCursor()->getNext()->setPrev(newNode);
            // pos.getCursor()->setNext(newNode);
            newNode->setNext(head_);
            head_->setPrev(newNode);
            head_ = newNode;
          }

          else if(pos.getCursor() == nullptr) {
            tail_->setNext(newNode);
            newNode->setPrev(tail_);
            tail_ = newNode;
          }
          ++size_;
          return Iterator(nullptr, nullptr, newNode);
				}

				/**
				 * Insert a new element after the index pos.
				 * Should work with an empty list.
				 *
				 * Should return an iterator pointing to the newly created node
				 *
				 * To reduce repeated code, you may want to simply find
				 * 	an iterator to the node at the pos index, then
				 * 	send it to the other overload of this method.
				*/
				Iterator insert_after(size_t pos, const T& value)
				{
          // auto itr = begin();
          // itr = std::advance(itr, pos);
          // // while(itr < static_cast<int>(pos)) {itr++;}
          // return insert_after(itr, value);
          size_++;
				}

				/**
				 * Erase the node pointed to by the Iterator's cursor.
				 *
				 * If the 'pos' iterator does not point to a valid node,
				 * 	throw an std::range_error
				 *
				 * Return an iterator to the node AFTER the one we erased,
				 * 	or this->end() if we just erased the tail
				 */
				Iterator erase(Iterator pos)
				{
          if(pos.getCursor() == nullptr) throw std::range_error("iterator does not point to a valid node");

          if(pos.getCursor() == head_){
            if(pos.getCursor() == tail_) {
              // tail_ = tail_->getPrev();
              // tail_->setNext(nullptr);
              // delete pos.getCursor();
              // return this->end();
              head_ = tail_ = nullptr;
              // return this->end();
            }
            else {
              head_ = head_->getNext();
              head_->setPrev(nullptr);
            }
          }

          else if(pos.getCursor() == tail_) {
            tail_ = tail_->getPrev();
            tail_->setNext(nullptr);
          }
          else {
            pos.getCursor()->getNext()->setPrev(pos.getCursor()->getPrev());
            pos.getCursor()->getPrev()->setNext(pos.getCursor()->getNext());
          }
            --size_;
            Iterator returnNode(nullptr, nullptr, pos.getCursor()->getNext());
            delete pos.getCursor();
            return returnNode;
				}

				/**
				 * Add an element just after the one pointed to by the 'pos' iterator
				 *
				 * Should return an iterator pointing to the newly created node
				 */
				Iterator push_after(Iterator pos, const T& value)
				{
          // Node<T>* newNode = new Node<T>;
          // // if(empty()) {head_ = tail_ = newNode;}
          // newNode->setElement(value);
          // pos.getCursor()->setNext(newNode);
          // newNode->setPrev(pos.getCursor());
          // newNode->setNext(pos.getCursor()->getNext()->getNext());
          // ++size_;
          // return Iterator(nullptr, nullptr, newNode);
				}

				/**
				 * Add a new element to the front of our list.
				 */
				void push_front(const T& value)
				{
          Node<T>* newNode = new Node<T>;
          if(empty()) {head_ = tail_ = newNode;}
          newNode->setElement(value);
          newNode->setNext(head_);
          newNode->setPrev(newNode);
          head_ = newNode;
          ++size_;
				}

				/**
				 * Add an element to the end of this list.
				 *
				 * Should return an iterator pointing to the newly created node.
				 */
				Iterator push_back(const T& value)
				{
          Node<T>* newNode = new Node<T>;
          if(empty()) {head_ = tail_ = newNode;}
          newNode->setElement(value);
          newNode->setPrev(tail_);
          tail_->setNext(newNode);
          tail_ = newNode;
          ++size_;
          return Iterator(nullptr, nullptr, newNode);
				}

				/**
				 * Remove the node at the front of our list
				 *
				 * Should throw an exception if our list is empty
				 */
				void pop_front()
				{
          if(empty()) throw std::length_error("empty list");

          erase(begin());
          // Node<T>* u = head_;
          // head_ = head_->getNext();
          // delete u;
          // // if(head_ != nullptr) {head_->setPrev(nullptr);}
          // size_--;
				}

				/**
				 * Return a reference to the element at the front.
				 *
				 * Throw an exception if the list is empty
				 */
				T& front()
				{
          if(empty() == true) throw std::length_error("empty list");
          return head_->getElement();
				}

				/**
				 * Return a reference to the element at the back.
				 *
				 * Throw an exception if the list is empty
				 */
				T& back()
				{
          if(empty() == true) throw std::length_error("empty list");
          return tail_->getElement();
				}

				/**
				 * Return the element at an index
				 *
				 * Should throw a range_error is out of bounds
				 */
				T& at(size_t index)
				{
          // if((index >= size_) || (index < 0)) {
          //   throw std::range_error("ERROR: outside the size boundary");
          // }
          // size_t i = 0;
          // for(auto itr = begin(); itr != end(); itr++, i++) {
          //   if(i == index) {return *itr;}
          // }
				}

				/**
				 * Reverse the current list
				 *
				 * It might be easy to consider the following:
				 * - Create a temp empty list
				 * - Iterate through the current list
				 * - For each item in the current list, push to the FRONT (not back)
				 * - Assign the current list to the temp list
				 * - Discard the temp list
				 */
				void reverse()
				{

				}

				/**
				 * I bet you're happy I'm not making you do this.
				 * No tests will be run against this function,
				 * 	but feel free to try it out, as a challenge!
				 *
				 * If I were doing this and didn't care too much for efficiency,
				 * 	I would probably create an extra helper function to swap two
				 * 	positions in the current list.
				 * Then I would simply sweep through the list bubble-sort style.
				 * Perhaps selection sort.
				 *
				 * If you want a huge challenge, try implementing quicksort.
				 *
				 * (but again, don't worry about this method; it will not be tested)
				 */
				void sort()
				{

				}

				/**
				 * Assignment operator
				 *
				 * Clear this list and fill it with the others' values
				 * (by value, not by reference)
				 *
				 * Return a reference to this list
				 */
				DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
				{
          // this->clear();
				}

				/**
				 * Return true if the lists are "equal"
				 *
				 * "Equal" here is defined as:
				 * - Same size
				 * - Elements at the same indexes would return true for their own comparison operators
				 *
				 * In other words: "They contain all the same values"
				 * (no need to be references to each other)
				 */
				bool operator ==(DoublyLinkedList<T>& other)
				{
          // if(size_ == other.size_) {
          //   for(size_t i = 0; i < size_; i++) {
          //     if(this->getElement() != other.getElement()) return false;
          //     this->getNext();
          //     other.getNext();
          //   }
          // }
				}

				/**
				 * Return true if the lists are "not equal"
				 *
				 * See the operator== stub for definition of "equal"
				 *
				 * Probably want to avoid repeated code by relying on the other operator
				 */
				bool operator !=(DoublyLinkedList<T>& other)
				{

				}

			private:
				Node<T>* head_ = nullptr;
				Node<T>* tail_ = nullptr;
				size_t size_ = 0;
		};
	}
}

#endif















































/// Yes, I'm aware it's spelled you're*
