#include <iostream>
#include <cmath>
#include <vector>
#include <istream>
//#include <boost/test/unit_test.hpp>
#include <fstream>
#include <math.h>

const float flt_tolerance = 0.0001;

struct point_t { //(x, y)
    float x = NAN, y = NAN, z = NAN;

    point_t(){
        x = NAN;
        y = NAN;
        z = NAN;
    }

    point_t(float x0, float y0, float z0)
    {
        x = x0;
        y = y0;
        z = z0;
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
    }

    bool is_valid() const {
        if (_finite(x) == 0|| _finite(y) == 0 || _finite(z) == 0)
            return false;
        return true;
    }

    bool is_equal(const point_t &rhs) const {
        if (std::abs(x - rhs.x) < flt_tolerance && std::abs(y - rhs.y) < flt_tolerance && std::abs(z - rhs.z) < flt_tolerance)
            return true;
        return false;
    }
};

struct plane_t { //Ax + Bx + Cz + D = 0
    float A = 0.0f, B = 0.0f, C = 0.0f, D = 0.0f;

    plane_t(){}

    plane_t (float a, float b, float c, float d)
    {
        A = a;
        B = b;
        C = c;
        D = d;
    }

    plane_t(point_t const &p1, point_t const &p2, point_t const &p3)//building plane on 3 points
    {
        A = (p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z);
        B = (p3.x - p1.x) * (p2.z - p1.z) - (p2.x - p1.x) * (p3.z - p1.z);
        C = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
        D = -1 * p1.x * ((p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z)) -
            p1.y * ((p3.x - p1.x) * (p2.z - p1.z) - (p2.x - p1.x) * (p3.z - p1.z)) -
            p1.z * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
    }

    bool is_valid () const {
        if (A == 0 && B == 0 && C == 0) {

            return false;
        }
        return true;
    }

    bool is_parallel (plane_t plane) const {
        float kA = NAN, kB = NAN, kC = NAN;
        if (!plane.is_valid())
            return false;
        if (plane.A != 0) {
            kA = A / plane.A;}
        if (plane.B != 0){
            kB = B / plane.B;}
        if (plane.C != 0)
            kC = C / plane.C;
        if (kA == kB == kC)
            return true;

        if (plane.A == 0 && A != 0)
            return false;
        if (plane.B == 0 && B != 0)
            return false;
        if (plane.C == 0 && C != 0)
            return false;
        return true;
    }

    bool is_equal (plane_t plane) const {
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
        if (D / plane.D == k){
            return true;
        }
        return false;
    }

    void print() const {
        std::cout << A << "x + " << B << "y + " << C << "z + " << D << " = 0" << std::endl;
    }
};

struct line_t { // (x - x0) / ax = (y - y0) / ay = (z - z0) / az
    float x0 = 0.0f, y0 = 0.0f, z0 = 0.0f;
    float ax = 1.0f, ay = 1.0f, az = 1.0f;

    line_t(){}

    line_t(const point_t &p1, const point_t &p2) // construct line on two points
    {
        ax = p2.x - p1.x;
        ay = p2.y - p1.y;
        az = p2.z - p1.z;
        x0 = p1.x;
        y0 = p1.y;
        z0 = p1.z;
    }

    line_t(const plane_t &p1, const plane_t &p2) // construct line on two planes
    {
        ax = p1.B * p2.C - p1.C * p2.B;
        ay = -1 * (p1.A * p2.C - p1.C * p2.A);
        az = p1.A * p2.B - p1.B * p2.A;
        y0 = (p2.A * p1.D / p1.A - p2.D) / (-p2.A * p1.B / p1.A + p2.B);
        x0 = (-p1.D - p1.B * y0) / p1.A;
        z0 = 0.0f;
    }

    point_t intersection(line_t line) const// finding of crossing point of two lines
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

    point_t projection_p (point_t p) const {
        if (!is_valid())
        {
            point_t in_val;
            return in_val;
        }
       float d = - (ax * p.x + ay * p.y + az * p.z);
       float k = (-d - ax * x0 - ay * y0 - ax * z0) / (ax * ax + ay * ay + az * az);
       float x = ax * k + x0;
       float y = ay * k + y0;
       float z = az * k + z0;
       point_t proj{x, y, z};
       return proj;

    }

    void print () const {
        std::cout << "x0 = " << x0 << ", "  << "y0 = " << y0 << ", " << "z0 = " << z0 << ";" << std::endl;
        std::cout << "ax = " << ax << ", "  << "ay = " << ay << ", " << "az = " << az << ";" << std::endl;
    }

    bool is_valid() const {
        if (ax == 0 && ay == 0 && az == 0)
            return false;
        return true;
    }
};

struct vector_t{
    point_t p1, p2;

    vector_t(){}

