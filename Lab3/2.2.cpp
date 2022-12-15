#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double f(double x) {
    return 1.0 / (1.0 + 11.0 * x * x);
}

double df(double x) {
    return -22.0 * x / pow(1.0 + 11.0 * x * x, 2);
}

double spl(double val, double a, double b) {

    double k = (val - a) / (b - a);

    double ans = (1.0 - 3 * pow(k, 2) + 2 * pow(k, 3)) * f(a)
        + (3 * pow(k, 2) - 2 * pow(k, 3)) * f(b)
        + (b - a) * (k - 2 * pow(k, 2) + pow(k, 3)) * df(a)
        + (b - a) * (-pow(k, 2) + pow(k, 3)) * df(b);

    return ans;
}

int main() {

    vector<pair<double, double>> intervals;
    for (double x = -1; x < 1; x += 0.1)
        intervals.push_back({ x, x + 0.1 });

    for (double x = -1; x <= 1; x += 0.1 / 4) {
        pair<double, double> interv;
        for (auto i : intervals)
            if (i.first <= x && x <= i.second) {
                interv = i;
                break;
            }
        cout << spl(x, interv.first, interv.second) << endl;
    }
    
    return 0;
}
