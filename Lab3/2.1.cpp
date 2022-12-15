#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double f(double x) {
    return 1.0 / (1.0 + 11.0 * x);
}

double spl(double val, pair<double, double> der) {
    double a = -1, b = 1;
    double k = (val - a) / (b - a);

    double ans = (1.0 - 3 * pow(k, 2) + 2 * pow(k, 3)) * f(a)
        + (3 * pow(k, 2) - 2 * pow(k, 3)) * f(b)
        + (b - a) * (k - 2 * pow(k, 2) + pow(k, 3)) * der.first
        + (b - a) * (-pow(k, 2) + pow(k, 3)) * der.second;

    return ans;
}

int main() {

    vector<pair<double, double>> ders{
        { 2, -2},
        { 3, 0},
        {-1, -4 }
    };

    for (int i = 0; i < ders.size(); i++) {
        cout << "f" << i << endl;
        for (double x = -1; x <= 1; x += 2.0 / 20)
            cout << spl(x, ders[i]) << endl;
        cout << "------------------------------------------\n";
    }
    
    return 0;
}
