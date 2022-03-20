#include <iostream>

#include <vector>

#include <limits>
using namespace std;
class Coords {
    int x, y;
public:
    Coords();
    Coords(int, int);
    friend istream& operator>> (istream& is, Coords& a) {
        cout << "x: ";
        is >> a.x;
        cout << "y: ";
        is >> a.y;
        return is;
    }
    friend ostream& operator<<(ostream& os, Coords& a) {
        os << "x: " << a.x << endl << "y: " << a.y << endl << endl;
        return os;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
};

Coords::Coords() {
    x = y = 0;
}
Coords::Coords(int x, int y) {
    this->x = x;
    this->y = y;
}

class Queue {
    vector<Coords> coordonate;
    int nr;
public:
    Queue();
    Queue(vector<Coords>, int);
    void clear();
    bool isEmpty();
    Coords operator[](int i) {
        if (0 <= i <= coordonate.size())
            return coordonate[i];
        else
            return Coords(-1, -1);
    }
    Queue operator+=(Coords x) {
        coordonate.push_back(x);
        nr++;
        return *this;
    }
    Queue operator--() {
        vector<Coords> coords(coordonate.size() - 1);
        for (int i = 1;i < coordonate.size();i++)
            coords[i - 1] = coordonate[i];
        coordonate = coords;
        nr--;
        return *this;
    }
    friend istream& operator>> (istream& is, Queue& a) {
        cout << "Queue: " << endl;
        is >> a.nr;
        vector<Coords> coords(a.nr);
        a.coordonate = coords;
        for (int i = 0;i < a.nr;i++)
            is >> a.coordonate[i];
        return is;
    }
    friend ostream& operator<<(ostream& os, Queue& a) {
        cout << "Coordonatele vectorului: " << endl;
        for (auto x : a.coordonate) {
            os << x;
        }
        return os;
    }
    vector<Coords> getQueue() {
        return coordonate;
    }
};

Queue::Queue() {
    nr = 0;
}

Queue::Queue(vector<Coords> v, int nr) {
    coordonate = v;
    this->nr = nr;
}

void Queue::clear() {
    coordonate.clear();
}

bool Queue::isEmpty() {
    return coordonate.size() == 0;
}

class Maze {
    int n;
    vector<vector<int>> m;
    Coords start, end;
    friend void back(Maze&, Coords, int);
public:
    Maze();
    Maze(int, vector<vector<int>>, Coords, Coords);
    void fill();
    friend istream& operator>> (istream& is, Maze& a) {
        cout << "n= ";
        is >> a.n;
        vector<vector<int>> m(a.n, vector<int>(a.n, 1));
        cout << "Start: " << endl;
        is >> a.start;
        cout << "End: " << endl;
        is >> a.end;
        a.m = m;
        Queue coada;
        is >> coada;
        for (auto coordonata : coada.getQueue()) {
            a.m[coordonata.gety()][coordonata.getx()] = 0;
        }
        return is;
    }
    friend ostream& operator<< (ostream& os, Maze& a)
    {
        cout << "Matricea este: " << endl;
        for (int i = 0;i < a.n;i++)
        {
            for (int j = 0;j < a.n;j++)
                if (i == a.start.gety() and j == a.start.getx())
                    cout << "s ";
                else if (i == a.end.gety() and j == a.end.getx())
                    cout << "e ";
                else
                    cout << a.m[i][j] << " ";
            cout << endl;
        }
        cout << endl;
        return os;
    }
};

Maze::Maze() {
    n = 0;
}

Maze::Maze(int n, vector<vector<int>> m, Coords start, Coords end) {
    this->n = n;
    this->m = m;
    this->start = start;
    this->end = end;
}

int nrdrumuri, distanta_minima = INT_MAX;
vector<vector<int>>unfilled;

void Maze::fill() {
    unfilled = m;
    unfilled[start.gety()][start.getx()] = unfilled[end.gety()][end.getx()] = 0;
    back(*this, start, 1);
}

void back(Maze& b, Coords c, int pas) {
    int i;
    for (i = 0;i < 4;i++) 
        /* i = 0 -> merg in dreapta
           i = 1 -> merg in jos
           i = 2 -> merg in sus
           i = 3 -> merg in stanga
        */
        if (i == 0)
        {
            if (c.getx() < b.m.size() - 1 && (unfilled[c.gety()][c.getx() + 1] || pas < b.m[c.gety()][c.getx() + 1]))
            {
                b.m[c.gety()][c.getx() + 1] = pas;
                unfilled[c.gety()][c.getx() + 1] = 0;
                c = Coords(c.getx() + 1, c.gety());
                back(b, c, pas + 1);
                c = Coords(c.getx() - 1, c.gety());
            }
            else if (c.getx() < b.m.size() - 1)
            {
                if (c.getx() + 1 == b.end.getx() && c.gety() == b.end.gety())
                {
                    if (pas == distanta_minima)
                        nrdrumuri++;
                    else if (pas < distanta_minima) {
                        distanta_minima = pas;
                        nrdrumuri = 1;
                    }
                }
                else if (b.m[c.gety()][c.getx() + 1] > b.m[c.gety()][c.getx()])
                {
                    c = Coords(c.getx() + 1, c.gety());
                    back(b, c, pas + 1);
                    c = Coords(c.getx() - 1, c.gety());
                }
            }
        }
        else if (i == 1)
        {
            if (c.gety() < b.m.size() - 1 && (unfilled[c.gety() + 1][c.getx()] || pas < b.m[c.gety() + 1][c.getx()]))
            {
                b.m[c.gety() + 1][c.getx()] = pas;
                unfilled[c.gety() + 1][c.getx()] = 0;
                c = Coords(c.getx(), c.gety() + 1);
                back(b, c, pas + 1);
                c = Coords(c.getx(), c.gety() - 1);
            }
            else if (c.gety() < b.m.size() - 1)
            {
                if (c.getx() == b.end.getx() && c.gety() + 1 == b.end.gety())
                {
                    if (pas == distanta_minima)
                        nrdrumuri++;
                    else if (pas < distanta_minima) {
                        distanta_minima = pas;
                        nrdrumuri = 1;
                    }
                }
                else if (b.m[c.gety() + 1][c.getx()] > b.m[c.gety()][c.getx()])
                {
                    c = Coords(c.getx(), c.gety() + 1);
                    back(b, c, pas + 1);
                    c = Coords(c.getx(), c.gety() - 1);
                }
            }
        }
        else if (i == 2)
        {
            if (c.gety() && (unfilled[c.gety() - 1][c.getx()] || pas < b.m[c.gety() - 1][c.getx()]))
            {
                b.m[c.gety() - 1][c.getx()] = pas;
                unfilled[c.gety() - 1][c.getx()] = 0;
                c = Coords(c.getx(), c.gety() - 1);
                back(b, c, pas + 1);
                c = Coords(c.getx(), c.gety() + 1);
            }
            else if (c.gety())
            {
                if (c.getx() == b.end.getx() && c.gety() - 1 == b.end.gety())
                {
                    if (pas == distanta_minima)
                        nrdrumuri++;
                    else if (pas < distanta_minima)
                    {
                        distanta_minima = pas;
                        nrdrumuri = 1;
                    }
                }
                else if (b.m[c.gety() - 1][c.getx()] > b.m[c.gety()][c.getx()])
                {
                    c = Coords(c.getx(), c.gety() - 1);
                    back(b, c, pas + 1);
                    c = Coords(c.getx(), c.gety() + 1);
                }
            }
        }
        else {
            if (c.getx() && (unfilled[c.gety()][c.getx() - 1] || pas < b.m[c.gety()][c.getx() - 1])) {
                b.m[c.gety()][c.getx() - 1] = pas;
                unfilled[c.gety()][c.getx() - 1] = 0;
                c = Coords(c.getx() - 1, c.gety());
                back(b, c, pas + 1);
                c = Coords(c.getx() + 1, c.gety());
            }
            else if (c.getx())
            {
                if (c.getx() - 1 == b.end.getx() && c.gety() == b.end.gety())
                {
                    if (pas == distanta_minima)
                        nrdrumuri++;
                    else if (pas < distanta_minima) {
                        distanta_minima = pas;
                        nrdrumuri = 1;
                    }
                }
                else if (b.m[c.gety()][c.getx() - 1] > b.m[c.gety()][c.getx()])
                {
                    c = Coords(c.getx() - 1, c.gety());
                    back(b, c, pas + 1);
                    c = Coords(c.getx() + 1, c.gety());
                }
            }
        }
    if (c.getx() == b.start.getx() && c.gety() == b.start.gety())
        cout << b << "Numarul de drumuri este " << nrdrumuri << " de distanta minima " << distanta_minima<<".";
}
int main()
{
    Maze a;
    cin >> a;
    cout << a;
    a.fill();
    return 0;
}