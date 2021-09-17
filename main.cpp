#include "test.h"

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    if (!test_overlap()) {
        std::cout << "Error in overlap function";
        exit(0);
    }
    if (!test_normalize()) {
        std::cout << "Error in normalize function";
        exit(0);
    }

    std::cout << "OK\n";
    int n1, n2;
    std::cin >> n1;
    std::vector<segment> segs1(n1), segs1_modified;
    for (int i = 0; i < n1; i++) {
        std::cin >> segs1[i];
    }
    std::cin >> n2;
    std::vector<segment> segs2(n2);
    for (int i = 0; i < n2; i++)
        std::cin >> segs2[i];
    if (are_equal(segs1, segs2)) {
        std::cout << "Sets are equal";
    } else {
        std::cout << "Sets are different";
    }
}