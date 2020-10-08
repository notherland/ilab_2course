
#ifndef TRIANGLE_TRIANGLES_H
#define TRIANGLE_TRIANGLES_H

#endif //TRIANGLE_TRIANGLES_H

#include <iostream>
#include <cmath>
#include <vector>
#include <istream>
#include <fstream>

const float flt_tolerance = 0.0001;

class point_t { //(x, y)

    float x = NAN, y = NAN, z = NAN;

public:

    friend std::istream& operator>> (std::istream &in, point_t& p);

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

    float getx() const{
        return x;
    }
    float gety() const{
        return y;
    }
    float getz() const{
        return z;
    }

    void newp(const point_t& newp)
    {
        x = newp.getx();
        y = newp.gety();
        z = newp.getz();
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
    }

    bool is_equal (const point_t& p) const;

    bool is_valid() const;
};

class plane_t { //Ax + Bx + Cz + D = 0
    float A = 0.0f, B = 0.0f, C = 0.0f, D = 0.0f;

    public :

    plane_t(){}

    plane_t (float a, float b, float c, float d){ //creating plane with parametrs
        A = a;
        B = b;
        C = c;
        D = d;
    }

    plane_t(point_t const &p1, point_t const &p2, point_t const &p3){ //building plane on 3 points
        A = (p2.gety() - p1.gety()) * (p3.getz() - p1.getz()) - (p3.gety() - p1.gety()) * (p2.getz() - p1.getz());
        B = (p3.getx() - p1.getx()) * (p2.getz() - p1.getz()) - (p2.getx() - p1.getx()) * (p3.getz() - p1.getz());
        C = (p2.getx() - p1.getx()) * (p3.gety() - p1.gety()) - (p3.getx() - p1.getx()) * (p2.gety() - p1.gety());
        D = -1 * p1.getx() * ((p2.gety() - p1.gety()) * (p3.getz() - p1.getz()) - (p3.gety() - p1.gety()) * (p2.getz() - p1.getz())) -
            p1.gety() * ((p3.getx() - p1.getx()) * (p2.getz() - p1.getz()) - (p2.getx() - p1.getx()) * (p3.getz() - p1.getz())) -
            p1.getz() * ((p2.getx() - p1.getx()) * (p3.gety() - p1.gety()) - (p3.getx() - p1.getx()) * (p2.gety() - p1.gety()));
    }

    float getA() const{
        return A;
    }
    float getB() const{
        return B;
    }
    float getC() const{
        return C;
    }
    float getD() const{
        return D;
    }

    bool is_valid () const;//checking valid

    bool is_parallel (plane_t plane) const; //checking parallelism

    bool is_equal (plane_t plane) const; //checking equality

    void print() const;
};

class line_t { // (x - x0) / ax = (y - y0) / ay = (z - z0) / az
    float x0 = 0.0f, y0 = 0.0f, z0 = 0.0f;
    float ax = 1.0f, ay = 1.0f, az = 1.0f;

public:

    line_t(){}

    line_t(const point_t &p1, const point_t &p2){ // construct line on two points
        ax = p2.getx() - p1.getx();
        ay = p2.gety() - p1.gety();
        az = p2.getz() - p1.getz();
        x0 = p1.getx();
        y0 = p1.gety();
        z0 = p1.getz();
    }

    line_t(const plane_t &p1, const plane_t &p2){ // construct line on two planes
        if (!p1.is_valid() || !p2.is_valid() || p1.is_parallel(p2))
        {
            point_t p1, p2;
            line_t(p1, p2);
            return;
        }
        ax = p1.getB() * p2.getC() - p1.getC() * p2.getB();
        ay = -1 * (p1.getA() * p2.getC() - p1.getC() * p2.getA());
        az = p1.getA() * p2.getB() - p1.getB() * p2.getA();
        if (p1.getA() == 0){
            x0 = 0;
            if (p1.getB() == 0){
                z0 = -1 * p1.getD() / p1.getC();
                y0 = -1 * (p2.getD() + z0 * p2.getC()) / p2.getB();
                return;
            }
            if (p1.getC() == 0){
                y0 = -1 * p1.getD() / p1.getB();
                z0 = -1 * (p2.getD() + y0 * p2.getB()) / p2.getC();
                return;
            }
            z0 = (p2.getB()/p1.getB() * p1.getD() - p2.getD()) / (-1 * p2.getB() / p1.getB() * p1.getC() + p2.getC());
            y0 = (-1 * p1.getD() - p1.getC() * z0) / p1.getB();
            return;
        }
        if (p2.getA() != 0) {
            x0 = -1 * p2.getD() / p2.getA();
            y0 = 0;
            z0 = 0;
            return;
        }
        if (p2.getB() != 0){
            z0 = 0;
            y0 = -1 * p2.getD() / p2.getB();
            x0 = -1 * (p1.getD() - p1.getB() * y0) / p1.getA();
            return;
        }
        if (p2.getC() != 0){
            y0 = 0;
            z0 = -1 * p2.getD() / p2.getC();
            x0 = -1 * (p1.getD() - p1.getC() * z0) / p1.getA();
            return;
        }
    }

    float getx0() const{
        return x0;
    }
    float gety0() const{
        return y0;
    }
    float getz0() const{
        return z0;
    }
    float getax() const{
        return ax;
    }
    float getay() const{
        return ay;
    }
    float getaz () const{
        return az;
    }

    point_t intersection(line_t line) const;// finding of crossing point of two lines

    point_t projection_p (point_t p) const; //finding of projection of point projection on line

    void print () const; // printing line

    bool is_valid() const; //checking valid
};

class vector_t{
    point_t p1, p2;

public:

    vector_t(){}

    vector_t (const point_t& pt1, const point_t pt2){ // creating on two points
        p1.newp(pt1);
        p2.newp(pt2);
    }

    point_t getp1() const{
        return p1;
    }
    point_t getp2() const{
        return p2;
    }

    float compx() const{
        return p2.getx() - p1.getx();
    }
    float compy() const{
        return p2.gety() - p1.gety();
    }
    float compz() const{
        return p2.getz() - p1.getz();
    }

    float length() const{// finding length
        return sqrt((p2.getx()-p1.getx()) * (p2.getx() - p1.getx()) + (p2.gety() - p1.gety()) * (p2.gety() - p1.gety()) + (p2.getz() - p1.getz()) * (p2.getz() - p1.getz()));
    }

    bool is_codir (const vector_t vector) const; // check co-direction of parallel vectors

    bool is_crossing(const vector_t& vec) const; // check intersection of sections lying on one line

    bool is_valid() const; // checking valid

    bool is_equal (const vector_t& vec) const; // checking equality

    void print() const; //print
};

class triangle_t {
    point_t A, B, C;
    plane_t plane;
    line_t AB, AC, BC;
public:

    triangle_t(const point_t &p1, const point_t &p2, const point_t &p3) {// Creating on three points
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

    point_t getA() const{
        return A;
    }
    point_t getB() const{
        return B;
    }
    point_t getC() const{
        return C;
    }
    plane_t getplane() const {
        return plane;
    }
    line_t getAB() const{
        return AB;
    }
    line_t getBC() const{
        return BC;
    }
    line_t getAC() const{
        return AC;
    }


    vector_t vec_cross_l (line_t cross_l) const; //finding of vector of triangle and line crossing

    bool is_valid() const; //checking validity

    void print() const; //print
};

bool check_crossing_eq_plane(const triangle_t& t1, const triangle_t& t2);//checkin equality of two planes

bool check_crossing(const triangle_t &t1, const triangle_t &t2);// checking crossing of two planes
