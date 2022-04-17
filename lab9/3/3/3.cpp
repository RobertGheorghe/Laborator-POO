#include <iostream>
#include <memory>
#include "../util/IoBase.h"
#include "../util/functions.h"

using namespace std;

unsigned int i;

class Jucarii : public IoBase {
protected:
    string denumire,tip;
    double dimensiune;
public:
    Jucarii():dimensiune(0) {}
    Jucarii(string denumire, string tip, double dimensiune) :
        denumire(denumire), tip(tip), dimensiune(dimensiune){}
    istream& read(istream& is) override {
        IoBase::read(is);
        cout << "Denumirea jucariei: ";
        is >> denumire;
        cout << "Tipul jucariei: ";
        is >> tip;
        cout << "Dimensiune: ";
        is >> dimensiune;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        os << "Denumirea jucariei: " << denumire << endl 
            << "Tipul jucariei: " << tip << endl
            << "Dimensiune: " << dimensiune << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Jucarii& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Jucarii& f) {
        return f.write(os);
    }
};

class Clasice : virtual public Jucarii {
protected:
    string material, culoare;
public:
    Clasice() :Jucarii() {};
    Clasice(string denumire, string tip, double dimensiune, string material, string culoare) :
        Jucarii(denumire, tip, dimensiune), material(material), culoare(culoare) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Jucarii::read(is);
        cout << "Material: ";
        is >> material;
        cout << "Culoare: ";
        is >> culoare;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Jucarii::write(os);
        os << "Material: " << material << endl << "Culoare: " << culoare << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Clasice& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Clasice& f) {
        return f.write(os);
    }
};

class Educative : virtual public Jucarii {
protected:
    string abilitate;
public:
    Educative() :Jucarii(), abilitate("generala") {}
    Educative(string denumire, string tip, double dimensiune, string abilitate) :
        Jucarii(denumire, tip, dimensiune), abilitate(abilitate) {};
    istream& read(istream& is) override {
        IoBase::read(is);
        Jucarii::read(is);
        cout << "Abilitatea dezvoltata: ";
        is >> abilitate;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Jucarii::write(os);
        os << "Abilitatea dezvoltata: " << abilitate << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Educative& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Educative& f) {
        return f.write(os);
    }
};

class Electronice: virtual public Jucarii {
protected:
    unsigned int baterii;
public:
    Electronice() :Jucarii(), baterii(1) {}
    Electronice(string denumire, string tip, double dimensiune, unsigned int baterii) :
        Jucarii(denumire, tip, dimensiune), baterii(baterii) {};
    istream& read(istream& is) override {
        IoBase::read(is);
        Jucarii::read(is);
        cout << "Numarul de baterii: ";
        is >> baterii;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Jucarii::write(os);
        os << "Numarul de baterii: " << baterii << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Electronice& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Electronice& f) {
        return f.write(os);
    }
};

class Moderne : public Educative, public Electronice {
    string brand, model;
public:
    Moderne() :Educative(), Electronice(){}
    Moderne(string denumire, string tip, double dimensiune, string brand, string model) :
        Educative(denumire, tip, dimensiune, "generala"), Electronice(denumire,tip,dimensiune,1),brand(brand), model(model) {};
    istream& read(istream& is) override {
        IoBase::read(is);
        Jucarii::read(is);
        cout << "Brand: ";
        is >> brand;
        cout << "Model: ";
        is >> model;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Jucarii::write(os);
        os << "Abilitate dezvoltata: "<<abilitate<<endl<<"Numarul de baterii : " <<baterii<< endl<< "Brand: " << brand << endl << "Model: " << model << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Moderne& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Moderne& f) {
        return f.write(os);
    }
};

