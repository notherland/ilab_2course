#include "RecursiveDet.cpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{1, 44, 555, 64, 345, 34, 34, 6, 4};
    Matrix<int> m{3, 3, v.begin(), v.end()};
    if (RecursiveDet(m) == m.LUdet())
        std::cout << "Success";
    else
        std::cout << "Fail";

}
