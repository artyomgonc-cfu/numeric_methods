#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
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

double find_max(const vector<vector<double>>& a, int& max_i, int& max_j) {
    double max_val = -1;
    for (int i = 0; i < a.size(); i++)
        for (int j = i+1; j < a.size(); j++)
            if (abs(a[i][j]) > max_val) {
                max_val = a[i][j];
                max_i = i;
                max_j = j;
            }
    return max_val;
}

vector<vector<double>> transpone(const vector<vector<double>>& a) {
    vector<vector<double>> ans(a.size(), vector<double>(a.size()));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++)
            ans[j][i] = a[i][j];
    return ans;
}

vector<vector<double>> rot_m(int size, int i, int j, double q) {
    vector<vector<double>> ans(size, vector<double>(size));
    for (int i = 0; i < size; i++)
        ans[i][i] = 1;
    ans[i][i] = cos(q);
    ans[j][j] = cos(q);
    ans[i][j] = sin(q);
    ans[j][i] = -sin(q);
    return ans;
}

pair<vector<double>, vector<vector<double>>> get_ls(const vector<vector<double>>& a, double eps) {
    bool first = true;
    auto w = a;

    auto ak = a;
    while (true) {
        int max_i, max_j;
        double max_el = find_max(ak, max_i, max_j);

        cout << "a[" << max_i << "][" << max_j << "] = " << max_el << endl;

        if (max_el < eps)
            break;

        double q = atan(2.0 * max_el / (ak[max_i][max_i] - ak[max_j][max_j])) / 2;
        auto r_m = rot_m(a.size(), max_i, max_j, q);

        if (first) {
            first = false;
            w = r_m;
        }
        else
            w = r_m * w;

        ak = r_m * (ak * transpone(r_m));
    }

    vector<double> ls(a.size());
    for (int i = 0; i < a.size(); i++)
        ls[i] = ak[i][i];

    return { ls, w };
}

int main() {
    vector<vector<double>> a{
        {10, 21, 17},
        {21, 15, 11},
        {17, 11, 12}
    };

    auto ls = get_ls(a, 1e-5);

    cout << endl;
    for (int i = 0; i < a.size(); i++) {
        cout << ls.first[i] << ": (";
        for (int j = 0; j < a.size(); j++)
            cout << ls.second[i][j] << " ";
        cout << "\b)\n";
    }

    return 0;
}
