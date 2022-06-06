/*
Gheorghe Robert-Mihai
GNU GCC++
Stefan-Eduard Deaconu
*/

#include <iostream>
#include <string>
#include <vector>
#include "IoBase.h"

using namespace std;

unsigned id_global = 0;

class Malware : public IoBase {
protected:
    double impact;
    unsigned int zi, luna, an;
    vector<string> registrii;
    string nume, metoda;
public:
    friend class Computer;
    Malware() : impact(0), zi(0), luna(0), an(0), metoda("unknown") {}
    Malware(double impact, unsigned int zi, unsigned int luna,
        unsigned int an, string nume, string metoda,
        vector<string> registrii) :
        impact(impact), zi(zi), luna(luna), an(an), nume(nume), metoda(metoda), registrii(registrii) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        cout << "Rating impact: ";
        is >> impact;
        cout << "Data de infectare:\nZi: ";
        is >> zi;
        cout << "Luna: ";
        is >> luna;
        cout << "An: ";
        is >> an;
        cin.get();
        cout << "Nume: ";
        getline(cin, nume);
        cout << "Metoda de infectare: ";
        is >> metoda;
        int n;
        cout << "Numar de registrii modificati: ";
        is >> n;
        cout << "Registrii modificati: ";
        string str;
        for (int i = 0; i < n; i++)
        {
            is >> str;
            registrii.push_back(str);
        }
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        cout << "Rating impact: " << impact << "\n" << "Data de infectare: " << zi << "." << luna << "." << an << "\n" <<
            "Nume: ";
        for (auto num : nume) {
            cout << num;
        }
        cout << "\nMetoda de infectare: " << metoda << "\nRegistrii modificati: ";
        for (auto registru : registrii) {
            cout << registru << " ";
        }
        cout << "\n";
        return os;
    }
    friend istream& operator>>(istream& is, Malware& m) {
        return m.read(is);
    }
    friend ostream& operator<<(ostream& os, Malware& m) {
        return m.write(os);
    }
};

class Rootkit : public Malware {
protected:
    vector<string> importuri, indici;
public:
    friend class Computer;
    Rootkit() : Malware() {}
    Rootkit(double impact, unsigned int zi, unsigned int luna,
        unsigned int an, string nume, string metoda,
        vector<string> registrii, vector<string> importuri,
        vector<string> indice) : Malware(impact, zi, luna, an, nume, metoda, registrii),
        importuri(importuri), indici(indici) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Malware::read(is);
        unsigned int nrimporturi, nrindici;
        cout << "Numar de importuri: ";
        is >> nrimporturi;
        cout << "Importuri: ";
        string str;
        for (unsigned int i = 0; i < nrimporturi; i++)
        {
            is >> str;
            importuri.push_back(str);
        }
        cout << "Numar de indici: ";
        is >> nrindici;
        cout << "Indici: ";
        for (unsigned int i = 0; i < nrindici; i++)
        {
            is >> str;
            indici.push_back(str);
        }
        return is;
    }
    ostream& write(ostream& os) const override {
        Malware::write(os);
        cout << "Importuri: ";
        for (auto import : importuri) {
            cout << import << " ";
        }
        cout << "\nIndici: ";
        for (auto indice : indici) {
            cout << indice << " ";
        }
        cout << "\n";
        return os;
    }
    friend istream& operator>>(istream& is, Rootkit& m) {
        return m.read(is);
    }
    friend ostream& operator<<(ostream& os, Rootkit& m) {
        return m.write(os);
    }
};

