#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
class InterestPoint {
    int nr_vizitatori, x, y;
public:
    friend class BikeTrail;
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    int getv() {
        return nr_vizitatori;
    }
    InterestPoint();
    InterestPoint(int, int, int);
    friend istream& operator>> (istream& is, InterestPoint& a) {
        is >> a.nr_vizitatori;
        is >> a.x;
        is >> a.y;
        return is;
    }
    friend ostream& operator<<(ostream& os, InterestPoint& a) {
        os << "Numar de vizitatori: " << a.nr_vizitatori << endl << "Coordonata x: " << a.x << endl << "Coordonata y: " << a.y << endl<<endl;
        return os;
    }
};   

InterestPoint::InterestPoint() {
    nr_vizitatori = x = y = 0;
}

InterestPoint::InterestPoint(int nr_vizitatori, int x, int y){
    this->nr_vizitatori = nr_vizitatori;
    this->x = x;
    this->y = y;
}


class BikeTrail {
    string denumire, oras;
    vector<InterestPoint>puncte_interes;
public:
    BikeTrail();
    friend void traseumaxim(BikeTrail);
    BikeTrail(string, string, vector<InterestPoint>);
    friend istream& operator>>(istream& is, BikeTrail& a) {
        getline(is, a.denumire);
        getline(is, a.oras);
        int i,n;
        InterestPoint x;
        is >> n;
        for (i = 0; i < n;i++) {
            is >> x;
            a.puncte_interes.push_back(x);
        }
        return is;
    }
    friend ostream& operator<<(ostream& os, BikeTrail& a) {
        os << "Denumire: " << a.denumire << endl << "Oras: " << a.oras<<endl;
        for (auto punct : a.puncte_interes) {
            os << punct << endl;
        }
        return os;
    }
};

void traseumaxim(BikeTrail a)
{
    float max = 0.0;
    int vmax = 0, imax=0, jmax=0, kmax=0;
    for (int i = 0; i < a.puncte_interes.size() - 2; i++)
        for (int j = i + 1; j < a.puncte_interes.size() - 1; j++)
            for (int k = j + 1; k < a.puncte_interes.size(); k++) {
                if ((float)sqrt((a.puncte_interes[j].getx() - a.puncte_interes[i].getx()) * (a.puncte_interes[j].getx() - a.puncte_interes[i].getx()) + (a.puncte_interes[j].gety() - a.puncte_interes[i].gety()) * (a.puncte_interes[j].gety() - a.puncte_interes[i].gety())))
                {
                    imax = i;
                    jmax = j;
                    vmax = a.puncte_interes[i].getv() + a.puncte_interes[j].getv();
                    max = (float)sqrt((a.puncte_interes[j].getx() - a.puncte_interes[i].getx()) * (a.puncte_interes[j].getx() - a.puncte_interes[i].getx()) + (a.puncte_interes[j].gety() - a.puncte_interes[i].gety()) * (a.puncte_interes[j].gety() - a.puncte_interes[i].gety()));
                }
                if (max + (float)sqrt((a.puncte_interes[k].getx() - a.puncte_interes[j].getx()) * (a.puncte_interes[k].getx() - a.puncte_interes[j].getx()) + (a.puncte_interes[k].gety() - a.puncte_interes[j].gety()) * (a.puncte_interes[k].gety() - a.puncte_interes[j].gety())) > max)
                {
                    kmax = k;
                    vmax += a.puncte_interes[k].getv();
                    max += (float)sqrt((a.puncte_interes[k].getx() - a.puncte_interes[j].getx()) * (a.puncte_interes[k].getx() - a.puncte_interes[j].getx()) + (a.puncte_interes[k].gety() - a.puncte_interes[j].gety()) * (a.puncte_interes[k].gety() - a.puncte_interes[j].gety()));
                }
            }
    cout << a.puncte_interes[imax] << endl << a.puncte_interes[jmax] << endl << a.puncte_interes[kmax] << endl << "Distanta: " << max << endl << "Numarul de vizitatori: " << vmax << endl;

}

BikeTrail::BikeTrail() {}

BikeTrail::BikeTrail(string denumire, string oras, vector<InterestPoint> puncte_interes) {
    this->denumire = denumire;
    this->oras = oras;
    this->puncte_interes = puncte_interes;
}


int main()
{
    BikeTrail pista;
    cin >> pista;
    traseumaxim(pista);
    return 0;
}
/*Traseu#1
Constanta
5
102  0 0
404  10 10
3    1 1
22   3 2
1001 5 0
*/