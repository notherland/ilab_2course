#include "Triangles.h"

//point_t

std::istream& operator >> (std::istream &in, point_t& p){
    in >> p.x;
    in >> p.y;
    in >> p.z;

    return in;
}

bool point_t::is_equal (const point_t& p) const{

    if (fabs(x - p.getx()) > flt_tolerance || fabs(y - p.gety()) > flt_tolerance || fabs(z - p.getz()) > flt_tolerance)
        return false;
    return true;
}

bool point_t::is_valid() const{
    if (finitef(x) == 0|| finitef(y) == 0 || finitef(z) == 0)
        return false;
    return true;
}

//plane_t
bool plane_t::is_parallel (plane_t plane) const {
    float kA = NAN, kB = NAN, kC = NAN;
    if (!plane.is_valid())
        return false;
    if (plane.getA() != 0) {
        kA = A / plane.getA();}
    if (plane.getB() != 0){
        kB = B / plane.getB();}
    if (plane.getC() != 0)
        kC = C / plane.getC();
    if (finitef(kA) != 0 && finitef(kB) != 0 && fabs(kA - kB) > flt_tolerance)
        return false;
    if (finitef(kA) != 0 && finitef(kC) != 0 && fabs(kA - kC) > flt_tolerance)
        return false;
    if (finitef(kB) != 0 && finitef(kC) != 0 && fabs(kB - kC) > flt_tolerance)
        return false;
    if (plane.getA() == 0 && A != 0)
        return false;
    if (plane.getB() == 0 && B != 0)
        return false;
    if (plane.getC() == 0 && C != 0)
        return false;

    return true;
}

bool plane_t::is_equal (plane_t plane) const {
    if (!is_parallel(plane))
        return false;
    float k;
    if (plane.A != 0) {
        if (A == 0)
            return false;
        k = A / plane.A;
    }
    if (plane.B != 0){
        if (B == 0)
            return false;
        k = B / plane.B;}
    if (plane.C != 0){
        if (C == 0)
            return false;
        k = C / plane.C;}
    if (D == 0){
        if (plane.D == 0)
            return true;
        return false;
    }
    if (abs (D / plane.D - k) <= flt_tolerance){
        return true;
    }
    return false;
}

bool plane_t::is_valid () const {
    if (A == 0 && B == 0 && C == 0) {
        return false;
    }
    return true;
}

void plane_t::print() const {
    std::cout << A << "x + " << B << "y + " << C << "z + " << D << " = 0" << std::endl;
}

//line_t

point_t line_t::intersection(line_t line) const
{
    point_t in_val;
    if (!is_valid() || !line.is_valid()){
        return in_val;
    }

    float x = NAN, y = NAN, z = NAN, a = NAN, b = NAN;
    if (ax == 0)
    {
        if (line.ax == 0)
        {
            if (x0 == line.x0)
                x = x0;
            else
                return in_val;
        }
        else
            b = (x0 - line.x0) / line.ax;
        x = x0;
        y = line.y0 + b * line.ay;
        z = line.z0 + b * line.az;
        if (ay == 0)
        {
            if (y0 != y)
                return in_val;
        }
        if (az == 0){
            if (z0 != z)
                return in_val;
        }
        point_t point{x, y, z};
        return point;
    }
    x = ((x0 * ay / ax - line.x0 * line.ay / line.ax) + line.y0 - y0) / (ay / ax - line.ay / line.ax);
    y = (x - x0) * ay / ax + y0;
    z = (x - x0) * az / ax + z0;

    point_t point{x, y, z};
    return point;
}

point_t line_t::projection_p (point_t p) const {
    if (!is_valid() || !p.is_valid())
    {
        point_t in_val;
        return in_val;
    }
    float k = (ax * p.getx() + ay * p.gety() + az * p.getz() - (ax * x0 + ay * y0 + az * z0)) / (ax * ax + ay * ay + az * az);
    float x = ax * k + x0;
    float y = ay * k + y0;
    float z = az * k + z0;
    point_t proj{x, y, z};
    return proj;
}

