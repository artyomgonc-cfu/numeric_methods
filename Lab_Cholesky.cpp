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

void print(const vector<vector<double>>& v, int dash_pos) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[0].size(); j++) {
            if (j == dash_pos)
                cout << "| ";
            cout << setw(7) << v[i][j] << ' ';
        }
        cout << endl;
    }
}

vector<double> gauss(const vector<vector<double>>& a, const vector<double>& b) {
    vector<vector<double>> g(a.size(), vector<double>(a.size() + 1));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a[0].size(); j++)
            g[i][j] = a[i][j];

    for (int i = 0; i < a.size(); i++)
        g[i][a.size()] = b[i];

    cout << setprecision(3);
    print(g, a.size());

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

//-----------------------------------------------------------------------------------------------------

vector<vector<double>> transpone(const vector<vector<double>>& a) {
    vector<vector<double>> ans(a.size(), vector<double>(a.size()));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++)
            ans[j][i] = a[i][j];
    return ans;
}

pair<vector<vector<double>>, vector<vector<double>>> split(const vector<vector<double>>& a) {
    vector<vector<double>> l(a.size(), vector<double>(a.size()));
    l[0][0] = sqrt(a[0][0]);

    for (int j = 1; j < a.size(); j++)
        l[j][0] = a[j][0] / l[0][0];

    for (int i = 1; i < a.size(); i++) {
        double sum = 0;
        for (int p = 0; p < i; p++) sum += l[i][p] * l[i][p];
        l[i][i] = sqrt(a[i][i] - sum);

        for (int j = i + 1; j < a.size(); j++) {
            sum = 0;
            for (int p = 0; p < i; p++) sum += l[i][p] * l[j][p];
            l[j][i] = (a[j][i] - sum) / l[i][i];
        }
    }

    return { l, transpone(l) };
}

vector<double> solve(const vector<vector<double>>& a, const vector<double>& b) {
    pair<vector<vector<double>>, vector<vector<double>>> llt = split(a);
    //print(llt.first, 0);
    //print(llt.second, 0);

    vector<double> y(a.size());
    for (int i = 0; i < a.size(); i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) sum += y[j] * llt.first[i][j];
        y[i] = (b[i] - sum) / llt.first[i][i];
    }

    vector<double> x(a.size());
    for (int i = a.size()-1; i >= 0; i--) {
        double sum = 0;
        for (int j = i+1; j < a.size(); j++) sum += x[j] * llt.second[i][j];
        x[i] = (y[i] - sum) / llt.second[i][i];
    }

    return x;
}


int main() {
    vector<vector<double>> a{
        {5, 2, 3},
        {2, 6, 1},
        {3, 1, 7}
    };
    vector<double> b{ -3, 4, 34 };

    for (int i = 0; i < 2; i++) {
        vector<double> x = gauss(a, b);
        cout << "Answer Gauss   : (";
        for (double i : x)
            cout << i << ' ';
        cout << "\b)\n";

        x = solve(a, b);
        cout << "Answer Cholesky: (";
        for (double i : x)
            cout << i << ' ';
        cout << "\b)\n";

        a = vector<vector<double>>{
            {21, 5, 8},
            {5, 7, 3},
            {8, 3, 12}
        };

        cout << endl;
    }
}
