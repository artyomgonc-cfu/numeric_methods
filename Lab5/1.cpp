#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double f(double x) {
    return 1.0 / (1 + 25.0 * x * x);
}

vector<double> gauss(vector<vector<double>> a) {
	int n = a.size();
	int i, j, k;

	vector<double> x(a.size());

	for (i = 0; i < n - 1; i++)
	{
		if (a[i][i] == 0.0)
		{
			cout << "Mathematical Error!";
			exit(0);
		}
		for (j = i + 1; j < n; j++)
		{
			double ratio = a[j][i] / a[i][i];

			for (k = 0; k < n + 1; k++)
			{
				a[j][k] = a[j][k] - ratio * a[i][k];
			}
		}
	}

	x[n-1] = a[n-1][n] / a[n-1][n-1];

	for (i = n - 2; i >= 0; i--)
	{
		x[i] = a[i][n];
		for (j = i + 1; j < n; j++)
		{
			x[i] = x[i] - a[i][j] * x[j];
		}
		x[i] = x[i] / a[i][i];
	}

	return x;
}

double sum_xi_pown(const vector<pair<double, double>>& pts, int n) {
    double ans = 0;
    for (auto i : pts)
        ans += pow(i.first, n);
    return ans;
}

double sum_xy_pown(const vector<pair<double, double>>& pts, int n) {
    double ans = 0;
    for (auto i : pts)
        ans += pow(i.first, n) * i.second;
    return ans;
}

int main() {

    double h = 2.0 / 5;

    vector<pair<double, double>> pts;
    for (double x = -1; x <= 1; x += h)
        pts.push_back(make_pair(x, f(x)));

    vector<vector<double>> matrix(2, vector<double>(3));
    matrix[0][0] = sum_xi_pown(pts, 0);
    matrix[0][1] = sum_xi_pown(pts, 1);

    matrix[1][0] = sum_xi_pown(pts, 1);
    matrix[1][1] = sum_xi_pown(pts, 2);

	matrix[0][2] = sum_xy_pown(pts, 0);
	matrix[1][2] = sum_xy_pown(pts, 1);
    
	vector<double> a = gauss(matrix);

	cout << "f:\n";
	for (double x = -1; x <= 1; x += 2.0 / 20)
		cout << f(x) << endl;
	cout << "-----------------------------------------\n";
	cout << "sq_min:\n";
	for (double x = -1; x <= 1; x += 2.0 / 20)
		cout << a[0]+a[1]*x << endl;

    return 0;
}
