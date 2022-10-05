//
// Created by davew on 10/4/22.
//

#include "String.h"
#include <cstring>  // Use C-style string functions in C++ code
#include <logic.h>   // HaverfordCS "precondition", "postcondition", "assert"

// Any well-formed String should return True from this;
// a result of False from repInv means a problem in class String
// (or a memory allocation/access problem, of course).
bool String::repInv() const {
    return strlen(this->letters) <= maxSize;
}

String::String(const char *init) {
    if (strlen(init) > maxSize)
        throw "Oversize initializer, can't create String";
    strcpy(this->letters, init);
    this->letters[maxSize] = '\0';  // put a NUL character there ... ToDo: discuss whether this is important
    postcondition(repInv());        // the end of a constructor should guarantee a well-formed object
}

String::String(const String &init) {
    precondition(init.repInv());  // at the start of a method, existing strings should be well-formed
    strcpy(this->letters, init.letters);
    postcondition(repInv());
}

String::String() {
    this->letters[0] = '\0';  // or strcpy(this->letters, ""), if you like
    postcondition(repInv());
}

String::~String() {
    precondition(this->repInv());     // one last chance to confirm we didn't ever make a malformed string
}

int String::length() const {
    precondition(this->repInv());
    return strlen(this->letters);
}
String &String::operator=(const String &rhs) {
    precondition(this->repInv() and rhs.repInv());  // left and right _both_ already exist, unlike in a constructor
    if (this != &rhs) {  // if we have different objects
        strcpy(this->letters, rhs.letters);
    }
    postcondition(this->repInv());
    return *this;
}

String operator+(const String &lhs, const String &rhs) {
    precondition(lhs.repInv() and rhs.repInv());  // left and right _both_ already exist
    if (strlen(lhs.letters) + strlen(rhs.letters) > String::maxSize)
        throw "can't concatenate, result too big :-(";
    String result;
    strcpy(result.letters, lhs.letters);
    strcat(result.letters, rhs.letters);  // strcat puts stuff where the NUL was, adds a NUL
    result.letters[String::maxSize] = '\0';  // put a NUL character there ... ToDo: discuss whether this is important

    postcondition(result.repInv());        // the end of a constructor should guarantee a well-formed object
    return result;
}

const char &String::operator[](int index) const {
    precondition(this->repInv());     // one last chance to confirm we didn't ever make a malformed string
    if (index<0 or index>=strlen(this->letters))
        throw "Illegal string index";

    return this->letters[index];
}

char &String::operator[](int index) {
    precondition(this->repInv());     // one last chance to confirm we didn't ever make a malformed string
    if (index<0 or index>=strlen(this->letters))
        throw "Illegal string index";

    return this->letters[index];
}

// this has to be a friend to get the data
std::ostream &operator<<(std::ostream &any_ostream, const String &printMe)             // output operation
{
    return any_ostream << printMe.letters;
}


void String_Demo() {
    String firstname = String("dave");
    firstname[0]='D';  // char-type object with ' rather than "
    String lastname  = String("Wonnacott");

    String name = firstname + String(" ") + lastname;  // currently no implicit casting
    std::cout << "Hello " << name << std::endl;
}
