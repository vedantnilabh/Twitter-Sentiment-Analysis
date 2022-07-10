//
// Created by mark on 6/2/2021.
//

#include "DSString.h"

DSString::DSString() {
    s = nullptr;
}

DSString::DSString(const char* arg) {
    s = new char[strlen(arg) + 1]; // creating new Cstring on heap of correct length
    strcpy(s, arg); // deep copy
    s[strlen(arg)] = '\0'; // null terminator
}

DSString::DSString(const DSString& arg) {
    // see above
    s = new char[strlen(arg.s) + 1];
    strcpy(s, arg.s);
    s[strlen(arg.s)] = '\0';
}

DSString::~DSString() {
    // destructor deallocates memory on the heap
    delete[] s;
}

DSString &DSString::operator=(const char* arg) {
    delete[] s; // deallocate
    s = new char[strlen(arg) + 1];
    strcpy(s, arg);
    s[strlen(arg)] = '\0';
    return *this;
}

DSString &DSString::operator=(const DSString& arg) {
    if(this != &arg) { // check for self assignment
        delete[] s;
        s = new char[strlen(arg.s) + 1];
        strcpy(s, arg.s);
        s[strlen(arg.s)] = '\0';
    }
    return *this;
}

DSString DSString::operator+(const DSString& arg) {
    if(arg.s != nullptr && s != nullptr) {
        // new c string of correct length
        char* temp = new char[strlen(s) + strlen(arg.s) + 1];
        strcpy(temp, s);
        strcat(temp, arg.s);
        DSString ret_val;
        ret_val.s = temp;
        // returning new DSString
        return ret_val;
    }
    // checking edge cases if one of the underlying cStrings is nullptr
    else if(arg.s == nullptr) {
        char* temp = new char[strlen(s) + 1];
        strcpy(temp, s);
        DSString ret_val;
        ret_val.s = temp;
        return ret_val;
    }
    else if(s == nullptr) {
        char* temp = new char[strlen(arg.s) + 1];
        strcpy(temp, arg.s);
        DSString ret_val;
        ret_val.s = temp;
        return ret_val;
    }
    else{
        // empty DSString object if both are nullptr
        return DSString("");
    }

}

bool DSString::operator==(const char* arg) const {
    return strcmp(s, arg) == 0;
}

bool DSString::operator==(const DSString& arg) const {
    if(s == nullptr || arg.s == nullptr){
        // if one is nullptr, only equal if both are nullptr
        return(s == nullptr && arg.s == nullptr);
    }
    // same as before
    return strcmp(s, arg.s) == 0;
}

bool DSString::operator>(const DSString& arg) const {
    return strcmp(s, arg.s) > 0;
}

bool DSString::operator>(const char* arg) const {
    return strcmp(s, arg) > 0;
}

char &DSString::operator[](const int n) {
    if(strlen(s) > n) {
        return s[n];
    }
    // means we are trying to access memory out of Cstring range
    cout << "out of range error for subscript";
    exit(1);
}

int DSString::getLength() {
    if(s != nullptr){
        return strlen(s);
    }
    return 0;
}

DSString DSString::substring(int start, int numChars) {
    if(s == nullptr || numChars <= 0){
        // empty DSString object
        return DSString("");
    }
    char substr[numChars + 1];
    for(int i = 0; i < numChars; i++){
        // iterates from start and copies specified number of characters
        substr[i] = s[start + i];
    }
    // null term
    substr[numChars] = '\0';
    DSString ret_val(substr);
    // return DSString object
    return ret_val;

}



std::ostream &operator<<(ostream& o, const DSString& string) {
    // so we can print DSStrings
    o << string.c_str();
    return o;
}
// helper functions for C strings
int DSString::strlen(const char *input) {
    return std::strlen(input);
}

char *DSString::strcpy(char *destination, const char *source) {
    return std::strcpy(destination, source);
}

int DSString::strcmp(const char *str1, const char *str2) const {
    return std::strcmp(str1, str2);
}

char *DSString::strncpy(char *destination, const char *source, int num) {
    return std::strncpy(destination, source, num);
}

char *DSString::strcat(char *destination, char *source) {
    return std::strcat(destination, source);
}

char *DSString::strncat(char *destination, const char *source, int num) {
    return std::strncat(destination, source, num);
}


// find function that looks in invoking substring for superstring (DSString types)
int DSString::find(DSString& arg) {
    int index = -1; // if we don't find the substring, return -1
    if(strlen(s) < arg.getLength() || this->s == nullptr || arg.s == nullptr){
        return index;
    }
    for(int i = 0; i <= (strlen(s) - arg.getLength()); i++){ // difference is the number of times the substring can fit in the superstring numerically
        for(int j = 0; j < arg.getLength(); j++){
            if(arg.s[j] != s[i+j]){
                break; // can't be substring at this index
            }
            if(j == (arg.getLength() - 1)) { // reached end of superstring, meaning we return
                return i;
            }
        }

    }
    return index;

}
// returns underlying C-string
char* DSString::c_str() const{
    if(s != nullptr) {
        return s;
    }
    char* blank;
    blank[0] = '\0';
    return blank;
}

vector<DSString> DSString::tokenize(char delimeter){
    // vector we will return
    vector<DSString> tokenizedString;
    int start = 0;
    int stringLength = this->getLength();
    this->toLower(); // converts to lowercase
    for(int end = 0; end < stringLength; end++){ // iterates across length of string
        if(s[end] == delimeter) {
            // found delim, get substring
            int numChars = end - start;
            DSString token = this->substring(start, numChars);
            // push to vector
            tokenizedString.push_back(token);
            // update start
            start = end + 1;
        }
    }
    // edge case - end of string reached
    int numChars = stringLength - start;
    DSString token = this->substring(start, numChars);
    tokenizedString.push_back(token);
    // return vector of DSStrings
    return tokenizedString;
}
// to uppercase helper function
void DSString::toUpper() {
    if(s == nullptr) {
        return;
    }
    for(int i = 0; i < this->getLength(); i++){
        s[i] = std::toupper(s[i]);
    }
}
// to lowercase helper function
void DSString::toLower() {
    if(s == nullptr) {
        return;
    }
    for(int i = 0; i < this->getLength(); i++){
        s[i] = std::tolower(s[i]);
    }
}
// pruning all nonalpha characters
void DSString::toAlpha() {
    if(s == nullptr) {
        return;
    }
    char* new_s = new char[this->getLength() + 1];
    int newlen = 0;
    for(int i = 0; i < this->getLength(); i++){
        if(s[i] == ' '){
            new_s[newlen] = s[i];
            newlen++;
        }
        if(std::isalpha(s[i]) != 0){
            new_s[newlen] = s[i];
            newlen++;

        }
    }
    delete s;
    new_s[newlen] = '\0';
    this->s = new_s;

}

bool DSString::operator< (const DSString &arg) const {
    return strcmp(s, arg.s) < 0;
}

bool DSString::operator<(const char* arg) const {
    return strcmp(s, arg) < 0;
}


