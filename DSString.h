//
// Created by Mark Fontenot on 6/2/2021.
//

#ifndef PA01_SENTIMENT_DSSTRING_H
#define PA01_SENTIMENT_DSSTRING_H
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
class DSString{

private:
    /**
     *  You will need to add some private data members here.
     *  This is up to your discretion.  However, we **strongly**
     *  encourage you to implement your string class as a wrapper
     *  for typical null-terminated c-strings.  In doing this, you
     *  may use c-sting functions in the methods in this class such
     *  as:
     *    * strlen(...)
     *    * strcpy(...)
     *    * strcmp(...)
     *    * strncpy(...)
     *    * strcat(...)
     *    * strncat(...)
     *
     *    A quick google search will return plenty of references on
     *    the c-string functions.
     **/
     char* s; // C-string
     // C-strinng helper functions
     int strlen(const char* input);
     char* strcpy(char* destination, const char* source);
     int strcmp(const char* str1, const char* str2) const;
     char* strncpy(char* destination, const char* source, int num);
     char* strcat(char* destination, char* source);
     char* strncat(char* destination, const char* source, int num);
     // DSstring helper functions
     void toUpper();
     void toLower();
     void toAlpha();

public:

    /**
     * Constructors and destructor
     *
     * Make sure you do proper memory management.
     **/
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();

    /**
     * Overloaded Assignment Operators
     */
    DSString& operator= (const char*);
    DSString& operator= (const DSString&);

    /**
     * Overloaded non-modifying string concat
     * @return
     */
    DSString operator+ (const DSString&);

    /**
     * Standard relational operators.  Feel free to add additional.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a DSString object
     *    one that takes a null-terminated c-string
     *
     **/

    bool operator== (const char*) const;
    bool operator== (const DSString&) const;
    bool operator> (const DSString&) const;
    bool operator> (const char*) const;
    bool operator< (const DSString&) const; // for using map
    bool operator< (const char* ) const;

    /**
     * Subscript operator to access a particular character of a DSString object
     * @return the character requested by reference
     */
    char& operator[] (const int);

    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    int getLength();

    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString substring(int start, int numChars);

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    char* c_str() const;

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream&, const DSString&);

    int find(DSString& ); // find function that looks for a particular substring passed as an argument within an invoking "superstring"
    //You are free to add more functionality to the class.  For example,
    //you may want to add a find(...) function that will search for a
    //string within a string.  (just an example)
    //
    //Further - you will be able to update and modify this class as the
    //semester progresses.
    vector<DSString> tokenize(char delimeter); // tokenize function



};



#endif //PA01_SENTIMENT_DSSTRING_H
