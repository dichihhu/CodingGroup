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
struct ComparePoint : public binary_function<Point, Point, bool>
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
    friend ConvexHull& operator+=(ConvexHull& l, const ConvexHull& r)
    {
        if (!l._data.empty()) l.pop(); //duplicate vertex
        l._data.insert(l._data.end(), r._data.rbegin(), r._data.rend());
        return l;
    }
    Point& operator[](size_t n)
    {
        return _data[n];
    }
private:
    vector<Point> _data;
};

typedef set<Point, ComparePoint> ST;

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
ConvexHull FindConvexHull(ST& pst)
{
    vector<Point> st(pst.begin(), pst.end());
    //points are sorted
    ConvexHull l, r;
    size_t start = 0;
    for(size_t i=0; i<st.size(); ++i)
    {
        int next = i;

        while(l.size()>=2)
        {
            int n = l.size();
            int c = cross(l[n-2], l[n-1], st[next]);
            if (c > 0 ||
                (c == 0 && farther(l[n-2], l[n-1], st[next])))
                { l.pop(); }
            else break;
        }
        l.add(st[next]);

        while(r.size()>=2) 
        {
            int n = r.size();
            int c = cross(r[n-2], r[n-1], st[i]);
            if (c < 0 ||
                (c == 0 && farther(r[0], r[1], st[i])))
                { r.pop(); }
            else break;
        }
        r.add(st[i]);
    }

    return (r += l);
}

void InsertSet(istream& in, ST& st)
{
    int nPoints =0;
    cin >> nPoints;
    if (nPoints == -1)
        cin >> nPoints; 
    while(nPoints--)
    {
        size_t x = 0, y = 0;
        cin>> x >> y;
        st.insert(Point(x, y));
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
        //ConvexHull d;
        //ReadData(cin, d);
        ST st;
        InsertSet(cin, st);
        cout << FindConvexHull(st);
        if (sets >0) cout << "-1" << endl;
    }
    return 0;
}
