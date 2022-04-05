#include <iostream>

#include "IoBase.h"
#include "functions.h"

using namespace std;

class Fraction : public IoBase {
protected:
    int a, b;
public:
    // constructori
    Fraction(int a, int b) : a(a), b(b) {}
    Fraction() {}
    // IoBase - overrided functions
    istream& read(istream& is) override {
        IoBase::read(is);
        cout << "a: ";
        is >> a;
        cout << "b: ";
        is >> b;
        return is;
    }

    ostream& write(ostream& os) const override {
        IoBase::write(os);
        cout << "a: " << a;
        cout << ", b: " << b;
        return os;
    }

    friend istream& operator>>(istream& is, Fraction& f) {
        return f.read(is);
    }

    friend ostream& operator<<(ostream& os, Fraction& f) {
        return f.write(os);
    }
    int geta() {
        return a;
    }
    int getb() {
        return b;
    }
    friend Fraction operator*(Fraction, Fraction);
};
class IrrationalFraction : public Fraction {
protected:
    // adaugam si radicalul dintr-un numar real
    double underSqrt;
public:
    // constructori:
    IrrationalFraction() {};
    IrrationalFraction(int a, int b, double underSqrt) : Fraction(a, b), underSqrt(underSqrt) {}

    // IoBase - overrided functions
    istream& read(istream& is) override {
        IoBase::read(is);
        Fraction::read(is);
        cout << "underSqrt: ";
        is >> underSqrt;
        return is;
    }

    ostream& write(ostream& os) const override {
        IoBase::write(os);
        Fraction::write(os);
        os << ", underSqrt: " << underSqrt;
        return os;
    }
    friend istream& operator>>(istream& is, IrrationalFraction& f) {
        return f.read(is);
    }

    friend ostream& operator<<(ostream& os, IrrationalFraction& f) {
        return f.write(os);
    }

    friend bool operator<(Fraction, Fraction);
    friend bool operator<(Fraction, IrrationalFraction);
    friend bool operator<(IrrationalFraction, Fraction);
    friend bool operator<(IrrationalFraction, IrrationalFraction);
    friend Fraction operator*(Fraction, Fraction);
    friend IrrationalFraction operator*(Fraction, IrrationalFraction);
    friend IrrationalFraction operator*(IrrationalFraction, Fraction);
    friend IrrationalFraction operator*(IrrationalFraction, IrrationalFraction);
};

bool operator<(Fraction f1, Fraction f2) {
    return (float)f1.geta() / f1.getb() < (float)f2.geta() / f2.getb();
}

bool operator<(Fraction f1, IrrationalFraction f2) {
    return (float)f1.geta() / f1.getb() < (float)f2.a / f2.b * f2.underSqrt;
}

bool operator<(IrrationalFraction f1, Fraction f2) {
    return (float)f1.a / f1.b * f1.underSqrt < (float)f2.geta() / f2.getb();
}

bool operator<(IrrationalFraction f1, IrrationalFraction f2) {
    return (float)f1.a / f1.b * f1.underSqrt < (float)f2.a / f2.b * f2.underSqrt;
}

Fraction operator*(Fraction f1, Fraction f2) {
    Fraction rezultat;
    rezultat.a = f1.geta() * f2.geta();
    rezultat.b = f1.getb() * f2.getb();
    for (int i = 2; i < min(rezultat.a, rezultat.b) / 2; i++)
        while (rezultat.a % i == rezultat.b % i && rezultat.a % i == 0) {
            rezultat.a /= i;
            rezultat.b /= i;
        }
    return rezultat;
}

IrrationalFraction operator*(Fraction f1, IrrationalFraction f2) {
    IrrationalFraction rezultat;
    rezultat.a = f1.geta() * f2.geta();
    rezultat.b = f1.getb() * f2.getb();
    rezultat.underSqrt = f2.underSqrt;
    for (int i = 2; i < min(rezultat.a, rezultat.b) / 2; i++)
        while (rezultat.a % i == rezultat.b % i && rezultat.a % i == 0) {
            rezultat.a /= i;
            rezultat.b /= i;
        }
    return rezultat;
}

IrrationalFraction operator*(IrrationalFraction f1, Fraction f2) {
    IrrationalFraction rezultat;
    rezultat.a = f1.geta() * f2.geta();
    rezultat.b = f1.getb() * f2.getb();
    rezultat.underSqrt = f1.underSqrt;
    for (int i = 2; i < min(rezultat.a, rezultat.b) / 2; i++)
        while (rezultat.a % i == rezultat.b % i && rezultat.a % i == 0) {
            rezultat.a /= i;
            rezultat.b /= i;
        }
    return rezultat;
}

IrrationalFraction operator*(IrrationalFraction f1, IrrationalFraction f2) {
    IrrationalFraction rezultat;
    rezultat.a = f1.geta() * f2.geta();
    rezultat.b = f1.getb() * f2.getb();
    rezultat.underSqrt = f1.underSqrt * f2.underSqrt;
    for (int i = 2; i < min(rezultat.a, rezultat.b) / 2; i++)
        while (rezultat.a % i == rezultat.b % i && rezultat.a % i == 0) {
            rezultat.a /= i;
            rezultat.b /= i;
        }
    return rezultat;
}

// Vom implementa cele doua clase
// Vom implementa <
// TODO aici editorul are un feature fain, genereaza toti op >, < etc

/*
Exemplu input:

2 3         -> citim fractia 2/3
1 2 2       -> citim fractia 1/2*sqrt(2)

Ca indiciu, vom avea 2/3 < 1/2*sqrt(2).
*/

// functie catre clasa de baza:
// TODO testati ce se intampla daca eliminati ampersand-ul
void show(const Fraction& f) {
    cout << "Fractia este: " << f << '\n';
} // daca elimin ampersand-ul imi apeleaza citirea de la clasa de baza (Fraction)

int main() {
    // level 0: constructori si operatori de afisare
    Fraction f1(2, 3);
    IrrationalFraction f2(1, 2, 2);

    //    // TODO Level 1: operator de citire
    //    cin >> f1;
    //    cin >> f2;
    //    cout << f1 << " si " << f2;
    Fraction x1;
    IrrationalFraction x2;
    cin >> x1 >> x2;
    cout << x1 << " si " << x2<<endl<<endl;
    //    // TODO level 2: Operator supraincarcat cu clase diferite
    //    if (f1 < f2) {
    //        cout << f1 << " < " << f2 << '\n';
    //    } else {
    //        cout << f2 << " < " << f1 << '\n';
    //    }
    if (f1 < f2)
        cout << f1 << " < " << f2 << "\n";
    else
        cout << f2 << " < " << f1 << "\n";
    cout << "\n";
    //    // TODO Level 3: operatori si metode
    //    cout << f1 * f2 << '\n';
    //    // TODO Intrebari spre rezolvare:
    //    //  -----------------------------
    //    // TODO Cand scadem doua fractii, una de forma a/b si cealalta a/b*sqrt(c),
    //    //      la ce forma ajungem?
    cout << f1 * f2<<"\n\n";
    IrrationalFraction a, b;
    cin >> a >> b;
    cout << a * b << "\n\n";
        // Aveti deja implementata functia globala show(Fraction f).
        // TODO Ce se intampla cand urmatoarele 2 linii de cod?
    show(f1);
    show(f2);
    // TODO dar daca adaugam & la parametrul din show?
}