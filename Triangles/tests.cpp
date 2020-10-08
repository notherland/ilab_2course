#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "Triangles.h"

BOOST_AUTO_TEST_CASE(Triangles_line_t_proj1)
{
    point_t pl1{4, 3, 1}, pl2{6, 2, 1}, p1{4, 10, 7}, p2{1, 4.5, 1};
    line_t l{pl1, pl2}; //(x-4)/2 = (y-3)/-1 = (z-1)/0;
    point_t p1_proj = l.projection_p(p1), p2_proj = l.projection_p(p2);
    point_t test_p1 {1.2, 4.4, 1}, test_p2{1, 4.5, 1};
    BOOST_TEST (p1_proj.is_equal(test_p1));
    BOOST_TEST (p2_proj.is_equal(test_p2));
}

BOOST_AUTO_TEST_CASE(Triangles_line_t_proj2)
{
    point_t pl1{1, 2, 6}, pl2{4, 0, 6}, p1{1, 44, 9}, p2{7, -2, 6};
    line_t l{pl1, pl2}; //(x-1)/3 = (y-2)/-2 = (z-6)/0
    point_t p1_proj = l.projection_p(p1), p2_proj = l.projection_p(p2);
    point_t test_p1 {-18.3846, 14.9231, 6}, test_p2{7, -2, 6};
    BOOST_TEST (p1_proj.is_equal(test_p1));
    BOOST_TEST (p2_proj.is_equal(test_p2));
}

BOOST_AUTO_TEST_CASE(Triangles_triangle_t)
{
    point_t A{4, 0, 2}, B{4, 4, 2}, C{0, 0, 0}, p1{0, 2, 0}, p2{4, 2, 2}, vp1{4, 2, 2}, vp2{2, 2, 1};
    triangle_t t{A, B, C};
    line_t l{p1, p2};
    vector_t vec_cross = t.vec_cross_l(l), test_vec {vp1, vp2};
    BOOST_TEST (vec_cross.is_equal(test_vec));
}

BOOST_AUTO_TEST_CASE(Triangles_Same_plane_crossing)
{
    point_t A1{2, 2, 0}, B1{4, 2, 0}, C1{3, 5, 0}, A2{3, 3, 0}, B2{4, 5, 0}, C2{4, 6, 0};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane {0, 0, 1, 0};
    BOOST_TEST (t1.getplane().is_equal(test_plane));
    BOOST_TEST (t2.getplane().is_equal(test_plane));
    BOOST_TEST(check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Same_plane_not_crossing)
{
    point_t A1{0, 0, 0}, B1{4, 0, 4}, C1{2, 4, 2}, A2{1, 5, 1}, B2{6, 6, 6}, C2{3, 8, 3};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane {-1, 0, 1, 0};
    BOOST_TEST(t1.getplane().is_parallel(test_plane));
    BOOST_TEST (t1.getplane().is_equal(test_plane));
    BOOST_TEST (t2.getplane().is_equal(test_plane));
    BOOST_CHECK(!check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Same_plane_crossing_inside)
{
    point_t A1{2, 4, 14}, B1{4, 6, 4}, C1{1, 4, 2}, A2{3, 5, 9}, B2{3.5, 5.5, 6.5}, C2{3, 5.2, 5.6};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane {-12, 17, 1, -58};
    BOOST_TEST (t1.getplane().is_equal(test_plane));
    BOOST_TEST (t2.getplane().is_equal(test_plane));
    BOOST_CHECK(check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Same_plane_crossing_on_side)
{
    point_t A1{10.5, 2, 0}, B1{4, 2, 10}, C1{3, 5, -6}, A2{10.5, 2, 0}, B2{4, 2, 10}, C2{-1.4, 0, 30};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane {20, 76, 13, -362};
    BOOST_TEST (t1.getplane().is_equal(test_plane));
    BOOST_TEST (t2.getplane().is_equal(test_plane));
    BOOST_TEST(check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Parallel_planes_not_crossing)
{
    point_t A1{1, 3, -7}, B1{0, 0, -2}, C1{5, 7, -15}, A2{3.5, 0, 0}, B2{1, 2, -1.75}, C2{4, 6, -9.25};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane {1, 3, 2, 10};
    BOOST_TEST (t1.getplane().is_parallel(test_plane));
    BOOST_TEST (t2.getplane().is_parallel(test_plane));
    BOOST_TEST(!check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Different_planes_crossing)
{
    point_t A1{0, 0, 0}, B1{4, 0, 0}, C1{4, 6, 0}, A2{0, 0, 4}, B2{4, 0, 4}, C2{3, 2, -1};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane1 {0, 0, 1, 0}, test_plane2 {0, 5, 2, -8};
    BOOST_TEST (t1.getplane().is_equal(test_plane1));
    BOOST_TEST (t2.getplane().is_equal(test_plane2));
    BOOST_TEST(check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Different_planes_not_crossing)
{
    point_t A1{10, 22, 8}, B1{4, 10, 16}, C1{11, 6, 2}, A2{4, 0, 3}, B2{9, 6, 4}, C2{-3, 7, -8};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane1 {50, -7, 27, -562}, test_plane2 {-73, 48, 77, 61};
    BOOST_TEST (t1.getplane().is_equal(test_plane1));
    BOOST_TEST (t2.getplane().is_equal(test_plane2));
    BOOST_TEST(!check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Different_planes_crossing_on_side)
{
    point_t A1{1, 2, 6}, B1{4, 0, 0}, C1{4, 6, 0}, A2{1, 2, 6}, B2{4, 0, 0}, C2{10, 9, -1};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    BOOST_TEST(check_crossing (t1, t2));
}

BOOST_AUTO_TEST_CASE(Triangles_Different_planes_crossing_on_point)
{
    point_t A1{0, 0, 0}, B1{4, 0, 4}, C1{4, 6, 0}, A2{0, 0, 0}, B2{4, 0, 4}, C2{3, 2, -1};
    triangle_t t1{A1, B1, C1}, t2{A2, B2, C2};
    plane_t test_plane1 {0, 0, 1, 0}, test_plane2 {0, 5, 2, -8};
    BOOST_TEST(check_crossing (t1, t2));
}