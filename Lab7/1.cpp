#include <iostream>
#include <vector>
using namespace std;

template
<typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> ans(a.size());
    for (int i = 0; i < a.size(); i++)
        ans[i] = a[i]+b[i];
    return ans;
}

vector<double> gauss(const vector<vector<double>>& a, const vector<double>& b) {
    vector<vector<double>> g(a.size(), vector<double>(a.size()+1));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a[0].size(); j++)
            g[i][j] = a[i][j];

    for (int i = 0; i < a.size(); i++)
        g[i][a.size()] = b[i];

    for (int i = 0; i < a.size(); i++) {

    }
}

int main() {

}
