/**
 * @file Event.cpp
 * @author MP-Team DECSAI
 * @warning Update the class. Methods print and read To be implemented by students 
 * 
 */
#include <fstream>
#include <string>
#include "Event.h"
using namespace std;


Event::Event() {
    initDefault();
}

void Event::initDefault() {
    set(EVENT_DEFAULT);
}

Event::Event(const string & line) {
    set(line);
}

DateTime Event::getDateTime() const{
    return _dateTime;
}

string Event::getType() const{
    return _type;
}

string Event::getProductID() const{
    return _prod_id;
}

string Event::getCategoryID() const{
    return _cat_id;
}

string Event::getCategoryCode() const{
    return _cat_cod;
}

string Event::getBrand() const{
    return _brand;
}

double Event::getPrice() const{
    return _price;
}

string Event::getUserID() const{
    return _user_id;
}

string Event::getSession() const{
    return _session;
}

void Event::setDateTime(const string & time) {
    _dateTime.set(time);
}

void Event::setType(const std::string & type) {
    bool valido = false;
    for (int i=0; i<sizeof(VALID_TYPES)/sizeof(string) && valido == false; i++){
        if (type == VALID_TYPES[i]) 
            valido = true;
    }
    
    if (valido)
        _type = type;
    else
        _type = VALID_TYPES[0];
}

void Event::setProductID(const std::string & prod_id) {
    if (prod_id == "")
        _prod_id = EMPTY_FIELD;
    else
        _prod_id = prod_id;
}

void Event::setCategoryID(const std::string & cat_id) {
    _cat_id = cat_id;
}

void Event::setCategoryCode(const std::string & cat_cod) {
    _cat_cod = cat_cod;
}

void Event::setBrand(const std::string & brand) {
     _brand = brand;
}

void Event::setPrice(double price) {
    if (price < 0)
        _price = -1.0;
    else
        _price = price;
}

void Event::convPrice(const std::string & price){
    try {
        setPrice(stod(price));
    } catch (...) {
        setPrice(-1.0);
    }
}

void Event::setUserID(const std::string & user_id) {
    if (user_id == "")
        _user_id = EMPTY_FIELD;
    else
        _user_id = user_id;
}

void Event::setSession(const std::string & session) {
    if (session == "")
        _session = EMPTY_FIELD;
    else
        _session = session;
}

void Event::set(const std::string & line) {
    int a = line.find(','), b=0;
    
    setDateTime(line.substr(0, a-1));
    
    b = line.find(',', a+1);
    setType(line.substr((a+1), b-a-1));
    
    a = line.find(',', b+1);
    setProductID(line.substr(b+1, a-b-1));
    
    b = line.find(',', a+1);
    setCategoryID(line.substr(a+1, b-a-1));
    
    a = line.find(',', b+1);
    setCategoryCode(line.substr(b+1, a-b-1));

    b = line.find(',', a+1);
    setBrand(line.substr(a+1, b-a-1));

    a = line.find(',', b+1);
    convPrice(line.substr(b+1, a-b-1));

    b = line.find(',', a+1);
    setUserID(line.substr(a+1, b-a-1));

    a = line.find(',', b+1);
    setSession(line.substr(b+1, a-b-1));
}

bool Event::isEmpty() const{
    return (_prod_id == EMPTY_FIELD || _user_id == EMPTY_FIELD || _session == EMPTY_FIELD || _dateTime.to_string() == DATETIME_DEFAULT || _price < 0);
}

string Event::to_string() const {
    string salida;
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
//    salida = salida +"," + DAYNAME[this->getDateTime().weekDay()];
    return salida;
}

string Event::getField(const string & field) const {
    string return_string = EMPTY_FIELD;
    if (field == "DateTime")
        return_string = _dateTime.to_string();
    
    if (field == "Type")
        return_string = _type;
    
    if (field == "ProductID")
        return_string = _prod_id;
    
    if (field == "CategoryID")
        return_string = _cat_id;
    
    if (field == "CategoryCode")
        return_string = _cat_cod;
    
    if (field == "Brand")
        return_string = _brand;
    
    if (field == "Price")
        return_string = std::to_string(getPrice());
    
    if (field == "UserID")
        return_string = _user_id;
    
    if (field == "Session")
        return_string = _session;    
    
    return return_string;
}

void Event::write(ostream &os) const{
    os << this->to_string();
}

void Event::read(istream &is) {
    string aux;
    getline(is,aux);
    set(aux);
}