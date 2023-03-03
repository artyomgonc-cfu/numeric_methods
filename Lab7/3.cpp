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

void print(const vector<vector<double>>& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[0].size(); j++) {
            cout << setw(7) << v[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<double>> gauss(const vector<vector<double>>& a, const vector<vector<double>>& b) {
    vector<vector<double>> g(a.size(), vector<double>(a.size() + b.size()));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a[0].size(); j++)
            g[i][j] = a[i][j];

    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            g[i][a.size()+j] = b[j][i];

    cout << setprecision(5);

    for (int it = 0; it < a.size()-1; it++) {
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
    }

    vector<vector<double>> x(b.size(), vector<double>(a.size()));
    for (int n = 0; n < b.size(); n++)
        for (int i = a.size() - 1; i >= 0; i--) {
            double bb = g[i][a.size()+n];
            for (int j = a.size() - 1; j > i; j--)
                bb -= g[i][j] * x[n][j];
            x[n][i] = bb / g[i][i];
        }

    return x;
}

int main() {
    vector<vector<double>> a{
        {2, 5, 7},
        {6, 3, 4},
        {5, -2, -3}
    };
    vector<vector<double>> b;
    for (int i = 0; i < a.size(); i++) {
        vector<double> tmp(a.size());
        tmp[i] = 1;
        b.push_back(tmp);
    }

    vector<vector<double>> x = gauss(a, b);

    cout << "A:\n";
    print(a);

    vector<vector<double>> rev(a.size(), vector<double>(a.size()));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++)
            rev[i][j] = x[j][i];

    cout << "A^-1\n";
    print(rev);

    cout << "A * A^-1 = E\n";
    cout << fixed << setprecision(2);
    print(a * rev);

    return 0;
}
