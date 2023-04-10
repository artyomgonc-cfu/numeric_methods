#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

double f1(double y, double z) {
    return z;
}

double f2(double y, double z) {
    return -9.8 / 10 * sin(y);
}

double calc(double a, double b, double ya, double w, double h) {
    double cur_y = ya, cur_z = w;
    for (double x = a + h; x < b + 1e-7; x += h) {
        double k11 = h * f1(cur_y, cur_z);
        double k12 = h * f2(cur_y, cur_z);

        double k21 = h * f1(cur_y + k11, cur_z + k12);
        double k22 = h * f2(cur_y + k11, cur_z + k12);
        
        cur_y = 0.5 * (k11 + k21) + cur_y;
        cur_z = 0.5 * (k12 + k22) + cur_z;
    }
    return cur_y;
}

double shooter(double a, double b, double ya, double yb, double n, double eps) {
    double wm = 1.5, wp = 2;

    cout << "(w-)=" << calc(a, b, ya, wm, (b - a) / n) << " < y_b=" << yb << endl;
    cout << "(w+)=" << calc(a, b, ya, wp, (b - a) / n) << " > y_b=" << yb << endl;
    cout << endl;

    double c = (wm + wp) / 2, val;
    do {
        val = calc(a, b, ya, c, (b - a) / n);
        if (val > yb) wp = c;
        else wm = c;
        c = (wm + wp) / 2;

    } while (abs(yb - val) > eps);

    return c;
}

int main() {
    const double pi = acos(-1);
    cout << "Answer: w=" << shooter(0, 1, 0, pi / 2, 20, 1e-5) << endl;

    return 0;
}
