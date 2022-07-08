//
// Created by davew on 10/12/21.
//

#ifndef A_CS251_STARTER_STRINGEXAMPLES_H
#define A_CS251_STARTER_STRINGEXAMPLES_H

#include <string>

std::string withExclamation(const std::string &sentence); // use "const" and "&" to avoid making a copy of the sentence, but not changing it
void   addExclamation(std::string &sentence);             // change "sentence", in this one, and return nothing
char *withExclamationClassic(char *sentence);             // old-school C version of withExclamation


int countXs(const std::string &s);                        // count the X's


void strcmpExamples();

#endif //A_CS251_STARTER_STRINGEXAMPLES_H
