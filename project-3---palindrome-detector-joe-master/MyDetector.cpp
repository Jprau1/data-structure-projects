

/**
 * TODO: Complete these class definitions
 */

/// Starter includes
#include "MyDetector.hpp"
#include "MyStack.hpp"
#include "MyQueue.hpp"


//
namespace CPSC131::PalindromeDetector
{
	/// Your welcome
	MyDetector::MyDetector() {}

	//
	bool MyDetector::isPalindrome(std::string s)
	{
    for(size_t i = 0; i < s.length(); i++) {
      if(isalpha(s[i])){
        s[i] = tolower(s[i]);
        stack.push(s[i]);
        queue.enqueue(s[i]);
      }
    }

    for(size_t i = stack.size(); i > 0; i--) {
      if(stack.top() != queue.front()) {
        stack.clear();
        queue.clear();
        return false;
      }
      stack.pop();
      queue.dequeue();
    }
    stack.clear();
    queue.clear();
    return true;
	}
}
