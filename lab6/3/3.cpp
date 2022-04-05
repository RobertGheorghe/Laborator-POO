#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class IoBase {
private:
public:
    virtual istream& read(istream& is) { 
        return is;    
    }
    virtual ostream& write(ostream& os) const {
        return os;     
    }
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }
    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

class Employee : public IoBase {
protected:
    int salariubaza,experienta;
    string nume;
    friend void back(int, vector<Employee*>);
public:
    Employee() : salariubaza(0), experienta(0),nume("") {};
    Employee(int salariubaza, int experienta, const string nume) : salariubaza(salariubaza), experienta(experienta), nume(nume) {};
    istream &read(istream &is) {
        IoBase::read(is);
        cout << "Nume angajat: ";
        is >> nume;
        cout << "Salariu de baza: ";
        is >> salariubaza; 
        cout << "Ani de exeperienta: ";
        is >> experienta;
        return is;
    }
    ostream &write(ostream &os) const {
        IoBase::write(os);
        cout << "Angajatul " << nume << " are salariul de baza de " << salariubaza << " lei si " << experienta << " ani de experienta. \n";
        return os;
    }
    friend bool areTeams(vector<Employee*>);
    friend int numberTeams(vector<Employee*>);
};

class FullstackProgrammer:public Employee {
protected:
    int extraore;
public:
    FullstackProgrammer(): Employee(), extraore(0) {};
    FullstackProgrammer(int salariubaza, int experienta, const string nume, int extraore) : Employee(salariubaza, experienta, nume), extraore(extraore) {};
    istream& read(istream& is) override{
        Employee::read(is);
        cout << "Numarul de ore extra: ";
        is >> extraore;
        return is;
    }
    ostream& write(ostream& os) const override{
        Employee::write(os);
        cout << "Este Fullstack Progammer si are "<< extraore<<" ore lucrate extra. \n\n";
        return os;
    }
    double SalariuNet() {
        return salariubaza / 2 + extraore * 2.5 * salariubaza / 160;
    }
    friend bool areTeams(vector<Employee*>);
    friend int numberTeams(vector<Employee*>);
};

class DevOpsProgrammer:public Employee {
protected:
    int extraore;
public:
    DevOpsProgrammer() :Employee(), extraore(0) {};
    DevOpsProgrammer(int salariubaza, int experienta, const string nume, int extraore) : Employee(salariubaza, experienta, nume), extraore(extraore) {};
    istream& read(istream& is) override{
        Employee::read(is);
        cout << "Numarul de ore extra: ";
        is >> extraore;
        return is;
    }
    ostream& write(ostream& os) const override {
        Employee::write(os);
        cout << "Este DevOps Progammer si are "<<extraore<< " ore lucrate extra. \n\n";
        return os;
    }
    double SalariuNet() {
        return salariubaza / 2 + extraore* 2.5*salariubaza/160;
    }
    friend bool areTeams(vector<Employee*>);
    friend int numberTeams(vector<Employee*>);
};

class Manager : public Employee {
public:
    Manager() :Employee() {};
    Manager(int salariubaza, int experienta, const string nume) : Employee(salariubaza, experienta, nume) {};
    istream& read(istream& is) override {
        Employee::read(is);
        return is;
    }
    ostream& write(ostream& os) const override{
        Employee::write(os);
        cout << "Este Manager. \n\n";
        return os;
    }
    double SalariuNet() {
        return salariubaza / 2;
    }
    friend bool areTeams(vector<Employee*>);
    friend int numberTeams(vector<Employee*>);
};

bool areTeams(vector<Employee*> angajati) {
    int v[3] = { 0 }, v1[3] = { 0 };
    for (auto* angajat : angajati) {
        auto* asFullstack = dynamic_cast<FullstackProgrammer*>(angajat);
        auto* asDevOps = dynamic_cast<DevOpsProgrammer*>(angajat);
        auto* asManager = dynamic_cast<Manager*>(angajat);
        if (asFullstack)
        {
            v[0]++;
            if (asFullstack->experienta >= 2)
                v1[0]++;
        }
        else if(asDevOps)
        {
            v[1]++;
            if (asDevOps->experienta >= 2)
                v1[1]++;
        }
        else
        {
            v[2]++;
            if (asManager->experienta >= 2)
                v1[2]++;
        }
    }
    for (int i = 0; i < 3; i++)
        if (v[i] == 0)
            return false;
    for (int i = 0; i < 2; i++)
        if (v1[i])
            return true;
}

int numberTeams(vector<Employee*> angajati) {
    int v[3] = { 0 }, v1[3] = { 0 }, nr = 0;
    for (auto* angajat : angajati) {
        auto* asFullstack = dynamic_cast<FullstackProgrammer*>(angajat);
        auto* asDevOps = dynamic_cast<DevOpsProgrammer*>(angajat);
        auto* asManager = dynamic_cast<Manager*>(angajat);
        if (asFullstack)
        {
            v[0]++;
            if (asFullstack->experienta >= 2)
                v1[0]++;
            if (v[1] && v[2] && (v1[0] || v1[1]) && !nr)
                nr = 1;
            else
                if (nr)
                    nr += (v[0] - int(asFullstack->experienta < 2));
        }
        else if (asDevOps)
        {
            v[1]++;
            if (asDevOps->experienta >= 2)
                v1[1]++;
            if (v[2] && v[0] && (v1[0] || v1[1]) && !nr)
                nr = 1;
            else
                if (nr)
                    nr += (v[1] - int(asDevOps->experienta < 2));
        }
        else
        {
            v[2]++;
            if (asManager->experienta >= 2)
                v1[2]++;
            if (v[1] && v[0] && (v1[0] || v1[1]) && !nr)
                nr = 1;
            else
                if (nr)
                    nr += (v[2] - int(asManager->experienta < 2));
        }
    }
    return nr;
}

int main()
{
    /*FullstackProgrammer b;
    DevOpsProgrammer c;
    Manager d;
    cin >> b >> c >> d;
    cout << b << c << d;
    cout << b.SalariuNet() << endl << c.SalariuNet() << endl << d.SalariuNet();*/
    int n,i,a;
    vector<Employee*> v;
    cout << "n= ";
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cout << "a= ";
        cin >> a;
        if (!a) {
            FullstackProgrammer x;
            cin >> x;
            v.push_back(&x);
        }
        else if (a == 1) {
            DevOpsProgrammer y;
            cin >> y;
            v.push_back(&y);
        }
        else if (a == 2) {
            Manager z;
            cin >> z;
            v.push_back(&z);
        }
    }
    cout << areTeams(v)<<endl;
    cout << numberTeams(v)<<endl;
    return 0;
}

/*
4
0
robert
1500
2
2
1
andrei
2000
3
2
2
mihai
2500
2
1
daniela
2000
1
3
*/
