#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

struct Point
{
    size_t x;
    size_t y;
    Point(size_t i, size_t j): x(i), y(j) {}
};
struct ComparePoint : public binaryfunction<Point, Point, bool>
{
    bool operator()(const Point& a, const Point& b)
    {
        return (a.y < b.y) ||
            (a.y == b.y && a.x < b.x);
    }
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

typedef set<Point> ST;

int cross(Point orig, Point a, Point b)
{
    return (a.x - orig.x) * (b.y - orig.y) - (a.y - orig.y) * (b.x - orig.x);
}
bool farther(Point orig, Point a, Point b)
{
    return (a.y - orig.y)*(a.y - orig.y) + (a.x - orig.x)*(a.x - orig.x)
        <= (b.y - orig.y)*(b.y - orig.y) + (b.x - orig.x)*(b.x - orig.x); // return true if a and b are the same point
}

static bool compare(const Point& a, const Point& b)
{
    return (a.y < b.y) ||
        (a.y == b.y && a.x < b.x);
}
size_t FindStartVertex(const ConvexHull& d)
{
    //find the bottom left point
    size_t first = 0;
    for (size_t i = 1; i < d.size(); i++)
    {
        if (compare(d.at(i), d.at(first)))
        {
            first = i;
        }
    }
    return first;
}
ConvexHull FindConvexHull( ConvexHull& d)
{
//assume sorted
    size_t start = FindStartVertex(d);
    ConvexHull o;
    o.add(d.at(start));

    for (size_t n=0; n<d.size(); ++n)
    {   
        size_t m = o.size();
        size_t next = (start+1 + n) % d.size();
        while (m>=2)
        {
            int c = cross(o.at(m-2), o.at(m-1), d.at(next));
            if (c > 0 || // i is out side of the last vertex
                (c == 0 && farther(o.at(m - 2), o.at(m - 1), d.at(next)))) // i is farther than last vertex
            {
                o.pop(); // drop last vertex
                m = o.size();
            }
            else
                break;
        }
        o.add(d.at(next));
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

    cout << sets << endl; 
    while (sets--)
    {
        ConvexHull d;
        ReadData(cin, d);
        cout << FindConvexHull(d);
        if (sets >0) cout << "-1" << endl;
    }
    return 0;
}