class Copii : public IoBase {
protected:
    unsigned int id, varsta, fapte_bune;
    string nume, prenume, adresa;
    vector<shared_ptr<Jucarii>> jucarii_primite;
public:
    Copii() : id(i++), varsta(0), fapte_bune(0) {};
    Copii(unsigned int varsta, unsigned int fapte_bune,
        string nume, string prenume, string adresa, vector<shared_ptr<Jucarii>> jucarii_primite) :
        id(i++), varsta(varsta), fapte_bune(fapte_bune), nume(nume),
        prenume(prenume), adresa(adresa),
        jucarii_primite(jucarii_primite) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Clasice clasice;
        Educative educative;
        Electronice electronice;
        Moderne moderne;
        string type;
        cout << "Nume: ";
        is >> nume;
        cout << "Prenume: ";
        is >> prenume;
        cout << "Varsta: ";
        is >> varsta;
        cout << "Numar de fapte bune: ";
        is >> fapte_bune;
        cout << "Jucarii primite:\n\n";
        for (int j = 0; j < fapte_bune; j++)
        {
            cout << "Clasice/Educative/Electronice/Moderne? ";
            is >> type;
            while (type != "Clasice" && type != "Educative" && type != "Electronice" && type != "Moderne")
            {
                cout << "Invalid\n";
                cout << "Clasice/Educative/Electronice/Moderne? ";
                is >> type;
            }
            if (type == "Clasice") 
            {
                is >> clasice;
                jucarii_primite.push_back(make_shared<Clasice>(clasice));
                cout << endl;
            }
            else if (type == "Educative")
            {
                is >> educative;
                jucarii_primite.push_back(make_shared<Educative>(educative));
                cout << endl;
            }
            else if (type == "Electronice") 
            {
                is >> electronice;
                jucarii_primite.push_back(make_shared<Electronice>(electronice));
                cout << endl;
            }
            else
            {
                is >> moderne;
                jucarii_primite.push_back(make_shared<Moderne>(moderne));
                cout << endl;
            }
        }
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        os << "ID: " << id << endl << "Nume:" << nume << endl
            << "Prenume: " << prenume << endl << "Varsta: " << varsta
            << endl << "Numar de fapte bune: " << fapte_bune << endl
            << "Jucarii primite:\n\n";
        for (auto jucarie: jucarii_primite)
            os << *jucarie << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Copii& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Copii& f) {
        return f.write(os);
    }
    friend void copilDupaNume(vector<shared_ptr<Copii>>, string nume);
    friend vector<shared_ptr<Copii>> sortCopii(vector<shared_ptr<Copii>>);
};

void copilDupaNume(vector<shared_ptr<Copii>> copii, string nume) {
    for (auto copil : copii)
        if (copil->nume == nume)
            cout << *copil << endl;
}

vector <shared_ptr<Copii>> sortCopii(vector<shared_ptr<Copii>> copii) {
    shared_ptr<Copii> aux;
    for (int j = 0; j < copii.size() - 1; j++)
        for (int k = j + 1; k < copii.size(); k++)
            if (copii[j]->fapte_bune > copii[k]->fapte_bune)
            {
                aux = copii[j];
                copii[j] = copii[k];
                copii[k] = aux;
            }
    return copii;
}

class Cuminti : public Copii {
    unsigned int dulciuri;
public:
    Cuminti() :Copii(), dulciuri(0) {}
    Cuminti(unsigned int varsta, unsigned int fapte_bune,
        string nume, string prenume, string adresa,
        vector<shared_ptr<Jucarii>> jucarii_primite, unsigned int dulciuri) :
        Copii(varsta, fapte_bune, nume, prenume, adresa, jucarii_primite),
        dulciuri(dulciuri) {
        while (fapte_bune < 10)
        {
            cout << "Copilul nu este cuminte, reintroduceti numarul de fapte bune: ";
            cin >> fapte_bune;
        }
        *this = Cuminti(varsta,fapte_bune,nume,prenume,adresa,jucarii_primite,dulciuri);
    }

