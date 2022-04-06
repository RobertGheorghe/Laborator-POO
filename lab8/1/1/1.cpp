#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <iterator>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;
class Building : public IoBase {
protected:
    string nume, culoare;
public:
    Building() {}
    Building(string nume, string culoare) : nume(nume), culoare(culoare) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        cout << "Nume proprietar: ";
        is >> nume;
        cout << "Culoare cladire: ";
        is >> culoare;
        return is;
    }

    ostream& write(ostream& os) const override {
        IoBase::write(os);
        cout << "Numele proprietarului este " << nume;
        cout << ", iar culoarea cladirii este " << culoare << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Building& f) {
        return f.read(is);
    }

    friend ostream& operator<<(ostream& os, Building& f) {
        return f.write(os);
    }

    void operator=(Building b) {
        nume = b.nume;
        culoare = b.culoare;
    }
};

class House : public Building {
protected:
    int cntFloors;
public:
    House() {}
    House(string nume, string culoare, int cntFloors) : Building(nume, culoare), cntFloors(cntFloors) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Building::read(is);
        cout << "Numarul de etaje: ";
        is >> cntFloors;
        return is;
    }

    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Building::write(os);
        cout << "Casa are " << cntFloors << " etaje\n";
        return os;
    }

    friend istream& operator>>(istream& is, House& f) {
        return f.read(is);
    }

    friend ostream& operator<<(ostream& os, House& f) {
        return f.write(os);
    }
};

class Apartment : public Building {
protected:
    int floor;
public:
    Apartment() {}
    Apartment(string nume, string culoare, int floor) : Building(nume, culoare), floor(floor) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Building::read(is);
        cout << "Etaj apartament: ";
        is >> floor;
        return is;
    }

    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Building::write(os);
        cout << "Apartamentul se afla la etajul " << floor << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Apartment& f) {
        return f.read(is);
    }

    friend ostream& operator<<(ostream& os, Apartment& f) {
        return f.write(os);
    }
};

class BaseMenu {
public:
    virtual void listOptions() {}
    virtual void chooseOption() {}
    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
public:
    void listOptions() {
        cout << "Alege un numar de la 1 la 4.\n1. Adauga o noua cladire.\n2. Sterge o cladire existenta.\n3. Modifica o cladire.\n4. Iesire.\n";
    }
    void chooseOption() {
        int choice;
        cout << "Alegerea ta: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Se adauga cladirea...\n";
            break;
        case 2:
            cout << "Se sterge cladirea...\n";
            break;
        case 3:
            cout << "Se modifica cladirea...\n";
            break;
        case 4:
            cout << "La revedere!\n";
            exit(0);
        default:
            cout << "Input invalid.\n";
        }
    }
    void mainLoop() {
        while (true) {
            listOptions();
            chooseOption();
        }
    }
};

class MenuCRUD : public BaseMenu {
protected:
    vector<shared_ptr<Building>> v;
public:
    MenuCRUD() {}
    MenuCRUD(vector<shared_ptr<Building>> v) : v(v) {}
    void listOptions() {
        cout << "Alege un numar de la 1 la 4.\n1. Adauga o noua cladire.\n2. Afiseaza toate cladirile.\n3. Sterge una dintre cladirile existente.\n4. Modifica una dintre cladirile existente.\n";
    }
    void chooseOption() {
        int choice;
        cout << "Alegerea ta: ";
        cin >> choice;
        switch (choice) {
        case 1:
        {
            cout << "Introdu detaliile cladirii:\n";
            Building b;
            cin >> b;
            cout << "Se adauga cladirea...\n";
            v.push_back(make_shared<Building>(b));
            break;
        }
        case 2:
        {
            for (auto cladire : v) {
                cout << *cladire << "\n";
            }
            break;
        }
        case 3:
        {
            cout << "Introdu indexul cladirii pe care vrei sa o stergi: ";
            int x;
            cin >> x;
            v.erase(v.begin() + x);
            break;
        }
        case 4:
        {
            cout << "Introdu indexul cladirii pe care vrei sa o modifici: ";
            int x;
            cin >> x;
            Building b;
            cin >> b;
            v[x] = make_shared<Building>(b);
        }
        default:
            cout << "Input invalid.\n";
        }
    }
    void mainLoop() {
        while (true) {
            listOptions();
            chooseOption();
        }
    }
};

class OptionMenu : public BaseMenu {
private:
    int ok = 0;
protected:
    string nume;
public:
    OptionMenu() {}
    OptionMenu(string nume) : nume(nume) {}
    void listOptions() {
        if (nume == "Create")
            cout << "C++_Class\nText_file\n\n";
        else if (nume == "Open")
            cout << "Browse\n\n";
    }
    void chooseOption() {
        ok = 0;
        string choice;
        cin >> choice;
        if (nume == "Create")
            if (choice == "C++_Class")
            {
                ok = 1;
                cout << "Clasa creata cu succes!\n\n";
            }
            else if (choice == "Text_file")
            {
                ok = 1;
                cout << "Fisier text creat cu succes!\n\n";
            }
            else
                cout << "Invalid\n\n";
        else
            if (choice == "Browse")
            {
                cout << "Cautare...\n\n";
                ok = 1;
            }
            else
                cout << "Invalid\n\n";
    }
    void mainLoop() {
        while (true) {
            listOptions();
            chooseOption();
            if (!ok)
                break;
        }
    }
};

class SubMenu : public BaseMenu {
public:
    void listOptions() {
        cout << "Create\nOpen\nDelete_file\n\n";
    }
    void chooseOption() {
        string choice;
        cin >> choice;
        if (choice == "Create") {
            OptionMenu o("Create");
            o.mainLoop();
        }
        else if (choice == "Open") {
            OptionMenu o("Open");
            o.mainLoop();
        }
        else if (choice == "Delete_file") {
            cout << "Fisier sters:(\n\n";
        }
        else
            cout << "Invalid\n\n";
    }
    void mainLoop() {
        while (true) {
            listOptions();
            chooseOption();
        }
    }
};

class ComposedMenu : public BaseMenu {
public:
    void listOptions() {
        cout << "File\n\n";
    }
    void chooseOption() {
        string choice;
        cin >> choice;
        if (choice == "File")
        {
            SubMenu s;
            s.mainLoop();
        }
        else
            cout << "Invalid\n\n";
    }
    void mainLoop() {
        while (true) {
            listOptions();
            chooseOption();
        }
    }
};

shared_ptr<Building> transform() {
    int i;
    cout << "Pentru a citi o casa, introdu 0\nPentru a citi un apartament, introdu 1\n";
    cin >> i;
    while (i && i != 1)
    {
        cout << "Invalid, introdu doar 0 sau 1\n";
        cin >> i;
    }
    if (!i)
    {
        House h;
        cin >> h;
        return make_shared<Building>(h);
    }
    else
    {
        Apartment a;
        cin >> a;
        return make_shared<Building>(a);
    }
}


int main()
{
    // Exercitiul 1

    /*SimpleMenu menu;
    menu.mainLoop();*/

    // Exercitiul 2

    /*vector<shared_ptr<Building>> v;
    Building b;
    int n;
    cout << "n= ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> b;
        v.push_back(make_shared<Building>(b));
    }
    MenuCRUD menu(v);
    menu.mainLoop();
    cout << *transform();
    */

    /* Pentru exercitiul 3, pur si simplu mostenim clasa
    MenuCRUD si facem override pe metodele mainLoop(),
    chooseOption() si listOptions()
    */
    // Exercitiul 4

    /*ComposedMenu m;
    m.mainLoop();*/
    return 0;
}