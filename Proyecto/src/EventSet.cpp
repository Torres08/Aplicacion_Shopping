/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @warning Update the class. Methods read and write To be implemented by students 
     * remove rawFilters is not longer used, -> deprecated
 */




#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include "DateTime.h"
#include "EventSet.h"
#include <iostream>

using namespace std;

Event NULL_EVENT = Event();

/**
 * @brief Give string[] and a string, it searches for string within string[]
 * @param array     The set of strings to look for
 * @param n_array   The size of string[]
 * @param name      The string that is being seeked
 * @return          The position of the first occurrence of string within string[]
 *  -1 if the string does not belong to string[]
 */
int findString(const string array[], int n_array, const string & name) {
    bool string_found = false;
    int string_pos = -1;
    for (int i = 0; i < n_array && !string_found; i++) {
        if (array[i] == name) {
            string_pos = i;
            string_found = true;
        }
    }
    return string_pos;
}

void EventSet::copy_to(Event *dest) const{
    for (int i = 0; i < _nEvents; i++)
        dest[i] = at(i);
}

void EventSet::copy(const EventSet &orig){
    for (int i = 0; i<orig._nEvents; i++)
        add(orig.at(i));
}

void EventSet::reallocate(unsigned size){
    Event *aux = nullptr;
    aux = new Event[size];
    copy_to(aux);
    deallocate();
    _events = aux;
}

void EventSet::deallocate(){
    if (_events != nullptr){
        delete[]_events;
        _events = nullptr;
    }  
}

EventSet::EventSet() {
    _nEvents = 0;
    _capacity = 0;
    _events = nullptr;
}

EventSet::EventSet(const EventSet & orig){
    EventSet();
    copy(orig);
}


int EventSet::size() const {
    return _nEvents;
}

std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

void EventSet::clear() {
    _nEvents = 0;
    _capacity = 0;
    deallocate();
}

int EventSet::add(const Event & e) {
    if (_nEvents >= _capacity){
        _capacity = _capacity*2+1;
        reallocate(_capacity);
    }
    _events[_nEvents] = e;
        _nEvents++;
    return 1;
}

int EventSet::add(const std::string& line) {
    Event aux;
    aux.set(line);
    return add(aux);
}

const Event & EventSet::at(int pos) const {
    if (pos >=0 && pos < _nEvents)
        return _events[pos];
    else 
        return NULL_EVENT;
}

void EventSet::write(ofstream &os) const {
    for (int i = 0; i < _nEvents; i++) {
        at(i).write(os);
        os << endl;
    }
}

EventSet & EventSet::operator=(const EventSet & one) {
    _nEvents = 0;
    _capacity = 0;
    copy(one);   
    return *this;
}

EventSet::~EventSet(){
    deallocate();
}

bool EventSet::read(ifstream &is, int nelements) {
    bool success = true;
    Event one;
    clear();
    for (int i = 0; i < nelements && success; i++){
        one.read(is);
        if (is.eof())
            success = false;
        if (!one.isEmpty())
            success = add(one);
    }
    return success;  
}
// external functions

float sumPrice(const EventSet & evSet) {
    float sum = 0;
    float price;
    for (int i = 0; i < evSet.size(); i++) {
        price = evSet.at(i).getPrice();
        if (price > -1)
            sum += price;
    }
    return sum;
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    string value;
    n_values = 0;
    for (int i = 0; i < es.size(); i++){
        value = es.at(i).getField(field);
        if (field != "DateTime"){
            if (findString(values, n_values, value) == -1)
                values[n_values++] = value;
        } 
        else {
            DateTime dtValue(value);
            bool found = false;
            for (int j = 0; j < n_values && !found; j++){
                DateTime dtRecord;
                dtRecord.set(values[j]);
                if (dtRecord.sameDay(dtValue))
                    found=true;
            }
            if (!found){
                value[11] = value [12] = value[14] = value[15] = value[17] = value[18] = '0';
                values[n_values++] = value;
            }    
        }
    }
}
