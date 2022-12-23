#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

vector<double> sys_solve(const vector<vector<double>>& a, const vector<double>& b) {
    int n = a.size();
    vector<double> p(n);
    vector<double> q(n);

    p[1] = -a[0][1];
    q[1] = b[0];

    for (int i = 1; i < n-1; i++) {
        p[i + 1] = a[i][i+1] / (a[i][i] - a[i][i - 1] * p[i]);
        q[i + 1] = (b[i] + a[i][i-1] * q[i]) / (a[i][i] - a[i][i - 1] * p[i]);
    }

    vector<double> y(n);
    y[n - 1] = (-a[n - 1][n - 2] * q[n - 1] + b[n - 1]) / (1.0 + a[n - 1][n - 2] * p[n - 1]);
    for (int i = n - 2; i >= 0; i--)
        y[i] = p[i + 1] * y[i + 1] + q[i + 1];

    return y;
}

vector<vector<double>> create_matrix(int n, double a, double b, double c, double k1, double k2) {
    vector<vector<double>> m(n, vector<double>(n));
    m[0][0] = 1;
    m[0][1] = -k1;

    for (int i = 1; i < n - 1; i++) {
        m[i][i - 1] = a;
        m[i][i] = b;
        m[i][i + 1] = c;
    }

    m[n - 1][n - 2] = -k2;
    m[n - 1][n - 1] = 1;

    return m;
}

vector<double> equation(int n) {
    double a = 1, b = -4, c = 1, k1 = -0.25, k2 = -0.25, m1 = 2.5, m2 = 2.5, f = -12;

    auto ma = create_matrix(n, a, b, c, k1, k2);
    vector<double> mb(n);
    mb[0] = m1; mb[n - 1] = m2;
    for (int i = 1; i < n - 1; i++)
        mb[i] = f;

    return sys_solve(ma, mb);
}

int main() {

    vector<int> n{ 4, 5, 7, 10 };

    for (int i : n) {
        auto v = equation(i);
        for (double j : v)
            cout << j << ", ";
        cout << endl;
    }

    return 0;
}
