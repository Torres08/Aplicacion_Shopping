/* 
 * File:   matrix.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */


#include "Matrix.h"
#include <fstream>
#include <assert.h>

using namespace std;

/**
 * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
 * It is assumed that org and dest have the memory properly allocated 
 * @param dest destination matrix
 * @param org  source matrix
 * @param nrows number of rows
 * @param ncols number of cols
 */
void copy(double **dest, double **org, size_t nrows, size_t ncols) {
    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){
            dest[i][j] = org[i][j];
        }
    }
}

/** 
 * @brief this method reserve memory to allocate a 2D matrix of size r x c.
 * @param r number of rows
 * @param c number of cols
 * @return the pointer to the memory block containing the data
 */
double ** allocate(size_t r, size_t c) {
    double **block;
    block = new double*[r];
    for (int i = 0; i < r; i++){
        block[i] = new double[c];
    }
    return block;
}

/**
 * @brief In this method, given an index idx it returns the key in the position i, 
 * such that i is the first position in the index such that idx.at(i).getPos()==p
 * @param idx the input index
 * @param p number of 
 * @return the key for first position i in the index such that idx.at(i).getPos()==p
 */
string labelWithValuePosInIndex(const Index & idx, size_t p) {
    string salida;
    bool enc = false;
    for (int i = 0; i < idx.size() && !enc; i++) {
        if (idx.at(i).getPos() == p) {
            salida = idx.at(i).getKey();
            enc = true;
        }
    }
    return salida;
}

void Matrix::deallocate() {
    if (_data != nullptr) {
        for (int i = 0; i < _nrows; i++) {
            delete[]_data[i];
        }
        delete[]_data;
        _data = nullptr;
    }
}

Matrix::Matrix() {
    _data = nullptr;
    _nrows = _ncols = 0;
}

void Matrix::setValues(double valor) {
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            _data[i][j] = valor;
        }
    }
}

Matrix::Matrix(size_t f, size_t c, double vdef) {
    _data = nullptr;
    resize(f, c, vdef);
}

Matrix::Matrix(const Matrix& orig) {
    _data = nullptr;
    *this = orig;
}

Matrix::Matrix(const std::string *rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value) {
    _data = nullptr;
    resize(rowLabels, nrows, colLabels, ncols, value);
}

std::string Matrix::labelAtRow(size_t row) const {
    return labelWithValuePosInIndex(_rowLabels, row);
}

std::string Matrix::labelAtCol(size_t col) const {
    return labelWithValuePosInIndex(_colLabels, col);
}

void Matrix::resize(size_t nrows, size_t ncols, double value) {
    deallocate();
    _data = allocate(_nrows = nrows, _ncols = ncols);
    setValues(value);
}

void Matrix::resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value) {
    resize(nrows, ncols, value);
    _rowLabels.clear();
    _colLabels.clear();
    for (int i = 0; i < _nrows; i++) {
        Pair p1(rowLabels[i], i);
        _rowLabels.add(p1);
    }
    for (int i = 0; i < _ncols; i++) {
        Pair p2(colLabels[i], i);
        _colLabels.add(p2);
    }
}

void Matrix::clear() {
    deallocate();   
    _nrows = _nrows = 0;
    _rowLabels.clear();
    _colLabels.clear();
      
}

Matrix::~Matrix() {
    deallocate();
}

double & Matrix::at(size_t f, size_t c) {
    return _data[f][c];
}

const double & Matrix::at(size_t f, size_t c) const {
    return _data[f][c];
}

double & Matrix::operator()(size_t f, size_t c) {
    return _data[f][c];
}

const double & Matrix::operator()(size_t f, size_t c) const {
    return _data[f][c];
}

int Matrix::rowIndexOf(const std::string & label) const {
    int pos = _rowLabels.size()-1;
    for (int i = 0; i < _rowLabels.size(); i++) {
        if (_rowLabels.at(i).getKey() == label) {
            pos = _rowLabels.at(i).getPos();
        }
    }
    return pos;
}

int Matrix::colIndexOf(const std::string & label) const {
    int pos = _colLabels.size()-1;
    for (int i = 0; i < _colLabels.size(); i++) {
        if (_colLabels.at(i).getKey() == label) {
            pos = _colLabels.at(i).getPos();
        }
    }
    return pos;
}

double & Matrix::at(const std::string & rowLabel, const std::string & colLabel) {
    return _data[rowIndexOf(rowLabel)][colIndexOf(colLabel)];
}

double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel) {
    return _data[rowIndexOf(rowLabel)][colIndexOf(colLabel)];
}

const double & Matrix::at(const std::string & rowLabel, const std::string & colLabel)const {
    return _data[rowIndexOf(rowLabel)][colIndexOf(colLabel)];
    }

const double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel)const {
    return _data[rowIndexOf(rowLabel)][colIndexOf(colLabel)];
}

ostream & operator<<(ostream & flujo, const Matrix& m) {
    flujo << m._nrows << " " << m._ncols << endl;
    if (m._rowLabels.size()>0){
        for (int i = 0; i < m._nrows; i++){
            for (int j = 0; j < m._rowLabels.size(); j++){
                if (m._rowLabels.at(j).getPos() == i)
                    flujo << m._rowLabels.at(j).getKey() << " ";
            }
        }
        flujo << endl;
    }
    if (m._colLabels.size()>0){
        for (int i = 0; i < m._ncols; i++){
            for (int j = 0; j < m._colLabels.size(); j++){
                if (m._colLabels.at(j).getPos() == i)
                    flujo << m._colLabels.at(j).getKey() << " ";
            }
        }
        flujo << endl;
    }
    for (int i = 0; i < m._nrows; i++){
        flujo << m.at(i,0);
        for (int j = 1; j < m._ncols; j++){
            flujo << " " << m.at(i,j);
        }
        flujo << endl;
    }
    return flujo;
}

