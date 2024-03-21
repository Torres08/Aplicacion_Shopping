/* 
 * File:   Index.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include "Index.h"

using namespace std;

void Index::copy_to(Pair *dest){
    for (int i = 0; i < _nEntries; i++)
        dest[i] = at(i);
}

void Index::copy(const Index &orig){
    for (int i=0; i < orig._nEntries; i++)
        add(orig.at(i));
}

Index::Index(int onBrand) {
    _nEntries = 0;
    _maxEntries = 0;
    _onBrand = onBrand;
    _entries = nullptr;
}

Index::Index(const Index & orig){
    _nEntries = 0;
    _maxEntries = 0;
    _onBrand = orig._onBrand;
    _entries = nullptr;
    copy(orig);
}

void Index::setIOnWhich(int val) {
    _onBrand = val;
}

void Index::reallocate(int size) {
    Pair *aux = nullptr;
    aux = new Pair[size];
    copy_to(aux);
    deallocate();
    _entries = aux;
}

void Index::deallocate() {
    if (_entries != nullptr){
        delete[]_entries;
        _entries = nullptr;
    }   
}

int Index::size() const {
    return _nEntries;
}

void Index::clear() {
    _nEntries = 0;
    _maxEntries = 0;
    deallocate();
}

int Index::getIOnWhich() const {
    return _onBrand;
}

int Index::add(const Pair & pair) {
    if (!pair.isEmpty()){
        if (_nEntries >= _maxEntries){
            _maxEntries = _maxEntries*2+1;
            reallocate(_maxEntries);
        }
        int pos = upper_bound(pair.getKey());
        for (int i = _nEntries-1; i >= pos; i--){
            _entries[i+1] = _entries[i];
        }
        _entries[pos] = pair;
        _nEntries++;
        return 1;  
    } else 
        return 0;
}

int Index::add(const std::string &key){
    if (key!=""){
        Pair aux;
        aux.set(key,size());
        return add(aux);
    } else 
        return 0;
}

/**
 * @brief Build the index using the Brand o the userID as searching key
 * @param evSet origin
 */
void Index::build(const EventSet & evSet, int onBrand) {
    this->clear();
    string field;
    
    if (onBrand == 0)
        field = "UserID";
    if (onBrand == 1)
        field = "Brand";
    if (onBrand == 2)
        field = "Session";
    
    _onBrand = onBrand;
    Pair aux; 
    for (int i = 0; i < evSet.size(); i++){
        aux.set(evSet.at(i).getField(field), i);
        add(aux);
    }
}

/**
 * @brief Returns the position to the first element in the Index
 * which is not considered to go before key (i.e., either it is equivalent is the first one
 * or it goes after), look at the example.
 * @param key the searching key a string
 * example: // 10 20 30 30 40 50 60 70
 * low_bound(30) ....^
 * low_bound(35) ..........^
 * @return a position in the Index
 */

//la solucion propuesta está basada en la busqueda binaria pero con claves duplicadas

int Index::lower_bound(const string & key) const {  
    int pos = -1;
    bool found = false;
    int low = 0, upp = _nEntries - 1, center;
    while (low <= upp && !found) {
        center = (low + upp) / 2;
        if (_entries[center].getKey() == key) {
            found = true;
            for (pos = center; pos >= 0 && _entries[pos].getKey() == key; pos--)
                ; // pos goes down, increases until != key
            pos++; // The position we want to find is the first equal, the loop
            // places the pointer in the last different
        } else if (_entries[center].getKey() < key) low = center + 1;
        else upp = center - 1;
    }
    if (!found)
        pos = low;

    return pos;
    
}
//
/**
 * @brief Returns the position to the first element in the Index which is considered to go after val.
 * look at the example.
 * example: // 10 20 30 30 40 50 60 70
 * upper_bound(30) ........^
 * upper_bound(35) ........^
 * @param key the searching key a string
 * @return a position in the Index
 */

// OJO la solucion propuesta está basada en la busqueda binaria ADAPTADA  con claves duplicadas

int Index::upper_bound(const string & key) const { 
    int pos = -1;
    bool found = false;
    int low = 0, upp = _nEntries - 1, center;
    while (low <= upp && !found) {
        center = (low + upp) / 2;
        if (_entries[center].getKey() == key) {
            found = true;
            for (pos = center; pos < _nEntries && _entries[pos].getKey() == key; pos++)
                ; // pos goes down, increases until != key
        } else if (_entries[center].getKey() < key) low = center + 1;
        else upp = center - 1;
    }

    if (!found) {
        pos = low;
    }

    return pos;
}

const Pair & Index::at(int pos) const {
    return _entries[pos];
}

Pair & Index::at(int pos) {
    return _entries[pos];
}

void Index::print()const {
    for (int i = 0; i < this->size(); i++)
        cout << at(i).to_string() << endl;
}

Index & Index::operator=(const Index & one) {
    _nEntries = 0;
    _maxEntries = 0;
    _onBrand = one._onBrand;
    copy(one);
    return *this;
}

Index::~Index() {
    deallocate();
}

// external functions

Event getEvent(const EventSet & evSet, const Index & indx, int pos) {
    return evSet.at(indx.at(pos).getPos());
}

void write(ofstream &os, const EventSet & evSet, const Index & indx) {
    for (int i = 0; i < indx.size(); i++){
        getEvent(evSet, indx, i).write(os);
        os << endl;
    }
}
// external functions

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value) {
    Index filterIndex;
    
    if ((indx.getIOnWhich() == 0 && field == "UserID") || (indx.getIOnWhich() == 1 && field == "Brand") || (indx.getIOnWhich() == 2 && field == "Session")) {
        for (int i = indx.lower_bound(value); i < indx.upper_bound(value); i++){
            filterIndex.add(indx.at(i));
        }
    } else if (field == "DateTime") {
        DateTime aux;
        aux.set(value);
        for (int i = 0; i < indx.size(); i++){
            if (getEvent(evSet, indx, i).getDateTime().sameDay(aux)){
                filterIndex.add(indx.at(i));
            }
        }
    } else {
        for (int i = 0; i < indx.size(); i++){
            if (getEvent(evSet, indx, i).getField(field) == value)
                filterIndex.add(indx.at(i));
        }
    }
    return filterIndex;
}

float sumPrice(const EventSet & evSet, const Index & indx) {
    float sum = 0;
    for (int i = 0; i < indx.size(); i++){
        sum += getEvent(evSet, indx, i).getPrice();
    }
    return sum;
}