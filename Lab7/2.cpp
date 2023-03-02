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
    print(g, a.size());

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

        print(g, a.size());
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
        {4, 1, -2},
        {6, 3, -1},
        {8, 7, 5}
    };
    vector<vector<double>> b{
        {-3, 4, 34},
        {7, -2, 12}
    };
    vector<vector<double>> x = gauss(a, b);
    for (int n = 1; n <= x.size(); n++) {
        cout << "Answer "<< n<<": (";
        for (double i : x[n-1])
            cout << i << ' ';
        cout << "\b)\n";
    }
}
