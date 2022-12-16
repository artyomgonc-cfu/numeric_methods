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

void elab(const vector<pair<double, double>>& coords, string label) {
    vector<double> x, y;
    for (auto el : coords) {
        x.push_back(el.first);
        y.push_back(el.second);
    }
    vector<vector<double>> table = get_table(x, y);

    cout << label << ":\n";

    for (int i = 0; i < table.size(); i++) {
        cout << '|' << setw(5) << x[i] << '|';
        for (int j = 0; j < table[0].size(); j++)
            cout << setw(5) << table[i][j] << '|';
        cout << endl;
    }

    for (double xv = -2; xv <= 8; xv += 0.5)
        cout << n(xv, x, table) << endl;

    cout << "----------------------------------------\n";
}

int main() {

    vector<pair<double, double>> v3{
        {-2, -22},
        {1, 2},
        {4, 44},
        {8, 408}
    };

    vector<pair<double, double>> v21{
        {-2, -22},
        {1, 2},
        {8, 408}
    };

    vector<pair<double, double>> v22{
        {-2, -22},
        {4, 44},
        {8, 408}
    };

    elab(v21, "2.1");
    elab(v22, "2.2");
    elab(v3, "3");

    return 0;
}
