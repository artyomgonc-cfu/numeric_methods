#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

double ff(double y, double p) {
    return 2.0 * y * y - y - 6;
}

double binary(double a, double b, double (*f)(double, double), double p, double eps) {
    double c;
    int i = 0;
    cout << setw(3) << "i" << '|' << setw(7) << "a" << '|' << setw(7) << "b" << '|' << setw(7) << "y" << '|'
        << setw(7) << "f(a)" << '|' << setw(7) << "f(b)" << '|' << setw(7) << "f(y)" << '|' << setw(7) << "eps" << endl;
    do {
        c = (b + a) / 2;

        cout << fixed << setprecision(4) << setw(3) << i << '|' << setw(7) << a << '|' << setw(7) << b << '|' << setw(7) << c << '|'
            << setw(7) << f(a, p) << '|' << setw(7) << f(b, p) << '|' << setw(7) << f(c, p) << '|' << setw(7) << abs(a - b);

        if (abs(f(c, p)) < 1e-9) return c;

        if (f(c, p) * f(a, p) < 0)
            b = c;
        else
            a = c;
        i++;

        cout << endl;
    } while (abs(b-a) > eps);
    cout << i << endl;
    return (b + a) / 2;
}

int main() {
    cout << binary(-2, -0.5, *ff, 1, 0.0005);

    return 0;
}
