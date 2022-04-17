#include <iostream>
#include "../util/IoBase.h"
#include "../util/functions.h"

using namespace std;

class Tablou:public IoBase {
protected:
    double latime, ratie;
public:
    void cantitateUlei();
    double ariaTabloului();
    Tablou() : latime(0), ratie(0) {}
    Tablou(double latime, double ratie): latime(latime), ratie(ratie){}
};

class Miniatura: public Tablou{
public:
    Miniatura() {
        latime = 0;
        ratie = 0;
    }
    Miniatura(double _latime, double _ratie) throw(double){
        latime = _latime;
        ratie = _ratie;
        try {
            if (latime > 10 || ratie < 1 || ratie>3)
                throw 1.0;
        }
        catch (double x) {
            cout << "Dimensiuni invalide. (latime >= 10, 1 <= ratie <= 3)\n";
        }
    }
};

class Tablouri : public Tablou {
public:
    Tablouri() {
        latime = 0;
        ratie = 0;
    }
    Tablouri(double _latime, double _ratie) throw(double) {
        latime = _latime;
        ratie = _ratie;
        try {
            if (latime < 19 || latime >57 || ratie < 0.618 || ratie > 1.618)
                throw 1.0;
        }
        catch (double x) {
            cout << "Dimensiuni invalide. (19 <= latime <= 57, 0.618 <= ratie <= 1.618)\n";
        }
    }
};

class TablouriPerete : public Tablou {
public:
    TablouriPerete() {
        latime = 0;
        ratie = 0;
    }
    TablouriPerete(double _latime, double _ratie) throw(double) {
        latime = _latime;
        ratie = _ratie;
        try {
            if (latime < 1000 || latime >10000 || ratie < 1 || ratie > 10)
                throw 1.0;
        }
        catch (double x) {
            cout << "Dimensiuni invalide. (1000 <= latime <= 10000, 1 <= ratie <= 10)\n";
        }
    }
};

double Tablou::ariaTabloului() {
    return latime * latime / ratie;
}

void Tablou::cantitateUlei() {
    try {
        Miniatura* a = dynamic_cast<Miniatura*>(this);
        Tablouri* b = dynamic_cast<Tablouri*>(this);
        TablouriPerete* c = dynamic_cast<TablouriPerete*>(this);
        if (a && (latime > 10 || ratie < 1 || ratie>3))
            throw 1;
        else if (b && (latime < 19 || latime >57 || ratie < 0.618 || ratie > 1.618))
            throw 1;
        else if (c && (latime < 1000 || latime >10000 || ratie < 1 || ratie > 10))
            throw 1;
        cout << ariaTabloului() * 0.1;
    }
    catch (int x) {
        return;
    }
}

int main()
{
    TablouriPerete x;
    double latime, ratie;
    cin >> latime >> ratie;
    x = TablouriPerete{ latime, ratie };
    x.cantitateUlei();
    return 0;
}
