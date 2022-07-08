//
// Created by davew on 10/12/21.
//

#include <iostream>   // access system "iostream" library, include with < >
using std::cout;      // avoid having to write std:: in front of cout all the time
using std::cerr;
using std::endl;
#include <string>     // C++ string class, known as std::string
#include <cassert>    // for "assert", used below
#include <cstring>

#include "stringExamples.h"  // access part of my project, include with " "

// #include <cstring.h>   // old-style C string functions, e.g., strlen, strcpy


std::string withExclamation(const std::string &sentence)	// use "const" and "&" to avoid making a copy of the sentence, but not changing it
{
	return sentence+"!";
}

void   addExclamation(std::string &sentence)  	// change "sentence", in this one, and return nothing
{
	sentence = sentence+"!";
}

char *withExclamationClassic(char *sentence)
{
	char *newSentence = (char *) malloc(strlen(sentence)+1 + 1); // 1 byte for the "!", one for C's end-of-string marker
	strcpy(newSentence, sentence); // copy the existing characters
	newSentence[strlen(sentence)] = '!';
	newSentence[strlen(sentence)+1] = '!';
	return newSentence;
}


/*
 * Various idioms for "string compare" ... given s1 and s2, return
 *     0, if s1 == s2, i.e., the strings have identical sequences of characters
 *    +1, if s1 >  s2, i.e., s1 is after  s2 in the dictionary or an extension of s2
 *    -1, if s1 <  s2, i.e., s1 is before s2 in the dictionary or a prefix of s2
 *
 *    "dictionary" means "lexicographical order in the character-set values",
 *      so the lower-case alphabet is in order, but all upper-case is first,
 *      and numerals, punctuation, etc., all have consistent places
 *
 * e.g., see the example sweep "strcmp_examples" below the codes
 */



/* classic C-style string compare, array idioms, code version 1 */
int strcmp1(const char s1[], const char s2[])  //   =:-O   note that these are _also_ type char*
{
	int i=0;
	while (s1[i] != 0 and s2[i] != 0) {  // keep looking until one string ends
		if (s1[i] < s2[i]) {
			return -1;
		} else if (s1[i] > s2[i]) {
			return +1;
		}
		i++;		
	}
	if (s1[i] == 0 and s2[i] == 0) {
		return 0;   // both ended without seeing a difference
	} else if (s1[i] == 0) {
		return -1;  // s1 is shorter
	} else {
		assert (s2[i] == 0); // only way to get here
		return +1;  // s2 is shorter
	}
}

/* classic C-style string compare, pointer idioms, code version 1 */
int strcmp2(const char *s1, const char *s2)
{
	while (*s1 and *s2) {       // Note: null character treated as "False"
		if (*s1 < *s2) {    // *s1 is "the character pointed to by s1"
			return -1;
		} else if (*s1 > *s2) {
			return +1;
		}
		s1++;  // point to the next character in the array
		s2++;
	}
	if (not (*s1 or *s2)) { // both are null characters, work it out :-)
		return 0;   // both ended without seeing a difference
	} else if (not (*s1)) {
		return -1;  // s1 is shorter
	} else {
		assert (not (*s2)); // only way to get here
		return +1;  // s2 is shorter
	}
}

/* classic C-style string compare, array idioms, code version 2 */
int strcmp3(const char s1[], const char s2[])
{
	// this version emphasizes doing the fewest steps within the loop
	int i=0;
	while (s1[i] != 0                and s1[i] == s2[i]) {
		// note: "and s2[i] != 0" is redundant, since it makes one of the above true
		i++;
	}
	// Now, what happened?
	if (s1[i] == 0 and s2[i] == 0) {
		return 0;   // both ended without seeing a difference
	} else if (s1[i] == 0) {
		return -1;  // s1 is shorter
	} else if (s2[i] == 0) {
		return +1;  // s2 is shorter
	} else if (s1[i] < s2[i]) {
		return -1;  // s1 is earlier in the ordering
	} else {
		assert(s1[i] > s2[i]);
		return +1;  // s1 is further in the ordering
	}
}

void strcmpExamples()
{
	auto strcmp = strcmp2; // set to any of the above or std::strcmp;
	if (not ((strcmp("good", "good")   == 0) and
		 (strcmp("good", "evil")    > 0) and  // good > evil
		 (strcmp("Good", "good")    < 0) and  // capitals come first
		 (strcmp("Zoo", "aardvark") < 0) and  // _all_ capitals
		 (strcmp("good", "goody")   < 0))) {  // good < goody, it's a prefix
		cerr << "Wait, something's wrong in the strcmp examples" << endl;
	}
}



// a simple example that takes a string parameter and returns an int
int countXs(const std::string &s)
{
	int n_Xs = 0;
	for (char c : s) {
		if (c == 'X') n_Xs++;
	}
	// Old-style C equivalent still works, too:
	int n_XsAgain = 0;
	unsigned int i; // the one above could be 'unsigned' too
	for (i = 0; i<s.length(); i++) { // 'i' takes on each valid index
		if (s[i] == 'X') n_XsAgain++;
	}
	assert(n_Xs == n_XsAgain); // let me know, if this isn't true
	return n_Xs;
}

void testStringFunctions()
{
	cout << endl << "============ test string functions and built-ins ============" << endl << endl;

	std::string sentence1 = "My string function works";
	std::string sentence2 = "I'm inexplicably excited about that";
	
	cout << "withExclamation(sentence1) = " << withExclamation(sentence1) << endl;
	addExclamation(sentence2);
	cout << "after addExclamation(sentence2), sentence2 is now " << sentence2 << endl;
	cout << "   and sentence1 is still " << sentence1 << endl;

	char sentence3[] = "I should be excited if I can figure out old-school C functions";
	char *sentence3_done  = withExclamationClassic(sentence3);

	cout << "sentence3_done = withExclamation(sentence3) = " << sentence3 << endl;
	cout << "don't forget to free memory here, or your program may crash later :-(" << endl;
	free(sentence3_done);
	
	std::string sixX = "This boX of siX strings actually only has two X's in it ... no, wait, it has three X's now; I mean four X's; five X's! NEVERMIND!!";
	cout << "countXs(\"" << sixX << "\") = " << countXs(sixX) << endl;

	cout << endl << "  Note: string operations can sometimes reveal C++'s expectation" << endl;
	cout <<         "        that you think about the possible range of integer values" << endl;
	cout <<         "        and the implications of operators working only in this range:" << endl;

	cout << "string length test ... what is string(\"test\").length()?   " << std::string("test").length() << endl;
	cout << "string length test ... what is string(\"test\").length()-5? " << std::string("test").length()-5 << endl;
}
