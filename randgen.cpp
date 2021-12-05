#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

int random_int() {
    return rand() ^ (rand() << 16);
}

int main() {
    int64_t n, m;
    std::cout << "Enter number of integers to be generated:\n";
    std::cin >> n;
    std::ofstream fs("input.txt", std::ifstream::out);
    for (int i = 0; i < n; i++) {
        if (i % 10000 == 0) std::cout << i << "\n";
        fs << random_int() << "\n";
    }
    fs.close();
}
