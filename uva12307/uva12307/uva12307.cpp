//uva12307
// http://datagenetics.com/blog/march12014/index.html

// find 4 most vertices(lower, left, upper, right) (sorting)
// find the min angle formed by the above vertices and the coordination axies (atan2)
// rotate the caliper clockwise, and find one edge of the rectangle, and then its 4 points:
// - find the angle theta formed by pi, pi+1, pj
// - the length of line formed by (pj, P-1) is the projection of line(pi,pj) against line (pi, pi+1) by theta degrees
// - find P-1's coordination 
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
#include <iterator>

using namespace std;

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
    friend float dot(const Vec& v1, const Vec& v2)
    {
        return v1.u*v2.u + v1.v*v2.v;
    }
    friend float len(const Vec& v)
    {
        return hypot(v.u, v.v);
    }
    friend Vec scaler(Vec& v, float s)
    {
        return Vec(v.u * s, v.v * s);
    }
    friend Point end_point(Point& p, Vec& v)
    {
        return Point(p._x + v.u, p._y + v.v);
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
vector<Point> InitCaliper(vector<vpcit> Four) // initial caliper is perpendiclar to X and Y axes
{
    vector<Point> vp;// (4, Point(0.0f, 0.0f));
    std::transform(Four.begin(), Four.end(), back_inserter<vector<Point>>(vp), [](vpcit i){ return *i; });

    return vector<Point>({ 
        { vp[0]._x, vp[1]._y }, 
        { vp[2]._x, vp[1]._y },
        { vp[2]._x, vp[3]._y },
        { vp[0]._x, vp[3]._y }});
}
vpcit RotateCaliper(const vector<Point>& CH, const vector<vpcit>& Four, const vector<Point>& caliper)
{
    typedef tuple<Point, vpcit, vpcit> Tangent;

    vector<Tangent> tangentVector({
        Tangent(caliper[0], Four[0], Four[0] + 1),
        Tangent(caliper[1], Four[1], Four[1] + 1),
        Tangent(caliper[2], Four[2], Four[2] + 1),
        Tangent(caliper[3], Four[3], Four[3] + 1)
    });

	auto angle = [](Tangent& t) // what if p_rec is the same as p????
	{
        Point p_rec = get<0>(t);
		Point p = *(get<1>(t));
        Point p_next = *(get<2>(t));
        return atan2(fabs(cross(Vec(p, p_next), Vec(p, p_rec))), dot(Vec(p, p_next), Vec(p, p_rec)));
   	};

    vector<float> vf;
    std::transform(tangentVector.begin(), tangentVector.end(), back_inserter<vector<float>>(vf), angle);

    auto small = min_element(vf.begin(), vf.end());

    auto d = distance(vf.begin(), small);
    
    return get<1>(tangentVector[d]);
}
vector<Point> FindRec(const vector<Point>& CH, const vector<vpcit>& Four, vpcit next)
{
    vpcit i = next - 1;
    vpcit index_in_Four = *(find(Four.begin(), Four.end(), i));
    vpcit next_in_Four = index_in_Four + 1;

    Point p = *(index_in_Four);
    Point p_next = *next;
    Point p_next_in_Four = *(next_in_Four);

    float length_of_p_to_p_next = len(Vec(p, p_next));
    float length_of_p_to_rec_vertex = dot(Vec(p, p_next), Vec(p, p_next_in_Four)) / length_of_p_to_p_next;

    Point p_rec = length_of_p_to_rec_vertex > length_of_p_to_p_next ?
        end_point(p, scaler(Vec(p, p_next), length_of_p_to_rec_vertex / length_of_p_to_p_next))
        : p_next;

    vector<Point> ret;
    ret.push_back(p_rec);

    do
    {
        p = p_rec;
        p_next = p_next_in_Four;
        p_next_in_Four = *(next_in_Four + 1);
    }
    while ()


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

	vector<Point> caliper = InitCaliper(FourMost);

	vector<float> Area;
	vector<float> Perimeter;
    size_t i = CH.size();
	while(i--)
	{
		vpcit next_vertex = RotateCaliper (CH, FourMost, caliper);// clockwise

		vector<Point> Rec = FindRec(CH, FourMost, next_vertex);
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