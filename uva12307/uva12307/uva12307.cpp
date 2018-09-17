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
int main()
{
    return 0;
}