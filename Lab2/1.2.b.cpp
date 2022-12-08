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
    return 1.0 / (1.0 + 16.0 * x * x);
}

int main() {

    vector<int> nv{ 4, 10, 20 };
    for (int n : nv) {
        cout << "n=" << n << endl;

        vector<double> x;
        vector<double> y;
        for (int i = 0; i <= n; i++) {
            double xv = cos(acos(-1) * (2 * i + 1) / (2 * (n + 1)));
            x.push_back(xv);
            y.push_back(f(xv));
        }

        cout << "x:\n";
        for (double xv : x)
            cout << xv << endl;

        cout << "y:\n";
        for (double yv : y)
            cout << yv << endl;
    }
    return 0;
}
