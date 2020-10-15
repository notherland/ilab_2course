#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "RecursiveDet.cpp"
#include <iomanip>

const float TOLERANCE = 0.0001;

BOOST_AUTO_TEST_CASE(Matrix_fuctions)
{
    //Testing constructors

    std::vector<int> v0 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<int> v1 = {3, 3, 3, 3, 3, 3};
    Matrix<int> m1{2, 3, 3}; // 2x3 matrix of all zeros
    Matrix<int> m2{2, 3, v1.begin(), v1.end()};
    Matrix<int> m = Matrix<int>::eye(3, 3);
    Matrix<int> m0 {3, 3, v0.begin(), v0.end()};
    BOOST_TEST(m0.equal(m));
    BOOST_TEST(m1.equal(m2));
    std::vector<int> vt = {1, 0, 0, 2, 3, 0, 4, 5, 6};
    std::vector<int> vtrig = {1, 2, 3, 4, 5, 6};
    Matrix<int> mt = {3, 3, vt.begin(), vt.end()};
    Matrix<int> mtrig = Matrix<int>::triangle(3, vtrig.begin(), vtrig.end());
    BOOST_TEST (mt.equal(mtrig));

    //Testing basic functions
    BOOST_TEST(m2[1][2] == 3);
    m2[1][2] = 7;
    BOOST_TEST(m2[1][2] == 7);
    m2 = m1;
    BOOST_TEST(m1.equal(m2));

    //Testing methods
    std::vector<int> v3 = {1, 4, 2, 5, 3, 6};
    Matrix<int> m3{3, 2, v3.begin(), v3.end()};
    std::vector<int> v4 = {1, 2, 3, 4, 5, 6};
    Matrix<int> m4{2, 3, v4.begin(), v4.end()};
    m3.transpose();
    BOOST_TEST(m3.equal(m4));
    BOOST_TEST(m0.trace() == 3);
    BOOST_TEST(m1.trace() == 0);

    //Testing operators
    std::vector<int> v5 = {-1, -2, -3, -4, -5, -6};
    std::vector<int> v8 = {2, 4, 6, 8, 10, 12};
    std::vector<int> v7 = {14, 32, 32, 77};
    Matrix<int> m5{2, 3, v5.begin(), v5.end()};
    Matrix<int> m6{2, 3};
    Matrix<int> m7{2, 2, v7.begin(), v7.end()};
    Matrix<int> m8{2, 3, v8.begin(), v8.end()};
    BOOST_TEST(m4.equal(-m5));
    m3 -= m4;
    BOOST_TEST(m3.equal(m6));
    m3 += m4;
    BOOST_TEST (m3.equal(m4));
    m3 *= 2;
    BOOST_TEST(m3.equal(m8));
    m4.transpose();
    m5 = -m5;
    m3 = m5;
    m5.prod(m4);
    m6 = m5;
    BOOST_TEST(m6.equal(m7));
    float det = m6.LUdet();
    BOOST_TEST (abs(det - 54) < TOLERANCE);
}

BOOST_AUTO_TEST_CASE(Matrix_determinant)
{
    for (int i = 1; i < 10; i++)
    {
        Matrix<int> m = Matrix<int>::RandomMatrix(i, i, 30); //Checking on random matrix
        //m.dump();
        float det1 = RecursiveDet(m);
        float det2 = m.LUdet();
        //std::cout << det1 << " " << det2<< std::endl;
        BOOST_TEST (abs ((det1 - det2)/det1) < TOLERANCE); //Проверяем относительную ошибку, так как на больших числах погрешность накапливается
    }
}

