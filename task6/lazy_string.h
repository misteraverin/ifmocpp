/*
 * Averin Maxim 21.05.2016
 */
#ifndef LIB_LAZY_STRING
#define LIB_LAZY_STRING


#include <iostream>
#include <memory>
#include <string>



// class lazy_string implements copy-on-write string
class lazy_string{
    struct mychar{
        friend class lazy_string;
        operator char () const;
        mychar &operator = (char);
        private:
            mychar(lazy_string *ls, size_t index);
            const size_t index;
            lazy_string* const ls;
    };
    private:
        size_t begin, len;
        std::shared_ptr<std::string> str_cur;
        lazy_string(std::shared_ptr<std::string>str, size_t begin, size_t len);
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


    // for edition the element
    mychar at(size_t pos);
    mychar operator[](size_t pos);
    //@return character at the position in range [0..len - 1];
    char at(size_t pos) const;
    //@return character at the postion lazy_strin[pos] in range [0...len - 1]
    char operator[](size_t pos) const;

    // @return length of the lazy_string
    size_t  get_len() const;
    // @return length of the lazy_string
    size_t size() const;
};
#endif