    istream& read(istream& is) override {
        IoBase::read(is);
        IoBase::read(is);
        Clasice clasice;
        Educative educative;
        Electronice electronice;
        Moderne moderne;
        string type;
        cout << "Nume: ";
        is >> nume;
        cout << "Prenume: ";
        is >> prenume;
        cout << "Varsta: ";
        is >> varsta;
        cout << "Numar de fapte bune: ";
        is >> fapte_bune;
        while (fapte_bune < 10) {
            cout << "Numarul de fapte bune este invalid, reintroduceti-l: ";
            cin >> fapte_bune;
        }
        cout << "Jucarii primite:\n\n";
        for (int j = 0; j < fapte_bune; j++)
        {
            cout << "Clasice/Educative/Electronice/Moderne? ";
            is >> type;
            while (type != "Clasice" && type != "Educative" && type != "Electronice" && type != "Moderne")
            {
                cout << "Invalid\n";
                cout << "Clasice/Educative/Electronice/Moderne? ";
                is >> type;
            }
            if (type == "Clasice")
            {
                is >> clasice;
                jucarii_primite.push_back(make_shared<Clasice>(clasice));
                cout << endl;
            }
            else if (type == "Educative")
            {
                is >> educative;
                jucarii_primite.push_back(make_shared<Educative>(educative));
                cout << endl;
            }
            else if (type == "Electronice")
            {
                is >> electronice;
                jucarii_primite.push_back(make_shared<Electronice>(electronice));
                cout << endl;
            }
            else
            {
                is >> moderne;
                jucarii_primite.push_back(make_shared<Moderne>(moderne));
                cout << endl;
            }
        }
        cout << "Numar de dulciuri: ";
        is >> dulciuri;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Copii::write(os);
        os << "Numar de dulciuri: " << dulciuri << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Cuminti& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Cuminti& f) {
        return f.write(os);
    }
};

class Neastamparati : public Copii {
    unsigned int carbuni;
public:
    Neastamparati() :Copii(), carbuni(0) {}
    Neastamparati(unsigned int varsta, unsigned int fapte_bune,
        string nume, string prenume, string adresa,
        vector<shared_ptr<Jucarii>> jucarii_primite, unsigned int carbuni) :
        Copii(varsta, fapte_bune, nume, prenume, adresa, jucarii_primite),
        carbuni(carbuni) {}

    istream& read(istream& is) override {
        IoBase::read(is);
        Copii::read(is);
        cout << "Numar de carbuni: ";
        is >> carbuni;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Copii::write(os);
        os << "Numar de carbuni: " << carbuni<< endl;
        return os;
    }
    friend istream& operator>>(istream& is, Neastamparati& f) {
        return f.read(is);
    }
    friend ostream& operator<<(ostream& os, Neastamparati& f) {
        return f.write(os);
    }
};

class Menu {
    vector<shared_ptr<Copii>> copii;
public:
    void listOptions() {
        cout << "1. Citire n copii\n2. Afisare n copii\n3. Gaseste un copil dupa nume\n4. Sorteaza copiii dupa numarul de fapte bune\n";
    }
    void chooseOption() {
        unsigned int choice;
        cout << "Introdu numarul actiunii pe care vrei sa o executi: ";
        cin >> choice;
        switch (choice) {
        case 1:
        {
            string tip_copil;
            int n;
            cout << "Introduceti numarul n de copii: ";
            cin >> n;
            for (int j = 0; j < n; j++)
            {
                cout << "Cuminte/Neastamparat? ";
                cin >> tip_copil;
                while (tip_copil != "Cuminte" && tip_copil != "Neastamparat")
                {
                    cout << "Invalid\n";
                    cin >> tip_copil;
                }
                if (tip_copil == "Cuminte")
                {
                    Cuminti copil;
                    cin >> copil;
                    copii.push_back(make_shared<Cuminti>(copil));
                }
                else
                {
                    Neastamparati copil;
                    cin >> copil;
                    copii.push_back(make_shared<Neastamparati>(copil));
                }
            }
            break;
        }
        case 2:
        {
            for (auto copilas : copii)
            {
                cout << *copilas << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Introdu numele copilului pe care vrei sa il cauti: ";
            string nume;
            cin >> nume;
            copilDupaNume(copii, nume);
            break;
        }
        case 4:
        {
            copii = sortCopii(copii);
            break;
        }
        default:
            cout << "Alegere invalida\n";
            break;
        }
    }
    void mainLoop() {
        while (true) {
            listOptions();
            chooseOption();
        }
    }
};

int main()
{
    Menu m;
    m.mainLoop();
    return 0;
}

/*
lego
figurina
10
tanc
rusesc
15
vibranium
mov
biceps
muschi
90
proteine
cox
ceiala
25
6
woah
careful
29
abibas
superstar
*/

/*
Neastamparat
gheorghe
robert
20
2
Clasice
cox
montana
15
vibranium
mov
Educative
biceps
triceps
90
hoes
3
Neastamparat
andrei
alex
15
1
Moderne
animal
nebun
19
ayerdas
superztar
4
Neastamparat
mihai
mihaitza
19
0
5
*/