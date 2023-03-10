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
vector<vector<T>> operator*(const vector<vector<T>>& a, const vector<vector<T>>& b) {
    vector<vector<T>> ans(a.size(), vector<T>(b[0].size()));
    for (int i = 0; i < ans.size(); i++)
        for (int j = 0; j < ans[0].size(); j++) {
            vector<T> col;
            for (int k = 0; k < b.size(); k++)
                col.push_back(b[k][j]);
            ans[i][j] = a[i] * col;
        }
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

double norm(const vector<double>& v) {
    double ans = 0;
    for (double i : v)
        ans += i * i;
    return sqrt(ans/v.size());
}

double norm(const vector<vector<double>>& v) {
    double ans = 0;
    for (auto i : v)
        for (auto j : i)
            ans += j * j;
    return sqrt(ans);
}

double find_max_l(const vector<vector<double>>& a, double eps, vector<double>& v) {
    vector<double> x(a.size(), 1), old_x;
    double l_old, l = 1e10;
    do {
        old_x = x;
        x = a * old_x;

        l_old = l;
        l = (x * old_x) / (old_x * old_x);

        double n = norm(x);
        for (double& i : x)
            i /= n;

    } while (abs(l_old - l) >= eps);
    
    v = x;
    return l;
}

int main() {
    vector<vector<double>> a{
        {5, 4},
        {1, 2},
    };

    vector<double> x;
    cout << "max L: " << find_max_l(a, 1e-4, x) << " | (";
    for (double i : x)
        cout << i << ' ';
    cout << "\b)\n";

    double n = norm(a);
    for (int i = 0; i < a.size(); i++)
        a[i][i] -= n;

    cout << "min L: " << find_max_l(a, 1e-4, x) + n << " | (";
    for (double i : x)
        cout << i << ' ';
    cout << "\b)\n";
}
