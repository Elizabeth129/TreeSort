#include <iostream>
#include <chrono>
#include "Sorter.h"

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    Sorter sorter("input.txt", "output.txt", true, true);
    sorter.Sort();
    auto endTime = std::chrono::high_resolution_clock::now();
    printf("Time elapsed %ld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
    return 0;
}