class Keylogger : public Malware {
protected:
    vector<string> functii, taste;
public:
    friend class Computer;
    Keylogger() : Malware() {}
    Keylogger(double impact, unsigned int zi, unsigned int luna,
        unsigned int an, string nume, string metoda,
        vector<string> registrii, vector<string> functii,
        vector<string> taste) : Malware(impact, zi, luna, an, nume, metoda, registrii),
        functii(functii), taste(taste) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Malware::read(is);
        unsigned int nrfunctii, nrtaste;
        cout << "Numar de functii: ";
        is >> nrfunctii;
        cout << "Functii: ";
        string str;
        for (unsigned i = 0; i < nrfunctii; i++)
        {
            is >> str;
            functii.push_back(str);
        }
        cout << "Numar de taste: ";
        is >> nrtaste;
        cout << "Taste: ";
        for (unsigned int i = 0; i < nrtaste; i++)
        {
            is >> str;
            taste.push_back(str);
        }
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Malware::write(os);
        cout << "Functii: ";
        for (auto functie : functii) {
            cout << functie << " ";
        }
        cout << "\nTaste: ";
        for (auto tasta : taste) {
            cout << tasta << " ";
        }
        cout << "\n";
        return os;
    }
    friend istream& operator>>(istream& is, Keylogger& m) {
        return m.read(is);
    }
    friend ostream& operator<<(ostream& os, Keylogger& m) {
        return m.write(os);
    }
};

class Kernel_Keylogger : virtual public Keylogger, virtual public Rootkit {
protected:
    bool ascunde_fisiere, ascunde_registrii;
public:
    friend class Computer;
    Kernel_Keylogger() : Rootkit(), Keylogger(), ascunde_fisiere(false), ascunde_registrii(false) {}
    Kernel_Keylogger(double impact, unsigned int zi, unsigned int luna,
        unsigned int an, string nume, string metoda,
        vector<string> registrii, vector<string> importuri,
        vector<string> indice, vector<string> functii,
        vector<string> taste, bool ascunde_fisiere, bool ascunde_registrii) :
        Rootkit(impact, zi, luna, an, nume, metoda, registrii, importuri, indice),
        Keylogger(impact, zi, luna, an, nume, metoda, registrii, functii, taste),
        ascunde_fisiere(ascunde_fisiere), ascunde_registrii(ascunde_registrii) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Rootkit::read(is);
        unsigned int nrfunctii, nrtaste;
        cout << "Numar de functii: ";
        is >> nrfunctii;
        cout << "Functii: ";
        string str;
        for (unsigned i = 0; i < nrfunctii; i++)
        {
            is >> str;
            functii.push_back(str);
        }
        cout << "Numar de taste: ";
        is >> nrtaste;
        cout << "\nTaste: ";
        for (unsigned int i = 0; i < nrtaste; i++)
        {
            is >> str;
            taste.push_back(str);
        }
        cout << "Ascunde fisiere?(1/0) ";
        is >> ascunde_fisiere;
        cout << "Ascunde registrii?(1/0) ";
        is >> ascunde_registrii;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Rootkit::write(os);
        cout << "Functii: ";
        for (auto functie : functii) {
            cout << functie << " ";
        }
        cout << "\nTaste: ";
        for (auto tasta : taste) {
            cout << tasta << " ";
        }
        cout << "\n";
        if (ascunde_fisiere)
            cout << "Ascunde fisiere.\n";
        else
            cout << "Nu ascunde fisiere.\n";
        if (ascunde_registrii)
            cout << "Ascunde registrii.\n";
        else
            cout << "Nu ascunde registrii.\n";
        return os;
    }
    friend istream& operator>>(istream& is, Kernel_Keylogger& m) {
        return m.read(is);
    }
    friend ostream& operator<<(ostream& os, Kernel_Keylogger& m) {
        return m.write(os);
    }
};

class Ransomware : public Malware {
protected:
    unsigned int rating_criptare;
    double rating_obfuscare;
public:
    friend class Computer;
    Ransomware() : Malware(), rating_criptare(rating_criptare),
        rating_obfuscare(rating_obfuscare) {}
    Ransomware(double impact, unsigned int zi, unsigned int luna,
        unsigned int an, string nume, string metoda,
        vector<string> registrii, unsigned int rating_criptare,
        double rating_obfuscare) : Malware(impact, zi, luna, an, nume, metoda, registrii),
        rating_criptare(rating_criptare), rating_obfuscare(rating_obfuscare) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        Malware::read(is);
        cout << "Rating criptare: ";
        is >> rating_criptare;
        cout << "Rating obfuscare: ";
        is >> rating_obfuscare;
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Malware::write(os);
        cout << "Rating criptare: " << rating_criptare << "\nRating obfuscare: " << rating_obfuscare << "\n";
        return os;
    }
    friend istream& operator>>(istream& is, Ransomware& m) {
        return m.read(is);
    }
    friend ostream& operator<<(ostream& os, Ransomware& m) {
        return m.write(os);
    }
};

