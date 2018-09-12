#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Point
{
    size_t x;
    size_t y;
    Point(size_t _x, size_t _y): x(_x), y(_y) {}
};

class ConvexHull
{
public:
    ConvexHull() {}
    ConvexHull(size_t n) : _data(n, Point(0, 0)) {}
    size_t size() const {return _data.size();}
    const vector<Point>& data() const { return _data; }
    Point& at(size_t n) { return _data[n]; }
    const Point& at(size_t n) const { return _data[n]; }
    void add (const Point& p) { _data.push_back(p); }
    void pop () { _data.pop_back(); }
    void assign (const ConvexHull& c) { 
        _data.assign(c.data().begin(), c.data().end());
    }
    friend ostream& operator<<(ostream& out, const ConvexHull& d)
    {
        out << d.size() << endl;
        for(auto& a : d._data)
            out << a.x << " " << a.y << endl;
        return out;
    }
private:
    vector<Point> _data;
};

int cross(Point orig, Point a, Point b)
{
    return (a.x - orig.x) * (b.y - orig.y) - (a.y - orig.y) * (b.x - orig.x);
}

ConvexHull FindConvexHull( ConvexHull& d)
{
//sorted
    ConvexHull o;
    size_t start = 0;
    for (size_t i = start; i < d.size(); ++i)
    {   
        size_t m=i;
        while (m>=2 && cross(d.at(m-2), d.at(m-1), d.at(i)) > 0 )
        {
            o.pop();
            m--;
        }
        o.add(d.at(i));
    }
    d.assign(o);
    return d;
}

void ReadData(istream& in, ConvexHull& d)
{
    int n =0;
    while (cin >> n)
    {
        if (n == -1) return;
        int x = 0, y = 0;

        while (n-- > 0)
        {
            cin >> x >> y;
            d.add(Point(x, y));
        }
    }
    return;
}
int main ()
{
    int sets=0;
    cin >> sets;

    cout << sets;
    while (sets--)
    {
        ConvexHull d;
        ReadData(cin, d);
        cout << FindConvexHull(d);
        if (sets >0) cout << "-1" << endl;
    }
    return 0;
}
