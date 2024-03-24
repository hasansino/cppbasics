#include <cmath>
#include <iostream>

#include "math.hpp"
#include "sqrt_table.hpp"

using namespace std;

namespace libmath {
    double sqrt(const double& a) {
        if (a < 0) {
            return 0;
        }
        if (a <= sqrtTableLen) {
            cout << "libmath::sqrt using precomputed table" << endl;
            return sqrtTable[static_cast<int>(a)];
        }
#if defined(HAVE_LDEXP) && defined(HAVE_FREXP)
        cout << "libmath::sqrt using ldexp/frexp capabilities" << endl;
        double answer = a;
        if (answer <= 0)
            return 0;
        int exp = 0;
        answer = frexp(answer, &exp);
        if (exp & 1) {
            exp--;
            answer *= 2;
        }
        double y = (1 + answer) / 2;
        double z = 0;
        while (y != z) {
            z = y;
            y = (y + answer / y) / 2;
        }
        return ldexp(y, exp / 2);
#else
        cout << "libmath::sqrt ldexp/frexp is not available" << endl;
        return a;
#endif
    }


}// namespace libmath