class Computer : public IoBase {
protected:
    unsigned int id;
    vector<Rootkit> rootkits;
    vector<Keylogger> keyloggers;
    vector<Kernel_Keylogger> kkeyloggers;
    vector<Ransomware> ransomwares;
    double rating_final;
    double calcul_rating();
public:
    friend class Menu;
    Computer() : id(id_global++), rating_final(0) {}
    Computer(vector<Rootkit> rootkit, vector<Keylogger> keyloggers, vector<Kernel_Keylogger> kkeyloggers,
        vector<Ransomware> ransomwares) :
        id(id_global++), rootkits(rootkits), keyloggers(keyloggers), kkeyloggers(kkeyloggers), ransomwares(ransomwares),
        rating_final(calcul_rating()) {}
    istream& read(istream& is) override {
        IoBase::read(is);
        unsigned int m;
        string tip_malware;
        Rootkit rootkit;
        Keylogger keylogger;
        Kernel_Keylogger kkeylogger;
        Ransomware ransomware;
        cout << "Calculatorul cu ID-ul " << id << endl;
        cout << "Numar de malware-uri: ";
        is >> m;
        for (unsigned int i = 0; i < m; i++)
        {
            cout << "Tip malware: ";
            is >> tip_malware;
            if (tip_malware == "Rootkit" || tip_malware == "rootkit") {
                is >> rootkit;
                rootkits.push_back(rootkit);
            }
            else if (tip_malware == "Keylogger" || tip_malware == "keylogger") {
                is >> keylogger;
                keyloggers.push_back(keylogger);
            }
            else if (tip_malware == "Kernel_Keylogger" || tip_malware == "kernel_keylogger") {
                is >> kkeylogger;
                kkeyloggers.push_back(kkeylogger);
            }
            else {
                is >> ransomware;
                ransomwares.push_back(ransomware);
            }
        }
        rating_final = calcul_rating();
        return is;
    }
    ostream& write(ostream& os) const override {
        IoBase::write(os);
        cout << "ID: " << id << "\nMalwares:\n";
        for (auto rootkit : rootkits) {
            cout << rootkit << "\n";
        }
        for (auto keylogger : keyloggers) {
            cout << keylogger << "\n";
        }
        for (auto kkeylogger : kkeyloggers) {
            cout << kkeylogger << "\n";
        }
        for (auto ransomware : ransomwares) {
            cout << ransomware << "\n";
        }
        cout << "Rating final de impact: " << rating_final << "\n";
        return os;
    }
    friend istream& operator>>(istream& is, Computer& c) {
        return c.read(is);
    }
    friend ostream& operator<<(ostream& os, Computer& c) {
        return c.write(os);
    }
};

