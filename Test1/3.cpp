#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double f(double val, const vector<double>& x, const vector<double>& y) {
    double ans = 0;
    for (int i = 0; i < y.size(); i++) {
        double factor = 1;
        for (int j = 0; j < x.size(); j++)
            if (j != i) {
                factor *= (val - x[j]) / (x[i] - x[j]);
            }
        ans += factor * y[i];
    }
    return ans;
}

double fault(const vector<double>& x, double xv, double m) {
    double ans = m;
    for (double i : x)
        ans *= (xv-i);
    for (int i = 1; i <= x.size(); i++)
        ans /= i;
    return ans;
}

int main() {
    vector<double> x1{ -2, 8 };
    vector<double> y1{ -22, 408 };

    vector<double> x21{ -2, 1, 8 };
    vector<double> y21{ -22, 2, 408 };

    vector<double> x22{ -2, 4, 8 };
    vector<double> y22{ -22, 44, 408 };

    cout << "1:\n";
    for (double xv = -2; xv <= 8; xv += 0.5)
        cout << f(xv, x1, y1) << endl;
    cout << "----------------------------\n";


    cout << "2.1:\n";
    for (double xv = -2; xv <= 8; xv += 0.5)
        cout << f(xv, x21, y21) << endl;
    cout << "----------------------------\n";

    cout << "2.2:\n";
    for (double xv = -2; xv <= 8; xv += 0.5)
        cout << f(xv, x22, y22) << endl;
    cout << "----------------------------\n";

    double x_star = 7;
    cout << f(x_star, x1, y1) << endl;
    cout << f(x_star, x21, y21) << endl;
    cout << f(x_star, x22, y22) << endl;

    cout << "----------------------------\n";
    cout << "Faults:\n";
    cout << "1: " << abs(fault(x1, x_star, 44)) << endl;
    cout << "2.1: " << abs(fault(x21, x_star, 6)) << endl;
    cout << "2.2: " << abs(fault(x22, x_star, 6)) << endl;

    return 0;
}
