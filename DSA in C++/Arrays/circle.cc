//
// Basic Predicates for Circles
//
// This program provides common geometry functions involving circles:
// 1. Circle-Circle intersection
// 2. Line-Circle intersection
// 3. Tangents from a point to a circle
//

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>

using namespace std;

// ------------------------------------------------------------
// A 2D point is represented using complex<double>
//
// Example:
// point p(3, 4);
// real(p) -> x-coordinate = 3
// imag(p) -> y-coordinate = 4
// ------------------------------------------------------------
using point = complex<double>;

// ------------------------------------------------------------
// EPS is used for floating-point comparison.
//
// Floating-point numbers are not always exact.
// For example, mathematically 0.1 + 0.2 = 0.3,
// but computers may store a slightly different value.
//
// EPS lets us treat very small values as zero.
// ------------------------------------------------------------
const double EPS = 1e-8;

// ------------------------------------------------------------
// sign(x)
//
// Returns:
//  1  -> x is positive
//  0  -> x is approximately zero
// -1  -> x is negative
// ------------------------------------------------------------
int sign(double x)
{
    if (x < -EPS)
        return -1;

    if (x > EPS)
        return 1;

    return 0;
}

// ------------------------------------------------------------
// Dot product
//
// For vectors:
// p = (px, py)
// q = (qx, qy)
//
// dot(p, q) = px*qx + py*qy
//
// Useful for:
// - angles
// - projections
// - perpendicularity
// ------------------------------------------------------------
double dot(point p, point q)
{
    return real(conj(p) * q);
}

// ------------------------------------------------------------
// Cross product (2D)
//
// cross(p, q) = px*qy - py*qx
//
// Useful for:
// - determining orientation
// - checking clockwise/counter-clockwise
// - finding intersection geometry
// ------------------------------------------------------------
double cross(point p, point q)
{
    return imag(conj(p) * q);
}

// ------------------------------------------------------------
// Circle
//
// p = center of circle
// r = radius
// ------------------------------------------------------------
struct circle
{
    point p;
    double r;
};

// ------------------------------------------------------------
// Line
//
// p and q are two points on the line.
//
// The line is represented parametrically as:
//
//     L(t) = p + t(q - p)
//
// ------------------------------------------------------------
struct line
{
    point p;
    point q;
};

// ============================================================
// 1. CIRCLE - CIRCLE INTERSECTION
// ============================================================
//
// Returns:
// - empty vector {}    -> no intersection
// - one point          -> circles touch
// - two points         -> circles intersect at two points
//
// Example:
//
//        Circle A         Circle B
//           ◯               ◯
//            \             /
//             \           /
//              ●         ●
//                 \   /
//                  ...
//
// ------------------------------------------------------------
vector<point> intersect(circle C, circle D)
{

    // Distance between the two centers
    double d = abs(C.p - D.p);

    // --------------------------------------------------------
    // CASE 1: Circles are too far apart
    //
    // If:
    //     d > r1 + r2
    //
    // they cannot intersect.
    //
    // The original formula is written using sign()
    // to handle floating-point precision.
    // --------------------------------------------------------
    if (sign(d - C.r - D.r) > 0)
        return {};

    // --------------------------------------------------------
    // CASE 2: One circle is completely inside the other
    // or they touch internally.
    //
    // If:
    //     d <= |r1 - r2|
    //
    // there is no proper two-circle intersection.
    //
    // For this implementation, internal touching is also
    // treated as no result.
    // --------------------------------------------------------
    if (sign(d - abs(C.r - D.r)) <= 0)
        return {};

    // --------------------------------------------------------
    // 'a' is the distance from C's center to the chord
    // where the two circles intersect.
    //
    // Formula:
    //
    //       r1² - r2² + d²
    // a = -------------------
    //           2d
    // --------------------------------------------------------
    double a = (C.r * C.r - D.r * D.r + d * d) / (2 * d);

    // --------------------------------------------------------
    // 'h' is the distance from the chord midpoint
    // to either intersection point.
    //
    //         h = sqrt(r1² - a²)
    // --------------------------------------------------------
    double h = sqrt(max(C.r * C.r - a * a, 0.0));

    // --------------------------------------------------------
    // Direction from D's center to C's center.
    //
    // Dividing by d converts it into a unit vector.
    // --------------------------------------------------------
    point v = (C.p - D.p) / d;

    // --------------------------------------------------------
    // CASE: Circles touch externally
    //
    // h == 0 means there is only one intersection point.
    // --------------------------------------------------------
    if (sign(h) == 0)
        return {C.p + v * a};

    // --------------------------------------------------------
    // Two intersection points.
    //
    // Multiplication by point(0, 1) rotates a complex number
    // by +90 degrees.
    // --------------------------------------------------------
    point intersection1 =
        C.p + v * a + point(0, 1) * v * h;

    point intersection2 =
        C.p + v * a - point(0, 1) * v * h;

    return {intersection1, intersection2};
}

