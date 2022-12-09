#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double l(double val, const vector<double>& x, const vector<double>& y) {
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

double f(double x) {
    return x * x * x;
}

int main() {

    vector<int> nv{ 10, 20 };
    for (int n : nv) {
        cout << "n=" << n << endl;

        vector<double> x;
        vector<double> y;
        for (double xv = -1; xv <= 1; xv += 2.0 / n) {
            x.push_back(xv);
            y.push_back(f(xv));
        }

        cout << "x:\n";
        for (double xv : x)
            cout << xv << endl;

        cout << "y:\n";
        for (double yv : y)
            cout << yv << endl;

        cout << "y_calc:\n";
        double max_fault = -1e9;
        for (double xv = -1; xv <= 1; xv += 0.25 / 2) {
            cout << l(xv, x, y) << endl;
            if (abs(l(xv, x, y) - f(xv)) > max_fault)
                max_fault = abs(l(xv, x, y) - f(xv));
        }
        cout << "n=" << n << ": max abs fault = " << max_fault << endl;
    }
    return 0;
}
