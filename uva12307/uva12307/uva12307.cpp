//uva12307
// http://datagenetics.com/blog/march12014/index.html

// find 4 most vertices(lower, left, upper, right) (sorting)
// find the min angle formed by the above vertices and the coordination axies (atan2)
// rotate the capiler clockwise, and find one edge of the rectangle, and then its 4 points:
// - find the angle theta formed by pi, pi+1, pj
// - the length of line formed by (pj, P-1) is the projection of line(pi,pj) against line (pi, pi+1) by theta degrees
// - fine P-1's coordination 
// - repeat above steps with (P-1, pj, pk) -> P-2
//                           (P-2, pk, pl) -> P-3
//                           (P-3, pl, pi) -> P-4
// find area and perimeter of the rectangle
// repeat above with pi+1, pj, pk, pl, and so on, until all edges of the convex hull are traversed and find all rectangles
// 
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

using namespace std;
/*

iter pp = *pivot;
rec(i, j, k, l) = find_rectangle(fourMostVertices, pp+1);
area.push_back(rec.area());
perimeter.push_back(rec.perimeter());
*/

//2nd case, ... etc.

class Vec;
template <typename T>
struct _Point
{
    friend class Vec;
    friend istream& operator>>(istream& in, _Point& p)
	{
		in >> p._x >> p._y;
		return in;
	}
    friend T cross(const _Point& a, const _Point& b, const _Point& c)
	{
        return (b._x - a._x) * (b._y - a._y) - (c._y - a._y) * (c._x - a._x);
	}
    friend bool operator< (const _Point& a, const _Point& b)
    {
        return a._x < b._x || (a._x == b._x && a._y < b._y);
    }
    friend bool lower(const _Point& a, const _Point& b)
    {
    	return a._y < b._y || (a._y == b._y && a._x < b._x);
    }
    friend float angle(const _Point& a, const _Point& b)
    {
        return 0;
    }
    _Point() {}
    _Point(const T& x, const T& y) : _x(x), _y(y) {}
	T _x;
	T _y;
};
typedef _Point<float> Point;

class Vec
{
	friend float cross(const Vec& v1, const Vec& v2)
	{
		return v1.u*v2.v - v2.u*v1.v;
	}
public:
	Vec(const Point& a, const Point& b): u(b._x - a._x), v(b._y - a._y) {}
private:
	float u;
	float v;
};

typedef vector<Point>::iterator vpit;
typedef vector<Point>::const_iterator vpcit;

vector<Point> FindConvexHull(vector<Point>& d)
{
	sort(d.begin(), d.end());

	vector<Point> uch; //upper convex hull
	vector<Point> lch; //lower convex hull
	for_each(d.begin(), d.end(), [&](const Point& p)
	{
		auto test = [&](vector<Point>& v, function<bool(float)> f){
			while(v.size()>1)
			{
				vpit mark=v.end();
				auto c = cross(*(mark-2), *(mark-1), p); 
				if (f(c)) break;
				else /*if (c > 0 || (c==0 && farther(*(mark-2), *(mark-1), p)))*/ v.pop_back();
			}
			v.push_back(p);
			return;
		};
		test(uch, [](float c){return c<0;});
		test(lch, [](float c){return c>0;});
		return;
	});

	lch.pop_back(); //duplicate end point
    uch.insert(uch.end(), lch.rbegin(), lch.rend());
    return uch;
}
vector<vpcit> FindFourMostV(const vector<Point>& CH)
{
	auto pair_x = 
	minmax_element(CH.begin(), CH.end(), [](const Point& a, const Point& b)
	{ 
		return a < b;
	});
    auto pair_y =
	minmax_element(CH.begin(), CH.end(), [](const Point& a, const Point& b)
	{ 
		return lower(a, b);
	});
    
    return vector<vpcit>({ pair_x.first, pair_y.second, pair_x.second, pair_y.first });
}
vector<Point> InitCaliper(vector<vpcit> Four)
{
 //   auto deref = [](vector<vpcit>::iterator i)->Point { return *(*i); };
	vector<Point> vp;
    vp.resize(4);
//	transform(Four.begin(), Four.end(), vp.begin(), deref);

	Point p1 (vp[0]._x, vp[3]._y);
	Point p2 (vp[0]._x, vp[1]._y);
	Point p3 (vp[2]._x, vp[1]._y);
	Point p4 (vp[2]._x, vp[3]._y);

	return vector<Point>({p1, p2, p3, p4});
}
vpcit RotateCaliper(const vector<Point>& CH, const vector<vpcit>& Four, const vector<Point>& caliper)
{
	auto angle = [&](vector<vpcit>::iterator it)
	{
		Point p1 = *(*it);
		Point p2 = *(*(it+1));
		//acos(p1, )
		return 0;
	};
	//1st case
//angle(p_minx, p_minx+1, p_minx+1.y*(0, 1)); // (1, 0), (0, -1), (-1, 0)

//iterator pivot = min_element(Four., [](i, j)
//	{ return angle(i, i+1, v0(i)) < angle(j, j+1, v0(j));});
    vpcit i;
    return i;
}
void testcase(size_t n)
{
	vector<Point> dataset;
	while(n--)
	{
		Point p;
		cin >> p;
		dataset.push_back(p);
	}

	vector<Point> CH = FindConvexHull(dataset); // sorted clockwise

	vector<vpcit> FourMost = FindFourMostV(CH); // sorted clockwise

	vector<Point> rec = InitCaliper(FourMost);

	vector<float> Area;
	vector<float> Perimeter;
    size_t i = CH.size();
	while(i--)
	{
		vpcit next_vertex = RotateCaliper (CH, FourMost, rec);// clockwise

//		vector<Point> Rec = FindRec(CH, FourMost, next_vertex);
//		UpdateFourMost(next_vertex, FourMost);
//		vector<Vec> v1 = {(rec_i.x - pi.x, rec_i.y - pi.y), 
//		              (rec_j,x - pj.x, rec_j.y - pj.y), ... };

//		Area.push_back(FindArea(Rec));
//		Perimeter.push_back(FindPerimeter(Rec));
	}

	vector<float>::iterator min = min_element(Area.begin(), Area.end());
    cout << *min;
	min = min_element(Perimeter.begin(), Perimeter.end());
    cout << " " << *min << endl;
}

int main()
{
	size_t n;
	while (cin >> n)
	{
		if (n==0) break;

		testcase(n);
	}
    return 0;
}