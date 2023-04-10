#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

double p(double x) { return sin(x); }
double q(double x) { return cos(x); }
double r(double x) { return 1; }
double f(double x) { return pow(sin(x),2); }

vector<double> sys_solve(const vector<vector<double>>& a, const vector<double>& b) {
    int n = a.size();
    vector<double> p(n);
    vector<double> q(n);

    p[1] = -a[0][1];
    q[1] = b[0];

    for (int i = 1; i < n - 1; i++) {
        p[i + 1] = a[i][i + 1] / (a[i][i] - a[i][i - 1] * p[i]);
        q[i + 1] = (b[i] + a[i][i - 1] * q[i]) / (a[i][i] - a[i][i - 1] * p[i]);
    }

    vector<double> y(n);
    y[n - 1] = (-a[n - 1][n - 2] * q[n - 1] + b[n - 1]) / (1.0 + a[n - 1][n - 2] * p[n - 1]);
    for (int i = n - 2; i >= 0; i--)
        y[i] = p[i + 1] * y[i + 1] + q[i + 1];

    return y;
}


vector<double> calc(double a, double b, double n, double ya, double yb) {
    vector<double> mb(n+1);
    mb[0] = ya; mb[mb.size() - 1] = yb;
    vector<vector<double>> ma(n+1, vector<double>(n+1));
    ma[0][0] = ma[ma.size() - 1][ma.size() - 1] = 1;

    double h = (b - a) / n;

    int i = 1;
    for (double x = a + h; x < b - h + 1e-7; x += h, i++) {
        ma[i][i - 1] = 1.0 / h / h - p(x) / 2 / h;
        ma[i][i] = 2.0 / h / h + q(x);
        ma[i][i+1] = 1.0 / h / h + p(x) / 2 / h;
        mb[i] = f(x);
    }

    return sys_solve(ma, mb);
}

int main() {
    const double pi = acos(-1);
    vector<double> ns{ 10, 20 };

    for (double n : ns) {

        cout << "n=" << n << ":\n";
        vector<double> ys = calc(0, 10, n, 0, 2.1);
        for (double y : ys)
            cout << y << endl;
        cout << endl;
    }
    return 0;
}
