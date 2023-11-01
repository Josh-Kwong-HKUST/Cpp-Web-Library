#include "../include/Buffer.h"
#include <iostream>

Buffer::Buffer(){}

Buffer::~Buffer(){}

void Buffer::append(const char* _str, int _size){
    buf.append(_str, _size);
}

ssize_t Buffer::size(){
    return buf.size();
}

const char* Buffer::toStr(){
    return buf.c_str();
}

void Buffer::clear(){
    buf.clear();
}

void Buffer::getline(){
    this->clear();
    std::getline(std::cin, buf);
}

void Buffer::setBuf(const char* _buf){
    this->clear();
    buf.append(_buf);
}