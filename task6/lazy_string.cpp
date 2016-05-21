#include <iostream>
#include <stdexcept>
#include "lazy_string.h"



size_t  lazy_string::get_len() const{
    return this->len;
}


size_t  lazy_string::size() const{
    return this->len;
}


std::istream &operator>>(std::istream &is, lazy_string &ls){
    auto cur = std::make_shared<std::string>();
    is >> *cur;
    ls.str_cur = cur;
    ls.begin = 0;
    ls.len = (*cur).size();
    return is;
}


std::ostream &operator<<(std::ostream &os, lazy_string &ls) {
    for (size_t i = 0; i < ls.size(); i++)
        os << ls[i];
    return os;
}

lazy_string::operator std::string() const{
    return str_cur->substr(begin, len);
};


lazy_string::lazy_string() {
    this->str_cur = std::make_shared<std::string>("");
    begin = 0;
    len = 0;
};


lazy_string::lazy_string(const std::string &str) {
    this->str_cur = std::make_shared<std::string>(str);
    begin = 0;
    len = str.size();
};


char lazy_string::at(size_t pos) const {
    return (*this)[begin + pos];
}


char lazy_string::operator[](size_t pos) const {
    return (*this)[begin + pos];
}


lazy_string::mychar lazy_string::at(size_t pos) {
    return mychar(this, pos);
}


lazy_string::mychar lazy_string::operator[](size_t pos) {
    return mychar(this, pos);
}

lazy_string::lazy_string(std::shared_ptr<std::string> str, size_t begin, size_t len) {
    this->str_cur = str;
    this->begin = begin;
    this->len = len;
};

lazy_string lazy_string::substr(size_t pos, size_t len) {
    size_t temp;
    if(pos + len > len)
        temp = len - pos + 1;
    else
        temp = len;
    return lazy_string(str_cur, begin + pos, temp);
}


lazy_string::mychar::operator char() const {
    return (*ls->str_cur)[ls->begin + index];
}


lazy_string::mychar &lazy_string::mychar::operator=(char c) {
    if (ls->str_cur.use_count() >= 2) {
        ls->begin = 0;
        ls->str_cur = std::make_shared<std::string>(ls->str_cur->substr(ls->begin, ls->len));
    }
    (*ls->str_cur)[ls->begin + index] = c;
    return *this;
}

lazy_string::mychar::mychar(lazy_string *ls, size_t index) : ls(ls), index(index) { };









