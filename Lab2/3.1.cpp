#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double n(double val, const vector<double>& x, const vector<vector<double>>& table) {
    double ans = 0;
    for (int i = 0; i < x.size(); i++) {
        double factor = 1;
        for (int j = 0; j < i; j++)
            factor *= val - x[j];
        ans += factor * table[0][i];
    }
    return ans;
}

vector<vector<double>> get_table(const vector<double>& x, const vector<double>& y) {
    vector<vector<double>> table(y.size(), vector<double>(y.size()));
    for (int i = 0; i < y.size(); i++)
        table[i][0] = y[i];

    for (int j = 1; j < y.size(); j++)
        for (int i = 0; i < y.size() - j; i++)
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);

    return table;
} 

int main() {
    vector<double> x{ -0.65, -0.531, -0.2, 0.223, 1 };
    vector<double> y{ 0.71, 0.322, 0.5, 1, 0.28 };
    vector<vector<double>> table = get_table(x, y);

    for (double xv = -1; xv <= 1; xv += 2.0 / 10)
        cout << n(xv, x, table) << endl;

    return 0;
}