void line_t::print () const {
    std::cout << "x0 = " << x0 << ", "  << "y0 = " << y0 << ", " << "z0 = " << z0 << ";" << std::endl;
    std::cout << "ax = " << ax << ", "  << "ay = " << ay << ", " << "az = " << az << ";" << std::endl;
}

bool line_t::is_valid() const {
    if (ax == 0 && ax == 0 && ay == 0)
        return false;
    return true;
}

//vector_t

bool vector_t::is_codir (const vector_t vector) const{
    float scalar_prod = vector.compx() * compx() + vector.compy() * compy() +  vector.compz() * compz();
    if (scalar_prod >= flt_tolerance)
        return true;
    return false;
}

bool vector_t::is_crossing(const vector_t& vec) const{
    vector_t A1A2 {p1, vec.p1}, A1B1 {p1, p2}, B1A2 {p2, vec.p1}, A1B2 {p1, vec.p2}, B1B2 {p2, vec.p2}, A2B2{vec.p1, vec.p2};
    if ((A1A2.length() <= A1B1.length() && B1A2.length() <= A1B1.length()) || (A1B2.length() <= A1B1.length() && B1B2.length() <= A1B1.length()) || (A1A2.length() <= A2B2.length() && A1B2.length() <= A1A2.length()))
        return true;
    else
        return false;
}

void vector_t::print() const{ //print
    p1.print();
    p2.print();
}

bool vector_t::is_equal (const vector_t& vec) const{
    if ((vec.getp1().is_equal(p1) && vec.getp2().is_equal(p2)) || (vec.getp1().is_equal(p2) && vec.getp2().is_equal(p1)))
        return true;
    return false;
}

bool vector_t::is_valid() const{
    if (p1.is_valid() && p2.is_valid())
        return true;
    return false;
}

//triangle_t

vector_t triangle_t::vec_cross_l (line_t cross_l) const{
    vector_t vector;

    if (!is_valid())
    {
        std::cout << "Triangle is not valid\n";
        print();
        return vector;
    }

    point_t proj_A = cross_l.projection_p(A);
    vector_t vecA {A, proj_A};
    point_t proj_B = cross_l.projection_p(B);
    vector_t vecB {B, proj_B};
    point_t proj_C = cross_l.projection_p(C);
    vector_t vecC {C, proj_C};
    point_t p1, p2, p3;

    /*vecA.print();
    std::cout << " - vecA\n";
    vecB.print();
    std::cout << " - vecB\n";
    vecC.print();
    std::cout << " - vecC\n";*/


    if (!vecB.is_codir(vecA)){
        p1 = AB.intersection(cross_l);
    }
    if (!vecA.is_codir(vecC)){
        p2 = AC.intersection(cross_l);
    }
    if (!vecC.is_codir(vecB)){
        p3 = BC.intersection(cross_l);
    }

    /*p1.print();
    std::cout << std::endl;
    p2.print();
    std::cout << std::endl;
    p3.print();
    std::cout << std::endl;*/

    if (p1.is_valid() && p2.is_valid())
    {
        vector_t new_vec{p1, p2};
        vector = new_vec;
        return vector;
    }
    if (p2.is_valid() && p3.is_valid())
    {
        vector_t new_vec{p2, p3};
        vector = new_vec;
        return vector;
    }
    if (p1.is_valid() && p3.is_valid())
    {
        vector_t new_vec{p1, p3};
        vector = new_vec;
        return vector;
    }
    return vector;
}

bool triangle_t::is_valid() const{
    if(!A.is_valid() || !B.is_valid() || !C.is_valid())
        return false;
    if (A.is_equal(B) || B.is_equal(C) || C.is_equal(A))
        return false;
    if (!plane.is_valid())
        return false;
    return true;
}

void triangle_t::print() const {
    A.print();
    B.print();
    C.print();
}
