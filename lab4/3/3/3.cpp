#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
class InterestPoint {
    int nr_vizitatori, x, y;
public:
    friend class BikeTrail;
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

    friend double distanta(const InterestPoint &p1, const InterestPoint &p2) {
        return (double)sqrt((p1.x - p2.x) * (p1.x - p2.x + (p1.y - p2.y) * (p1.y - p2.y)));
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
    friend void traseuminim(BikeTrail);
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
    double max = 0.0;
    int vmax = 0, imax=0, jmax=0, kmax=0;
    for (int i = 0; i < a.puncte_interes.size() - 2; i++)
        for (int j = i + 1; j < a.puncte_interes.size() - 1; j++)
            for (int k = j + 1; k < a.puncte_interes.size(); k++) {
                if (distanta(a.puncte_interes[i], a.puncte_interes[j]) + distanta(a.puncte_interes[j], a.puncte_interes[k]) > max) // daca te uiti acum la cod, este usor de vazut ca la conditie ai pus doar distanta
                {
                    imax = i;
                    jmax = j;
                    kmax = k;
                    vmax = a.puncte_interes[i].getv() + a.puncte_interes[j].getv();
                    max = distanta(a.puncte_interes[i], a.puncte_interes[j]) + distanta(a.puncte_interes[j], a.puncte_interes[k]);
                }
            }
    cout << a.puncte_interes[imax] << endl << a.puncte_interes[jmax] << endl << a.puncte_interes[kmax] << endl << "Distanta: " << max << endl << "Numarul de vizitatori: " << vmax << endl<<endl;
}

void traseuminim(BikeTrail a) {
    InterestPoint aux;
    int traseustart, traseufinal;
    for(int i=0;i<a.puncte_interes.size()-1;i++)
        for(int j=i+1;j<a.puncte_interes.size();j++)
            if (a.puncte_interes[i].getv() < a.puncte_interes[j].getv())
            {
                aux = a.puncte_interes[i];
                a.puncte_interes[i] = a.puncte_interes[j];
                a.puncte_interes[j] = aux;
            }
    // indecsii 0,1,2 reprezinta ABC din hint-ul tau
    if (distanta(a.puncte_interes[0], a.puncte_interes[1]) < distanta(a.puncte_interes[1], a.puncte_interes[2]))
    {
        if (distanta(a.puncte_interes[1], a.puncte_interes[2]) < distanta(a.puncte_interes[0], a.puncte_interes[2]))
            traseustart = 0, traseufinal = 2;
        else
            traseustart = 1, traseufinal = 2;
    }
    else
    {
        if (distanta(a.puncte_interes[0], a.puncte_interes[1]) < distanta(a.puncte_interes[0], a.puncte_interes[2]))
            traseustart = 0, traseufinal = 2;
        else
            traseustart = 0, traseufinal = 1;
    }
    if (traseustart == 0)
    {
        if (traseufinal == 1)
            cout << a.puncte_interes[0] << endl << a.puncte_interes[2] << endl << a.puncte_interes[1] <<endl<< endl;
        else
            cout << a.puncte_interes[0] << endl << a.puncte_interes[1] << endl << a.puncte_interes[2]  << endl;
    }
    else
        cout << a.puncte_interes[1] << endl << a.puncte_interes[0] << endl << a.puncte_interes[2] << endl;
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
    traseuminim(pista);
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