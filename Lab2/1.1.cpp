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

int main() {
    vector<double> x{ -0.65, -0.531, -0.2, 0.223, 1 };
    vector<double> y{ 0.71, 0.322, 0.5, 1, 0.28 };

    cout << "Power: " << x.size() - 1 << endl;

    for (double xv = -1; xv <= 1; xv += 2.0 / 10)
        cout << f(xv, x, y) << endl;

    return 0;
}
