#include "Triangles.h"

int main() {
    int N;
    std::ifstream fin ("/home/ksenia/Desktop/Proga/Triangle/test.txt");

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
