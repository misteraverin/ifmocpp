/*
 * Averin Maxim 21.05.2016
 */
#ifndef LIB_LAZY_STRING
#define LIB_LAZY_STRING


#include <iostream>
#include <memory>
#include <cstring>


// class lazy_string implements copy-on-write string
class lazy_string{
    private:
        size_t begin, len;
        std::string current;
        lazy_string(const lazy_string &cur, size_t begin, size_t len);
    public:

    // @return  std::string, which contains characters from lazy_string
    operator std::string() const;
    //constructors, which creates 1) empty lazy_string 2) lazy_string with std::string
    lazy_string();
    lazy_string(const std::string &str);


    // get substring str[from...len - 1]
    lazy_string substr(size_t position, size_t length);

    // get the characters from input to lazy_string
    friend std::istream &operator>>(std::istream &is, lazy_string &ls);

    // insert lazy_string into ostream
    friend std::ostream &operator<<(std::ostream &os, lazy_string &ls);

    //@return character at the position in range [0..len - 1];
    const char& at(size_t pos) const;

    //@return character at the postion lazy_strin[pos] in range [0...len - 1]
    const char& operator[](size_t pos) const;


    // @return length of the lazy_string
    size_t  get_len() const;
    // @return length of the lazy_string
    size_t size() const;
};
#endif