// ============================================================
// 2. LINE - CIRCLE INTERSECTION
// ============================================================
//
// We represent the line as:
//
//     P(t) = L.p + t(L.q - L.p)
//
// We then solve:
//
//     |P(t) - C.p|² = r²
//
// This produces a quadratic equation.
//
// Depending on its discriminant:
//
//     discriminant < 0  -> no intersection
//     discriminant = 0  -> one intersection (tangent)
//     discriminant > 0  -> two intersections
//
// ------------------------------------------------------------
vector<point> intersect(line L, circle C)
{

    // --------------------------------------------------------
    // u = direction of the line
    //
    // L.p - L.q is used here instead of L.q - L.p.
    // Either direction works as long as the equations
    // are consistent.
    // --------------------------------------------------------
    point u = L.p - L.q;

    // Vector from circle center to first line point
    point v = L.p - C.p;

    // --------------------------------------------------------
    // These values form the quadratic equation:
    //
    //     a*t² + 2*b*t + c = r²
    //
    // Here:
    //
    //     a = |u|²
    //     b = dot(u, v)
    //     c = |v|²
    // --------------------------------------------------------
    double a = norm(u);
    double b = dot(u, v);
    double c = norm(v);

    // --------------------------------------------------------
    // Rearranging gives the discriminant:
    //
    //     det = b² - a(c - r²)
    //
    // This is the quantity that determines the number
    // of intersections.
    // --------------------------------------------------------
    c -= C.r * C.r;

    double det = b * b - a * c;

    // --------------------------------------------------------
    // No intersection
    // --------------------------------------------------------
    if (sign(det) < 0)
        return {};

    // --------------------------------------------------------
    // One intersection
    //
    // The line is tangent to the circle.
    // --------------------------------------------------------
    if (sign(det) == 0)
    {

        double t = -b / a;

        return {
            L.p + t * (L.q - L.p)};
    }

    // --------------------------------------------------------
    // Two intersections
    //
    // Quadratic formula:
    //
    // t = (-b ± sqrt(det)) / a
    // --------------------------------------------------------
    double sqrtDet = sqrt(det);

    double t1 = (-b + sqrtDet) / a;
    double t2 = (-b - sqrtDet) / a;

    point intersection1 =
        L.p + t1 * (L.q - L.p);

    point intersection2 =
        L.p + t2 * (L.q - L.p);

    return {
        intersection1,
        intersection2};
}

// ============================================================
// 3. TANGENTS FROM A POINT TO A CIRCLE
// ============================================================
//
// Given:
//     point p
//     circle C
//
// Find the point(s) on the circle where tangent lines
// from p touch the circle.
//
// Possible cases:
//
//     p inside circle  -> 0 tangents
//     p on circle      -> 1 tangent
//     p outside circle -> 2 tangents
//
// ------------------------------------------------------------
vector<point> tangent(point p, circle C)
{

    // --------------------------------------------------------
    // Distance² from p to the center.
    // --------------------------------------------------------
    double distanceSquared = norm(p - C.p);

    // --------------------------------------------------------
    // sin²(theta) = r² / d²
    //
    // We use squared values so we don't need to calculate
    // the distance first.
    // --------------------------------------------------------
    double sin2 = (C.r * C.r) / distanceSquared;

    // --------------------------------------------------------
    // CASE 1: Point is inside the circle.
    //
    // r² > d²
    // therefore there are no real tangents.
    // --------------------------------------------------------
    if (sign(1 - sin2) < 0)
        return {};

    // --------------------------------------------------------
    // CASE 2: Point lies exactly on the circle.
    //
    // There is only one tangent point: p itself.
    // --------------------------------------------------------
    if (sign(1 - sin2) == 0)
        return {p};

    // --------------------------------------------------------
    // CASE 3: Point is outside the circle.
    //
    // There are two tangent points.
    //
    // z represents a rotation/scaling factor:
    //
    //     sqrt(1 - sin²(theta)) = cos(theta)
    //     sqrt(sin²(theta))       = sin(theta)
    //
    // Therefore:
    //
    //     z = (cos(theta), sin(theta))
    // --------------------------------------------------------
    point z(
        sqrt(1 - sin2),
        sqrt(sin2));

    // --------------------------------------------------------
    // Rotate the vector (C.p - p) in both directions.
    //
    // conj(z) gives rotation in the opposite direction.
    // --------------------------------------------------------
    point tangent1 =
        p + (C.p - p) * conj(z);

    point tangent2 =
        p + (C.p - p) * z;

    return {
        tangent1,
        tangent2};
}

// ============================================================
// MAIN
// ============================================================

int main()
{

    // --------------------------------------------------------
    // Example 1: Circle-Circle Intersection
    // --------------------------------------------------------

    circle C1{{0, 0}, 5};
    circle C2{{6, 0}, 5};

    vector<point> result = intersect(C1, C2);

    cout << "Circle-Circle Intersection:\n";

    for (point p : result)
    {
        cout << "("
             << real(p)
             << ", "
             << imag(p)
             << ")\n";
    }

    // --------------------------------------------------------
    // Example 2: Line-Circle Intersection
    // --------------------------------------------------------

    line L{{-10, 0}, {10, 0}};

    vector<point> result2 =
        intersect(L, C1);

    cout << "\nLine-Circle Intersection:\n";

    for (point p : result2)
    {
        cout << "("
             << real(p)
             << ", "
             << imag(p)
             << ")\n";
    }

    // --------------------------------------------------------
    // Example 3: Tangents from a point to a circle
    // --------------------------------------------------------

    point P(10, 0);

    vector<point> result3 =
        tangent(P, C1);

    cout << "\nTangent Points:\n";

    for (point p : result3)
    {
        cout << "("
             << real(p)
             << ", "
             << imag(p)
             << ")\n";
    }

    return 0;
}