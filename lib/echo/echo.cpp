#include "echo.hpp"

#include <iostream>

using namespace std;

namespace libecho {
    void printStrArr(const string arg[], int len) {
        for (int i = 0; i < len; i++) {
            cout << arg[i] << endl;
        }
    }
}// namespace libecho