#include <fstream>
#include <string>
#include <iostream>

int main() {
    std::ifstream ifs("input.txt", std::ifstream::in);
    std::ifstream ofs("output.txt", std::ofstream::in);

    intmax_t cntIn = 0;
    intmax_t cntOut = 0;
    int value;
    while (ifs >> value) {
        cntIn++;
    }

    int prevValue;
    bool first = true;
    while (ofs >> value) {
        cntOut++;
        if (!first) {
            if (value < prevValue) {
                std::cout << "ERROR: WRONG ORDER: " << prevValue << " " << value << "\n";
                ifs.close();
                ofs.close();
                return 0;
            }
        }
        first = false;
        prevValue = value;
    }

    if (cntIn == cntOut) {
      std::cout << "VALID SORTING\n";
    } else {
      std::cout << "ERROR: SIZES DON'T MATCH:\n";
      std::cout << cntIn << " " << cntOut << "\n";
    }
    ifs.close();
    ofs.close();
}
