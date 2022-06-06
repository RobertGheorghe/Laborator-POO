#ifndef POO_IOBASE_H
#define POO_IOBASE_H

#include <iostream>
#include <vector>
using namespace std;

class IoBase {
private:
public:
    // metoda citire
    virtual istream &read(istream &is) { // nu este nevoie de obiectul citit, pt ca avem this
        return is; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // metoda scriere
    virtual ostream &write(ostream &os) const { // nu este nevoie de obiectul citit, pt ca avem this
        return os; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // ...
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

template <class T>
friend istream& operator>>(istream& is, vector<T> v) {
    for (unsigned i = 0; i < v.size(); i++)
        is >> v[i];
    return is;
}

template <class T>
friend ostream& operator<<(ostream& os, vector<T> v) {
    for (unsigned i = 0; i < v.size(); i++)
        os << v[i] << "\n";
    os << "\n";
    return os;
}

#endif //POO_IOBASE_H
