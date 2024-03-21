    /* 
 * File:   Pair.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students
 */
#include <string>
#include <cstdlib>
#include "Pair.h"

using namespace std;

Pair NULL_PAIR = Pair();

Pair::Pair(){
    _key = EMPTY_FIELD;
    _pos = -1;
}

bool Pair::isEmpty() const {
    return _key == EMPTY_FIELD || _key == "" || _pos == -1;
}

Pair::Pair(const std::string & key, int pos) {
    set(key, pos);
}

const std::string & Pair::getKey() const {
    return _key;
}

const int Pair::getPos()const {
    return _pos;
}

void Pair::setKey(const std::string & key) {
    _key = key;
}

void Pair::setPos(int pos) {
    _pos = pos;
}

void Pair::set(const std::string & key, int pos) {
    if (key != "" || pos >= 0) {
        _key = key;
        _pos = pos;
    }
    else
        initDefault();
}

std::string Pair::to_string() const { 
    string pair_index;
    pair_index += _key;
    pair_index += " ";
    pair_index += std::to_string(_pos);
    
    return pair_index;
}

void Pair::initDefault(){
    Pair();
}

bool equalKey(const Pair & left, const Pair & right) {
    return left.getKey() == right.getKey();
}
