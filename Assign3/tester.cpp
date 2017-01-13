/*
 * This is a tester similar to the tester written in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our wordset class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 * After the test completes, I make sure the local variabls are properly
 * cleaned up.
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Peter Jensen and Ryan Welling
 * January 28, 2015
 */

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "wordset.h"
#include "node.h"

using namespace std;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualify the class names below with cs3505::

int main ()
{

  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.
    cs3505::wordset  our_set_of_words(1000);  // Our set class, with a hashtable of 1000 slots.
    bool failed = false;
  
    // Open the file stream for reading.  (We'll be able to use it just like
    //   the keyboard stream 'cin'.)
    ifstream in("Yankee.txt");

    // Loop for reading the file.  Note that it is controlled
    //   from within the loop (see the 'break').
    while (true)
    {
      // Read a word (don't worry about punctuation)
      string word;
      in >> word;

      // If the read failed, we're probably at end of file
      //   (or else the disk went bad).  Exit the loop.
      if (in.fail())
	break;

      // Word successfully read.  Add it to both sets.
      stl_set_of_words.insert(word);
      our_set_of_words.add(word);
    }

    // Close the file.
    in.close();

    /** 
     * My added tests
     */

    // Test removal of first item
    string *f = new string[1];
    our_set_of_words.get_elements(f, 1);
    string first = f[0];
    our_set_of_words.remove(first);
    if(our_set_of_words.contains(first)) {
      cout << "ERROR: Our set should not contain - " << first << endl;
    }

    // Test removal of last item
    string *g = new string[19168];
    our_set_of_words.get_elements(g, 19168);
    string last = g[19167];
    our_set_of_words.remove(last);
    if(our_set_of_words.contains(last)) {
      cout << "ERROR: Our set should not contain - "<< last << endl;
      failed = true;
    }

    // Test removal in the middle
    our_set_of_words.remove("youth");
    if(our_set_of_words.contains("youth")) {
      cout << "ERROR: Our set should not contain 'youth'" << endl;
      failed = true;
    }

    // Test equal operator overload
    cs3505::wordset  my_copy_set(1000);
    my_copy_set = our_set_of_words;
    if(my_copy_set.size() != our_set_of_words.size()) {
      cout << "ERROR: Set created with equal operator does not equal in size to original" << endl;
      failed = true;
    }

    // Test equal operator and get_elements method
    // Create array from original set
    string *equalTest1 = new string[19166];
    our_set_of_words.get_elements(equalTest1, 19166);

    // Create theoretical identical array from copy set
    string *equalTest2 = new string[19166];
    my_copy_set.get_elements(equalTest2, 19166);

    // Grab random place in sets and compare to see if values are equal
    for(int i = 10055; i < 11055; i++) {
      if(equalTest1[i] != equalTest2[i]) {
	  cout << "ERROR: Set is not equal to original for given values" << endl;
	  failed = true;
	}
    }

    // Remove most of original set, make sure that copy set doesn't rely on original set
    for(int i = 0; i < our_set_of_words.size(); i++) {
      our_set_of_words.remove(equalTest1[i]);
    }

    if(my_copy_set.size() == our_set_of_words.size()) {
      cout << "Original set was cleaned, sizes should not be the same" << endl;
      failed = true;
    }

    // Print out the number of words found in each set.
    cout << endl;
    cout << "STL set contains " << stl_set_of_words.size() << " unique words.\n";
    cout << "Our set contains " << our_set_of_words.size() << " unique words after deletions.\n";
    cout << endl;

    // If any tests have failed, bool will be tripped
    if(failed) {
      cout << "Tests failed" << endl;
      cout << endl;
    }
    else {
      cout << "Tests passed" << endl;
      cout << endl;
    }
  }

  // Now that the objects have been destroyed, I will simply call my auditing
  // code to print out how many times constructors have been called, and
  // how many times destructors have been called.  They should exactly match.
  // If not, we have a memory problem.

  cout << "Class cs3505::wordset:" << endl;
  cout << "    Objects created:  " << cs3505::wordset::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::wordset::destructor_count() << endl;
  cout << endl;

  cout << "Class cs3505::node:" << endl;
  cout << "    Objects created:  " << cs3505::node::constructor_count() << endl;
  cout << "    Objects deleted:  " << cs3505::node::destructor_count() << endl;
  cout << endl;

  // Now we're really done.  End main.
  
  return 0;
}
