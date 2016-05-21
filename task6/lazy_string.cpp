#include <iostream>
#include <stdexcept>
#include "lazy_string.h"


lazy_string::lazy_string(){
    (*this).current= std::string();
    (*this).begin = 0;
    (*this).len = 0;
}


lazy_string::lazy_string(const std::string &str) {
    (*this).current = str;
    (*this).begin = 0;
    (*this).len = size_t(str.size());
}


lazy_string::lazy_string(const lazy_string &ls, size_t start, size_t size) {
    this->current = ls.current;
    this->begin = start;
    this->len = size;
}


size_t  lazy_string::get_len() const{
    return this->len;
}


size_t  lazy_string::size() const{
    return this->len;
}


std::istream &operator>>(std::istream &is, lazy_string &ls){
    is >> ls.current;
    ls.begin = 0;
    ls.len = ls.get_len();
    return is;
}


const char& lazy_string::at(size_t pos) const{
    return this->current[(this->begin) + pos];
}


//@return character at the postion lazy_strin[pos] in range [0...len - 1]
const char& lazy_string::operator[](size_t pos) const{
    if(pos >= this->len){
        throw std::out_of_range ("index out of range");
    }
    return at(pos);
}

lazy_string lazy_string::substr(size_t position, size_t length){
    if(position > size())
        throw std::out_of_range ("index out of range");
    length = std::min(length, this->len -begin);
    return lazy_string(this->current, this->begin + position, length);
}

std::ostream &operator<<(std::ostream &os, lazy_string &ls) {
    for (size_t i = 0; i < ls.get_len(); i++)
        os << ls[i];
    return os;
}








