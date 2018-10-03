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

template <typename T>
class _Point
{
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
    	return a._y < b._y || (a._y == b._y && a._x > b._x);
    }

    //template <typename>
    //friend class _Vec;
public:
    _Point(const T& x, const T& y) : _x(x), _y(y) {}
    const T& x() const { return _x; }
    const T& y() const { return _y; }
private:
    T _x;
	T _y;
};
typedef _Point<float> Point;

template <typename T>
class _Vec
{
	friend T cross(const _Vec& v1, const _Vec& v2)
	{
		return v1.u*v2.v - v2.u*v1.v;
	}
    friend T dot(const _Vec& v1, const _Vec& v2)
    {
        return v1.u*v2.u + v1.v*v2.v;
    }
    friend T len(const _Vec& v)
    {
        return hypot(v.u, v.v);
    }
    friend _Vec scaler(_Vec& v, T s)
    {
        return _Vec(v.u * s, v.v * s);
    }
    friend _Point<T> end_point(_Point<T>& p, _Vec& v)
    {
        return Point(p.x() + v.u, p.y() + v.v);
    }
    friend T angle(const _Vec& v1, const _Vec& v2)
    {
        return atan2(fabs(cross(v1, v2)), dot(v1, v2));
    }
public:
	_Vec(const _Point<T>& a, const _Point<T>& b): u(b.x() - a.x()), v(b.y() - a.y()) {}
    _Vec(const T& u, const T& v) : u(u), v(v) {}
private:
	T u;
	T v;
};
typedef _Vec<float> Vec;

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
    
    // clockwise: left-lower, top, right, bottom
    return vector<vpcit>({ pair_x.first, pair_y.second, pair_x.second, pair_y.first });
}
vector<Point> InitCaliper(const vector<vpcit>& Four) // initial caliper is perpendicular to X and Y axes
{
    vector<Point> vp;// (4, Point(0.0f, 0.0f));
    std::transform(Four.begin(), Four.end(), back_inserter<vector<Point>>(vp), 
        [](vpcit i) { return *i; });

    return vector<Point>({ //convex hull might have 2, 3, 4, ..., 8 points touch the caliper. 
        { vp[0].x(), vp[1].y() }, // left upper
        { vp[2].x(), vp[1].y() }, // right upper
        { vp[2].x(), vp[3].y() }, // right lower
        { vp[0].x(), vp[3].y() }});// left lower
}

template <typename T>
typename T::const_iterator adv1 (typename T::const_iterator i, const T& v)
{
    if (next(i) == v.end()) return v.begin();
    else return next(i);
};

vpcit RotateCaliper(const vector<Point>& CH, const vector<vpcit>& Four, const vector<Point>& caliper)
{
    typedef tuple<Point, vpcit, vpcit> Tangent;
    vector<Tangent> tangentVector({
        Tangent(caliper[0], Four[0], adv1(Four[0], CH)),
        Tangent(caliper[1], Four[1], adv1(Four[1], CH)),
        Tangent(caliper[2], Four[2], adv1(Four[2], CH)),
        Tangent(caliper[3], Four[3], adv1(Four[3], CH))
    });

	auto find_angle = [&](const Tangent& t) // what if p_rec is the same as p????
	{
        Point p_rec = get<0>(t);
		Point p = *(get<1>(t));
        Point p_next = *(adv1(get<1>(t), CH));
        float f = angle(Vec(p, p_next), Vec(p, p_rec));
        return f > 0.0 ? f : 4.0; //FIXME: limit of atan2 is PI, not 4.0
   	};

    vector<float> vf;
    std::transform(tangentVector.begin(), tangentVector.end(), back_inserter<vector<float>>(vf), 
        find_angle);

    auto small = min_element(vf.begin(), vf.end()); // edge case: what if the 4 angles are the same?

    auto d = distance(vf.begin(), small);
    
    return get<1>(tangentVector[d]);
}
vector<Point> FindRec(const vector<Point>& CH, const vector<vpcit>& Four, vpcit itr_min_angle_vertex)
{
    // one side of the rectangle is adherent to the edge of convex hull
    // need to find the first vertex of the rectangle

    vector<vpcit>::const_iterator itr_in_Four = find(Four.begin(), Four.end(), itr_min_angle_vertex);
    vector<vpcit> reordered_Four, reordered_Four_shift1;
    for (size_t n = 0; n<Four.size(); ++n)
    {
        reordered_Four.push_back(*itr_in_Four);
        itr_in_Four = adv1(itr_in_Four, Four);
        reordered_Four_shift1.push_back(*(itr_in_Four));
    }

    vector<Point> ret;
    std::transform(reordered_Four.begin(), reordered_Four.end(), reordered_Four_shift1.begin(),
        back_inserter<vector<Point>>(ret),
        [&](vpcit it, vpcit it_shift1){
            Point p = *it;
            Point p_next = *(adv1(it, CH));
            Point p_next_in_Four = *(it_shift1);

            float length_of_p_to_p_next = len(Vec(p, p_next)); //(a)
            float length_of_p_to_rec_vertex = dot(Vec(p, p_next), Vec(p, p_next_in_Four)) / length_of_p_to_p_next; //(b)
            // (a) < (b)
            // (a) == (b)
            // (a) > (b)
            Point p_rec = length_of_p_to_rec_vertex > length_of_p_to_p_next 
                ? end_point(p, scaler(Vec(p, p_next), length_of_p_to_rec_vertex / length_of_p_to_p_next))
                : p_next;
            return p_rec;
        });
    return ret;
}

void testcase(size_t n)
{
	vector<Point> dataset;
	while(n--)
	{
        Point p(0.0, 0.0);
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