double Computer::calcul_rating() {
    rating_final = 0;
    for (auto rootkit : rootkits) {
        for (auto registru : rootkit.registrii) {
            if (registru == "HKLM-run" || registru == "HKCU-run")
                rating_final += 20;
        }
        unsigned int dublu = 1;
        for (auto import : rootkit.importuri) {
            if (import == "ntoskrnl.exe")
            {
                dublu = 2;
                break;
            }
        }
        for (auto indice : rootkit.indici) {
            if (indice == "System Service Descriptor Table" ||
                indice == "SSDT" || indice == "NtCreateFile")
                rating_final += 100 * dublu;
        }
    }
    for (auto keylogger : keyloggers) {
        for (auto registru : keylogger.registrii) {
            if (registru == "HKLM-run" || registru == "HKCU-run")
                rating_final += 20;
        }
        unsigned int dublu = 1;
        for (auto tasta : keylogger.taste) {
            if (tasta == "[Up]" || tasta == "[NumLock]" || tasta == "[Down]" ||
                tasta == "[Right]" || tasta == "[UP]" || tasta == "[Left]" ||
                tasta == "[PageDown]")
                rating_final += 10;
        }
        for (auto functie : keylogger.functii) {
            if (functie == "CreateFileW" || functie == "OpenProcess" || functie == "ReadFile" ||
                functie == "WriteFile" || functie == "RegisterHotKey" || functie == "SetWindowsHookEx")
                rating_final += 30;
        }
    }
    for (auto kkeylogger : kkeyloggers) {
        for (auto registru : kkeylogger.Rootkit::Malware::registrii) {
            if (registru == "HKLM-run" || registru == "HKCU-run")
                rating_final += 20;
        }
        unsigned int dublu = 1;
        for (auto import : kkeylogger.importuri) {
            if (import == "ntoskrnl.exe")
            {
                dublu = 2;
                break;
            }
        }
        for (auto indice : kkeylogger.indici) {
            if (indice == "System Service Descriptor Table" ||
                indice == "SSDT" || indice == "NtCreateFile")
                rating_final += 100 * dublu;
        }
        for (auto tasta : kkeylogger.taste) {
            if (tasta == "[Up]" || tasta == "[NumLock]" || tasta == "[Down]" ||
                tasta == "[Right]" || tasta == "[UP]" || tasta == "[Left]" ||
                tasta == "[PageDown]")
                rating_final += 10;
        }
        for (auto functie : kkeylogger.functii) {
            if (functie == "CreateFileW" || functie == "OpenProcess" || functie == "ReadFile" ||
                functie == "WriteFile" || functie == "RegisterHotKey" || functie == "SetWindowsHookEx")
                rating_final += 30;
        }
        if (kkeylogger.ascunde_fisiere)
            rating_final += 20;
        if (kkeylogger.ascunde_registrii)
            rating_final += 30;
    }
    for (auto ransomware : ransomwares) {
        for (auto registru : ransomware.registrii) {
            if (registru == "HKLM-run" || registru == "HKCU-run")
                rating_final += 20;
        }
        rating_final += ransomware.rating_criptare + ransomware.rating_obfuscare;
    }
    return rating_final;
}

class Menu : public IoBase {
    vector<Computer> v;
public:
    Menu(vector<Computer> v) : v(v) {}
    void listOptions();
    void chooseOption();
    void mainLoop();
};

void Menu::listOptions() {
    cout << "1. Afisare informatii despre fiecare calculator.\n";
    cout << "2. Afisare informatii despre fiecare calculator ordonate dupa rating-ul final.\n";
    cout << "3. Afisare primele k calculatoare ordonate dupa rating-ul final.\n";
    cout << "4. Afisare procent de calculatoare infectate.\n";
}

void Menu::chooseOption() {
    int choice;
    cout << "Introduceti un numar de la 1 la 4: ";
    cin >> choice;
    if (choice == 1)
        for (auto computer : v) {
            cout << computer << "\n";
        }
    else if (choice == 2) {
        Computer aux;
        for (unsigned int i = 0; i < v.size() - 1; i++)
            for (unsigned int j = i + 1; j < v.size(); j++)
                if (v[i].rating_final > v[j].rating_final) {
                    aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
        for (auto computer : v)
            cout << computer << "\n";
    }
    else if (choice == 3) {
        unsigned int k;
        do {
            cout << "k= ";
            cin >> k;
            if (k < 0 || k > v.size())
                cout << "Index out of range.\n";
        } while (k < 0 || k > v.size());
        Computer aux;
        for (unsigned int i = 0; i < v.size() - 1; i++)
            for (unsigned int j = i + 1; j < v.size(); j++)
                if (v[i].rating_final > v[j].rating_final) {
                    aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
        for (unsigned int i = 0; i < k; i++)
            cout << v[i] << "\n";
    }
    else if (choice == 4) {
        unsigned int infectate = 0;
        for (auto computer : v)
            if (computer.rating_final)
                infectate++;
        cout << (double)infectate / v.size() * 100 << "%\n";
    }
    else
        cout << "Invalid. Numarul trebuie sa fie de la 1 la 4.\n";
}

void Menu::mainLoop() {
    while (true)
    {
        listOptions();
        chooseOption();
    }
}

int main()
{
    int n;
    vector<Computer> v;
    cout << "Numar calculatoare: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Computer computer;
        cin >> computer;
        v.push_back(computer);
    }
    for (auto computer : v)
        cout << computer << endl;
    Menu m(v);
    m.mainLoop();
    return 0;
}