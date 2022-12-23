#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double f(double x) {
    return 1.0 / (1 + 25.0 * x * x);
}

vector<double> sys_solve(const vector<vector<double>>& a, const vector<double>& b) {
    int n = a.size();
    vector<double> p(n);
    vector<double> q(n);

    p[1] = -a[0][1];
    q[1] = b[0];

    for (int i = 1; i < n-1; i++) {
        p[i + 1] = -a[i][i+1] / (a[i][i] + a[i][i - 1] * p[i]);
        q[i + 1] = (b[i] - a[i][i-1] * q[i]) / (a[i][i] + a[i][i - 1] * p[i]);
    }

    vector<double> y(n);
    y[n - 1] = (b[n - 1] - a[n - 1][n - 2] * q[n - 1]) / (a[n - 1][n - 1] + a[n - 1][n - 2] * p[n - 1]);
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

vector<double> equation(double h, double d) {
    double a = 1.0/h, b = 4.0/h, c = 1.0/h, k1 = 1, k2 = 1, m1 = d, m2 = -d;

    int n = round(2.0 / h)+1;

    auto ma = create_matrix(n, a, b, c, k1, k2);
    vector<double> mb(n);
    mb[0] = m1; mb[n - 1] = m2;
    for (int i = 1; i < n - 1; i++) {
        double x = -1.0 + h * i;
        mb[i] = 3.0 * ((f(x) - f(x-h)) / h /h + (f(x+h) - f(x)) / h / h);
    }
    return sys_solve(ma, mb);
}

double xi(int i, double h) {
    return (-1.0 + h * i);
}

double spline(double xv, const vector<double>& s, double h, double i) {
    /*double ans = 1.0 / (6.0 * h) * (s[i - 1] * pow(xi(i, h) - xv, 3) + s[i] * pow(xv - xi(i - 1, h), 3));
    ans += (xv - xi(i - 1, h)) * (f(xi(i, h)) / h - h * s[i] / 6);
    ans += (xi(i, h) - xv) * (f(xi(i-1, h)) / h - h * s[i-1] / 6);*/
    double ans = f(xi(i - 1, h)) * pow(xv - xi(i, h), 2) * (2 * (xv - xi(i - 1, h)) + h) / pow(h, 3);
    ans += f(xi(i, h)) * pow(xv - xi(i-1, h), 2) * (2 * (xi(i, h) - xv) + h) / pow(h, 3);
    ans += s[i - 1] * pow(xv - xi(i, h), 2) * (xv - xi(i - 1, h)) / pow(h, 2);
    ans += s[i] * pow(xv - xi(i - 1, h), 2) * (xv - xi(i, h)) / pow(h, 2);
    return ans;
}

int main() {

    double h = 2.0 / 5;

    vector<pair<double, double>> intervals;
    intervals.push_back({ 0,0 });
    for (double x = -1; x < 1; x += h)
        intervals.push_back({ x, x + h });

    vector<double> des{ 0, 3, 5, 10, 25 };
    for (double d : des) {
        cout << d << ":\n";
        vector<double> s = equation(h, d);
        for (double x = -1; x <= 1; x += 2.0 / 20) {
            int interv = -1;
            for (int i = 1; i < intervals.size(); i++)
                if (intervals[i].first <= x && x <= intervals[i].second) {
                    interv = i;
                    break;
                }

            cout << spline(x, s, h, interv) << endl;
        }
        cout << "-----------------------------------------------------------\n";
    }

    return 0;
}
