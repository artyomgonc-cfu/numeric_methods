#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

double ff(double y) {
    return 2.0 * y * y - y - 6;
}

double d(double y) {
    return 4.0 * y - 1;
}

double binary(double a, double b, double (*f)(double), double eps) {
    double y = a;
    int i = 1;
    double diff;
    do {
        cout << setprecision(8) << "y_" << i << "=" << y << "-(" << f(y) << "/" << d(y) << ")=";
        double new_y = y - f(y) / (d(y));
        cout << new_y << endl;
        diff = abs(new_y - y);
        cout << "A=" << diff << "\n\n";
        y = new_y;
        i++;
    } while (diff > eps);

    return (b + a) / 2;
}

int main() {
    cout << binary(-2, -0.5, *ff, 0.0005);

    return 0;
}