    vector_t (const point_t& pt1, const point_t pt2)
    {
        p1.x = pt1.x;
        p1.y = pt1.y;
        p1.z = pt1.z;
        p2.x = pt2.x;
        p2.y = pt2.y;
        p2.z = pt2.z;
    }

    float compx() const{
        return p2.x - p1.x;
    }
    float compy() const{
        return p2.y - p1.y;
    }
    float compz() const{
        return p2.z - p1.z;
    }

    float length() const{
        return sqrt((p2.x-p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
    }

    bool is_valid() {
        if (p1.is_valid() && p2.is_valid())
            return true;
        return false;
    }

    bool is_codir (const vector_t vector) const{ // check co-direction of parallel vectors
        if (vector.compx() * compx() + vector.compy() * compy() +  vector.compz() * compz() > 0) // scalar product
            return true;
        return false;
    }

    bool is_crossing(const vector_t& vec){ // check intersection of sections lying on one line
        vector_t A1A2 {p1, vec.p1}, A1B1 {p1, p2}, B1A2 {p2, vec.p1}, A1B2 {p1, vec.p2}, B1B2 {vec.p2, vec.p2};
        if ((A1A2.length() <= A1B1.length() && B1A2.length() <= A1A2.length()) || (A1B2.length() <= A1A2.length() && B1B2.length() <= A1A2.length()))
            return true;
        else
            return false;
    }

    void print()
    {
        p1.print();
        p2.print();
    }
};

struct triangle_t {
    point_t A, B, C;
    plane_t plane;
    line_t AB, AC, BC;

    triangle_t(const point_t &p1, const point_t &p2, const point_t &p3) {
        A = p1;
        B = p2;
        C = p3;
        plane_t new_plane{A, B, C};
        plane = new_plane;
        line_t lAB{A,B}, lBC{B, C}, lAC{A, C};
        AB = lAB;
        BC = lBC;
        AC = lAC;
    }

    bool is_valid() const{
        if(!A.is_valid() || !B.is_valid() || !C.is_valid())
            return false;
        if (A.is_equal(B) || B.is_equal(C) || C.is_equal(A))
            return false;
        if (!plane.is_valid())
            return false;
        return true;
    }

    vector_t vec_cross_l (line_t cross_l) const{
        vector_t vector;

        if (!is_valid())
        {
            std::cout << "Triangle is not valid\n";
            return vector;
        }

        point_t proj_A = cross_l.projection_p(A);
        vector_t vecA {A, proj_A};
        vecA.print();
        std:: cout <<"- vecA\n";
        point_t proj_B = cross_l.projection_p(B);
        vector_t vecB {B, proj_B};
        vecB.print();
        std:: cout <<"-vecB\n";
        point_t proj_C = cross_l.projection_p(C);
        vector_t vecC {C, proj_C};
        vecC.print();
        std:: cout <<"-vecC\n";
        point_t p1, p2, p3;
        if (!vecB.is_codir(vecA))
        {
            std::cout << "p1\n";
            AB.print();
            cross_l.print();
            p1 = AB.intersection(cross_l);
        }
        if (!vecA.is_codir(vecC))
        {
            std::cout << "p2";
            p2 = AC.intersection(cross_l);
        }
        if (!vecC.is_codir(vecB))
        {
            std::cout << "p3";
            BC.print();
            cross_l.print();
            std::cout << "\n";
            p3 = BC.intersection(cross_l);
        }
        p1.print();
        p2.print();
        p3.print();

        if (p1.is_valid() && p2.is_valid())
        {
            std::cout << p2.is_valid();
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
            //std::cout << p3.is_valid();
            vector_t new_vec{p1, p3};
            vector = new_vec;
            return vector;
        }
        return vector;
    }

    void print()
    {
        A.print();
        B.print();
        C.print();
    }
};

std::istream &operator>>(std::istream &stream, point_t &point) {
    stream >> point.x;
    stream >> point.y;
    stream >> point.z;
    return stream;
}

bool check_crossing_eq_plane(const triangle_t& t1, const triangle_t& t2) {
    vector_t vec_cross, vec_AB{t1.A, t1.B}, vec_AC{t1.A, t1.C}, vec_BC{t1.B, t1.C};

    vec_AB.print();
    std::cout << " - AB" << std::endl;
    vec_AC.print();
    std::cout << " - AC" << std::endl;
    vec_BC.print();
    std::cout << " - BC" << std::endl;

    if ((vec_cross = t2.vec_cross_l(t1.AB)).is_valid())
    {
        if (vec_cross.is_crossing(vec_AB))
            return true;
        return false;
    }
    if ((vec_cross = t2.vec_cross_l(t1.AC)).is_valid())
    {
        if (vec_cross.is_crossing(vec_AC))
            return true;
        return false;
    }
    if ((vec_cross = t2.vec_cross_l(t1.BC)).is_valid())
    {
        if (vec_cross.is_crossing(vec_BC))
            return true;
        return false;
    }

    point_t proj1_AB  = t1.AB.projection_p(t1.C);
    point_t proj1_AC  = t1.AC.projection_p(t1.B);
    point_t proj1_BC  = t1.BC.projection_p(t1.A);
    point_t proj2_AB  = t1.AB.projection_p(t2.A);
    point_t proj2_AC  = t1.AC.projection_p(t2.A);
    point_t proj2_BC  = t1.BC.projection_p(t2.A);

    vector_t n1_AB{proj1_AB, t1.C}, n1_AC{proj1_AC, t1.B}, n1_BC{proj1_BC, t1.A}, n2_AB{proj2_AB, t2.A}, n2_AC{proj2_AC, t2.A}, n2_BC{proj2_BC, t2.A};
    if (n1_AB.is_codir(n2_AB) && n1_AC.is_codir(n2_AC) && n1_BC.is_codir(n2_BC))
        return true;
    std::cout << "nothing" << std::endl;
    return false;
}

bool check_crossing(const triangle_t &t1, const triangle_t &t2) {
    if (t1.plane.is_parallel(t2.plane) && !(t1.plane.is_equal(t2.plane))){
        t1.plane.print();
        std::cout << std::endl;
        t2.plane.print();
        std::cout << std::endl;
        return false;}

    if (t1.plane.is_equal(t2.plane))
    {
        t1.plane.print();
        std::cout << std::endl;
        t2.plane.print();
        std::cout << std::endl;
        std::cout << "same plane" << std::endl;
        return check_crossing_eq_plane(t1, t2);
    }

    line_t cross_l{t1.plane, t2.plane};

    point_t pA1, pB1, pC1, pA2, pB2, pC2;

    std::cout << "cross_l :";
    cross_l.print();
    std::cout << std::endl;

    vector_t vec1 = t1.vec_cross_l(cross_l);
    vector_t vec2 = t2.vec_cross_l(cross_l);

    if (!vec1.is_valid() || !vec2.is_valid()) //check if the t1 and t2 crossed by cross_l
        return false;
    if (vec1.is_crossing(vec2))
        return true;
    std::cout << "nothing" << std::endl;
    return false;
}

int main() {
    int N;
    std::ifstream fin ("D:\\Clion\\Triangles\\test.txt");

    if (!fin){
        std::cout << "Failed to open file" << std::endl;
        return 1;
    }

    fin >> N;
    std::cout << "N = " << N <<std::endl;
    std::vector<triangle_t> list;
    point_t p1{1, 2, 0}, p2{4, 5, 0}, p3{4, 2, 0}, pl1{0, 3, 0}, pl2{1, 3, 0};


    /*point_t c1{0, 3, 0}, c2{3, 6, 0}, c3{0, 5, 0}, c4{3, 2, 0}, c;
    line_t l1 {c1, c2}, l2{c3, c4};
    c = l1.intersection(l2);
    l1.print();
    std::cout << std::endl;
    l2.print();
    c.print();
    std::cout << std::endl;*/

    triangle_t trig{p1, p2, p3};

    trig.print();
    std:: cout <<"\n";

    std::cout << trig.is_valid();

    line_t line{pl1, pl2};
    line.print();

    vector_t vec = trig.vec_cross_l(line);

    vec.print();
    /*point_t p1A, p1B, p1C, p2A, p2B, p2C;
    std::cin >> p1A >> p1B >> p1C >> p2A >> p2B >> p2C;

    plane_t plane1{1, 2, 3, 6}, plane2 {5, 6, 7, 0}, plane3{5, 44, 6, 8};

    plane1.print();
    plane2.print();
    plane3.print();

    line_t line1 {plane1, plane2};
    line1.print();

    line_t line2 {plane1, plane3};
    line2.print();

    point_t cross1 = line1.intersection(line2);
    point_t cross2 = line2.intersection(line1);

    cross1.print();
    cross2.print();

    point_t point{1, 2, 3};

    point_t proj = line1.projection_p(point);

    proj.print();*/

    /*for (int i = 0; i < N; i++) {
        std::cout << i << " triangle" << std::endl;
        fin >> p1 >> p2 >> p3;
        p1.print();
        std::cout << " ";
        p2.print();
        std::cout << " ";
        p3.print();
        std::cout << " " << std::endl;
        triangle_t triangle(p1, p2, p3);
        bool c = false;

       for (int k = 0; k < list.size(); k++) {
           std::cout << "list_size = " <<list.size() << std::endl;
            if (c = check_crossing(list[k], triangle))
            {
                std::cout << k << std::endl;
                //break;
            }
            std::cout << c << std::endl;
        }
        list.push_back(triangle);
    }*/
    return 0;
};
