#include "Triangles.h"

int main() {
    int N;
    /*std::ifstream fin ("/home/ksenia/Desktop/Proga/Triangles/test.txt");

    if (!fin){
        std::cout << "Failed to open file" << std::endl;
        return 1;
    }*/

    std::cin >> N;
    std::vector<triangle_t> list;
    point_t p1, p2, p3;

    for (int i = 0; i < N; i++) {
        std::cin >> p1 >> p2 >> p3;
        triangle_t triangle(p1, p2, p3);
        for (int k = 0; k < list.size(); k++) {
            if (check_crossing(list[k], triangle))
            {
                std::cout << k << " " << i << std::endl;
            }
        }
        list.push_back(triangle);
    }
    return 0;
};
