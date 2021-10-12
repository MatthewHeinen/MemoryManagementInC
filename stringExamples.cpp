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
	char *newSentence = (char *) malloc(strlen(sentence)+1 + 1); // 1 byte for the "!", one for the end-of-string marker
	strcpy(newSentence, sentence); // copy the existing characters
	newSentence[strlen(sentence)] = '!';
	newSentence[strlen(sentence)+1] = '!';
	return newSentence;
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
