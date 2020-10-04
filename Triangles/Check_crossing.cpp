#include "Triangles.h"

bool check_crossing_eq_plane(const triangle_t& t1, const triangle_t& t2) {
    vector_t vec_cross, vec_AB{t1.getA(), t1.getB()}, vec_AC{t1.getA(), t1.getC()}, vec_BC{t1.getB(), t1.getC()};

    vec_AB.print();
    std::cout << " - AB" << std::endl;
    vec_AC.print();
    std::cout << " - AC" << std::endl;
    vec_BC.print();
    std::cout << " - BC" << std::endl;

    if ((vec_cross = t2.vec_cross_l(t1.getAB())).is_valid())
    {
        if (vec_cross.is_crossing(vec_AB))
            return true;
        return false;
    }
    if ((vec_cross = t2.vec_cross_l(t1.getAC())).is_valid())
    {
        if (vec_cross.is_crossing(vec_AC))
            return true;
        return false;
    }
    if ((vec_cross = t2.vec_cross_l(t1.getBC())).is_valid())
    {
        if (vec_cross.is_crossing(vec_BC))
            return true;
        return false;
    }

    point_t proj1_AB  = t1.getAB().projection_p(t1.getC());
    point_t proj1_AC  = t1.getAC().projection_p(t1.getB());
    point_t proj1_BC  = t1.getBC().projection_p(t1.getA());
    point_t proj2_AB  = t1.getAB().projection_p(t2.getA());
    point_t proj2_AC  = t1.getAC().projection_p(t2.getA());
    point_t proj2_BC  = t1.getBC().projection_p(t2.getA());

    vector_t n1_AB{proj1_AB, t1.getC()}, n1_AC{proj1_AC, t1.getB()}, n1_BC{proj1_BC, t1.getA()}, n2_AB{proj2_AB, t2.getA()}, n2_AC{proj2_AC, t2.getA()}, n2_BC{proj2_BC, t2.getA()};
    if (n1_AB.is_codir(n2_AB) && n1_AC.is_codir(n2_AC) && n1_BC.is_codir(n2_BC))
        return true;
    std::cout << "nothing" << std::endl;
    return false;
}

bool check_crossing(const triangle_t &t1, const triangle_t &t2) {
    if (t1.getplane().is_parallel(t2.getplane()) && !(t1.getplane().is_equal(t2.getplane()))) {
        t1.getplane().print();
        std::cout << std::endl;
        t2.getplane().print();
        std::cout << std::endl;
        return false;
    }

    if (t1.getplane().is_equal(t2.getplane())) {
        t1.getplane().print();
        std::cout << std::endl;
        t2.getplane().print();
        std::cout << std::endl;
        std::cout << "same plane" << std::endl;
        return check_crossing_eq_plane(t1, t2);
    }

    line_t cross_l{t1.getplane(), t2.getplane()};

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