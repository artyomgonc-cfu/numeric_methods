#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

template
<typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> ans(a.size());
    for (int i = 0; i < a.size(); i++)
        ans[i] = a[i] + b[i];
    return ans;
}

template
<typename T>
vector<T> operator*(double c, const vector<T>& b) {
    vector<T> ans = b;
    for (T& i : ans)
        i *= c;
    return ans;
}

template
<typename T>
T operator*(const vector<T>& a, const vector<T>& b) {
    T ans = 0;
    for (int i = 0; i < a.size(); i++)
        ans += a[i] * b[i];
    return ans;
}

template
<typename T>
vector<T> operator*(const vector<vector<T>>& a, const vector<T>& b) {
    vector<T> ans(a.size());
    for (int i = 0; i < ans.size(); i++)
        ans[i] = a[i] * b;
    return ans;
}

void print(const vector<vector<double>>& v, int dash_pos) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[0].size(); j++) {
            if (j == dash_pos)
                cout << "| ";
            cout << setw(7) << v[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

vector<double> gauss(const vector<vector<double>>& a, const vector<double>& b) {
    vector<vector<double>> g(a.size(), vector<double>(a.size() + 1));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a[0].size(); j++)
            g[i][j] = a[i][j];

    for (int i = 0; i < a.size(); i++)
        g[i][a.size()] = b[i];

    cout << setprecision(3);
    //print(g, a.size());

    for (int it = 0; it < a.size() - 1; it++) {
        double maxv = -1e10;
        int maxi;
        for (int i = it; i < a.size(); i++)
            if (g[i][it] > maxv) {
                maxv = g[i][it];
                maxi = i;
            }
        swap(g[it], g[maxi]);
        for (int i = it + 1; i < a.size(); i++)
            g[i] = (-g[it][it] / g[i][it]) * g[i] + g[it];

        //print(g, a.size());
    }

    vector<double> x(a.size());
    for (int i = a.size() - 1; i >= 0; i--) {
        double bb = g[i][a.size()];
        for (int j = a.size() - 1; j > i; j--)
            bb -= g[i][j] * x[j];
        x[i] = bb / g[i][i];
    }

    return x;
}

double norm(const vector<double>& v) {
    double ans = 0;
    for (double i : v)
        ans += i*i;
    return sqrt(ans);
}

double norm(const vector<vector<double>>& v) {
    double ans = 0;
    for (auto i : v)
        for (auto j : i)
            ans += j * j;
    return sqrt(ans);
}

vector<double> min_nev(const vector<vector<double>>& a, const vector<double>& b, double eps, int& it) {
    vector<double> xk(a.size());
    vector<double> rk(a.size());
    double tk1;
    vector<double> old_x;

    it = 0;
    while(true) {
        it++;
        rk = a * xk + (-1.0 * b);

        if (norm(rk) < eps) break;

        tk1 = (rk * (a * rk)) / ((a*rk) * (a * rk));

        old_x = xk;
        xk = old_x + (-tk1 * rk);
    }

    return xk;
}

vector<double> fast_desc(const vector<vector<double>>& a, const vector<double>& b, double eps, int& it) {
    vector<double> xk(a.size());
    vector<double> rk(a.size());
    double tk1;
    vector<double> old_x;

    it = 0;
    while (true) {
        it++;
        rk = a * xk + (-1.0 * b);

        if (norm(rk) < eps) break;

        tk1 = (rk * rk) / (rk * (a * rk));

        old_x = xk;
        xk = old_x + (-tk1 * rk);
    }

    return xk;
}

int main() {
    vector<vector<double>> a{
        {21, 5, 8},
        {5, 7, 3},
        {8, 3, 12}
    };

    vector<double> b{ 17, 4, 1};
    vector<double> x = gauss(a, b);
    cout << "Answer Gauss: (";
    cout << fixed << setprecision(5);
    for (double i : x)
        cout << i << ' ';
    cout << "\b)\n\n";

    int it;
    vector<double> eps{ 1e-2, 1e-4, 1e-8, 1e-16 };
    for (double e : eps) {
        x = min_nev(a, b, e, it);
        cout << fixed << setprecision(5);
        cout << "Answer min_neuv:  (";
        for (double i : x)
            cout << i << ' ';
        cout << "\b); iter: " << it << "; eps: " << scientific << setprecision(0) << e << ";\n";

        x = fast_desc(a, b, e, it);
        cout << fixed << setprecision(5);
        cout << "Answer fast_desc: (";
        for (double i : x)
            cout << i << ' ';
        cout << "\b); iter: " << it << "; eps: " << scientific << setprecision(0) << e << ";\n";

        cout << endl;
    }

    return 0;
}