Matrix & Matrix::operator=(const Matrix& m) {
    clear();
    _rowLabels = m._rowLabels;
    _colLabels = m._colLabels;
    resize(_nrows = m._nrows, _ncols = m._ncols);
    copy(_data, m._data, _nrows, _ncols);
    return *this;
}

void Matrix::setLabels(Index & idx, const string * labels, int nlabels) {
    idx.clear();
    int lb, ub;
    bool correct = true;
    for (int i = 0; i < nlabels && correct; i++) {
        lb = idx.lower_bound(labels[i]);
        ub = idx.upper_bound(labels[i]);
        if (lb == ub) { // it is NOT in the set
            idx.add(Pair(labels[i], i));
        } else {
            correct = false;
        }
    }
    if (!correct) idx.clear();
}

int Matrix::getLabels(const Index & idx, string * labels) const {
    if (idx.size() > 0) {
        for (int i = 0; i < idx.size(); i++) {
            for (int j = 0; j < idx.size(); j++){
                if (idx.at(j).getPos() == i)
                    labels[i] = idx.at(j).getKey();
            }
        }
    }
    return idx.size();
}

int Matrix::getRowLabels(string * labels) const {
    return getLabels(_rowLabels, labels);
}

int Matrix::getColLabels(string *labels) const {
    return getLabels(_colLabels, labels);
}

size_t Matrix::columns() const {
    return _ncols;
}

size_t Matrix::rows() const {
    return _nrows;
}

void Matrix::save(const string & nf) const {
    ofstream fsal(nf);
    if (fsal.is_open()) {
        fsal << "#matrix ";
        if (_rowLabels.size() == 0)
            fsal << "unlabeled" << endl;
        else fsal << "labeled" << endl;
        fsal << *this;
        fsal.close();
    } else cerr << "Fail creating " << nf << " file" << endl;
}

void Matrix::load(const string & nf) {
    ifstream fent(nf);
    string labeled, cad;
    clear();
    if (fent.is_open()) {
        fent >> cad >> labeled;
        fent >> _nrows >> _ncols;
        if (labeled == "labeled") {
            for (int i = 0; i < _nrows; i++) {
                fent >> cad;
                _rowLabels.add(Pair(cad, i));
            }
            for (int i = 0; i < _ncols; i++) {
                fent >> cad;
                _colLabels.add(Pair(cad, i));
            }
        }
        _data = allocate(_nrows, _ncols);
        for (int i = 0; i < _nrows; i++) {
            for (int j = 0; j < _ncols; j++) {
                fent >> _data[i][j];
            }
        }
        fent.close();
    } else cerr << "Fail reading " << nf << " file" << endl;
}

Matrix & Matrix::operator*=(double val) {
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            _data[i][j] *= val;
        }
    }
    return *this;
}

Matrix & Matrix::operator+=(double val) {
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            _data[i][j] += val;
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix & m) const {
    double aux;
    Matrix result;
    if (_ncols == m._nrows) {
        
        string *rowLabels = new string[m._nrows];
        string *colLabels = new string[m._ncols];
        getRowLabels(rowLabels);
        m.getColLabels(colLabels);
        result.resize(rowLabels, _nrows, colLabels, m._ncols, 0);
        
        delete[]rowLabels;
        delete[]colLabels;
        
        for (int row = 0; row < _nrows; row++) {
            for (int col = 0; col < m._ncols; col++){
                for (int inner = 0; inner < _ncols; inner++){
                    result._data[row][col] += _data[row][inner] * m._data[inner][col];
                    aux = result._data[row][col];
                }
            }
        }
    }
    return result;
}

Matrix Matrix::operator+(double val) const {
    Matrix result(*this);
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            result._data[i][j] += val;
        }
    }
    return result;
}

Matrix Matrix::operator*(double val) const {
    Matrix result(*this);
    for (int i = 0; i < _nrows; i++) {
        for (int j = 0; j < _ncols; j++) {
            result._data[i][j] *= val;
        }
    }
    return result;
}

Matrix operator+(double ival, const Matrix & dch) {
    Matrix prod(dch);
    for (int i = 0; i < dch._nrows; i++){
        for (int j = 0; j < dch._ncols; j++){
            prod(i,j) = ival + dch(i,j);
        }
    }
    return prod;
}

Matrix operator*(double ival, const Matrix & dch) {
    Matrix prod(dch);
    for (int i = 0; i < dch._nrows; i++){
        for (int j = 0; j < dch._ncols; j++){
            prod(i,j) = ival * dch(i,j);
        }
    }
    return prod;
}

Matrix & Matrix::normalize() {
    int sum;   
    for (int i = 0; i < _nrows; i++){
        sum = 0;
        for (int j = 0; j < _ncols; j++){
            sum += _data[i][j];
        }
        if (sum!=0){
            for (int j = 0; j < _ncols; j++){
                _data[i][j] /= sum;
            }
        } else {
            for (int j = 0; j < _ncols; j++){
                _data[i][j] = 1/(double)_ncols;
            }
        }
    }
}